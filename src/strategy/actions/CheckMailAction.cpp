/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "CheckMailAction.h"
#include "Event.h"
#include "GuildTaskMgr.h"
#include "Playerbot.h"

bool CheckMailAction::Execute(Event event)
{
    WorldPacket p;
    bot->GetSession()->HandleQueryNextMailTime(p);

    std::vector<uint32> ids;
    for (PlayerMails::iterator i = bot->GetMailBegin(); i != bot->GetMailEnd(); ++i)
    {
        Mail* mail = *i;
        if (!mail || mail->state == MAIL_STATE_DELETED)
            continue;

        Player* owner = ObjectAccessor::FindPlayer(ObjectGuid::Create<HighGuid::Player>(mail->sender));
        if (!owner)
            continue;

        uint32 account = sObjectMgr->GetPlayerAccountIdByGUID(owner->GetGUID().GetCounter());
        if (sPlayerbotAIConfig->IsInRandomAccountList(account))
            continue;

        ProcessMail(mail, owner);
        ids.push_back(mail->messageID);
        mail->state = MAIL_STATE_DELETED;
    }

    for (uint32 id : ids)
    {
        bot->SendMailResult(id, MAIL_DELETED, MAIL_OK);
        CharacterDatabase.PExecute("DELETE FROM mail WHERE id = '%u'", id);
        CharacterDatabase.PExecute("DELETE FROM mail_items WHERE mail_id = '%u'", id);
        bot->RemoveMail(id);
    }

    return true;
}

bool CheckMailAction::isUseful()
{
    if (botAI->GetMaster() || !bot->GetMailSize() || bot->InBattleground())
        return false;

    return true;
}

void CheckMailAction::ProcessMail(Mail* mail, Player* owner)
{
    if (mail->items.empty())
    {
        if (mail->itemTextId)
        {
            sGuildTaskMgr->CheckTaskTransfer(sObjectMgr->GetItemText(mail->itemTextId), owner, bot);
        }
        return;
    }

    if (mail->subject.find("Item(s) you asked for") != string::npos)
        return;

    for (MailItemInfoVec::iterator i = mail->items.begin(); i != mail->items.end(); ++i)
    {
        Item *item = bot->GetMItem(i->item_guid);
        if (!item)
            continue;

        if (!sGuildTaskMgr->CheckItemTask(i->item_template, item->GetCount(), owner, bot, true))
        {
            std::ostringstream body;
            body << "Hello, " << owner->GetName() << ",\n";
            body << "\n";
            body << "Here are the item(s) you've sent me by mistake";
            body << "\n";
            body << "Thanks,\n";
            body << bot->GetName() << "\n";

            MailDraft draft("Item(s) you've sent me", body.str());
            draft.AddItem(item);
            bot->RemoveMItem(i->item_guid);
            draft.SendMailTo(MailReceiver(owner), MailSender(bot));
            return;
        }

        bot->RemoveMItem(i->item_guid);
        item->DestroyForPlayer(bot);
    }
}
