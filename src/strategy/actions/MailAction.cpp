#include "botpch.h"
#include "Mail.h"
#include "../../playerbot.h"
#include "MailAction.h"
#include "../../PlayerbotAIConfig.h"
#include "../../Helpers.h"

using namespace ai;

map<string, MailProcessor*> MailAction::processors;

class TellMailProcessor : public MailProcessor
{
public:
    virtual bool Before(PlayerbotAI* botAI)
    {
        botAI->TellMaster("=== Mailbox ===");
        tells.clear();
        return true;
    }
    virtual bool Process(int index, Mail* mail, PlayerbotAI* botAI)
    {
        Player* bot = botAI->GetBot();
        time_t cur_time = time(0);
        int days = (cur_time - mail->deliver_time) / 3600 / 24;
        ostringstream out;
        out << "#" << (index+1) << " ";
        if (!mail->money && !mail->has_items)
            out << "|cffffffff" << mail->subject;

        if (mail->money)
        {
            out << "|cffffff00" << ChatHelper::formatMoney(mail->money);
            if (!mail->subject.empty()) out << " |cffa0a0a0(" << mail->subject << ")";
        }

        if (mail->has_items)
        {
            for (MailItemInfoVec::iterator i = mail->items.begin(); i != mail->items.end(); ++i)
            {
                Item* item = bot->GetMItem(i->item_guid);
                int count = item ? item->GetCount() : 1;
                ItemTemplate const* proto = sObjectMgr->GetItemTemplate(i->item_template);
                if (proto)
                {
                    out << ChatHelper::formatItem(proto, count);
                    if (!mail->subject.empty()) out << " |cffa0a0a0(" << mail->subject << ")";
                }
            }
        }
        out  << ", |cff00ff00" << days << " day(s)";
        tells.push_front(out.str());
        return true;
    }

    virtual bool After(PlayerbotAI* botAI)
    {
        for (list<string>::iterator i = tells.begin(); i != tells.end(); ++i)
            botAI->TellMaster(*i);

        return true;
    }
    static TellMailProcessor instance;

private:
    list<string> tells;
};

class TakeMailProcessor : public MailProcessor
{
public:
    virtual bool Process(int index, Mail* mail, PlayerbotAI* botAI)
    {
        Player* bot = botAI->GetBot();
        if (!CheckBagSpace(bot))
        {
            botAI->TellError("Not enough bag space");
            return false;
        }

        ObjectGuid mailbox = FindMailbox(botAI);
        if (mail->money)
        {
            ostringstream out;
            out << mail->subject << ", |cffffff00" << ChatHelper::formatMoney(mail->money) << "|cff00ff00 processed";
            botAI->TellMaster(out.str());

            WorldPacket packet;
            packet << mailbox;
            packet << mail->messageID;
            bot->GetSession()->HandleMailTakeMoney(packet);
            RemoveMail(bot, mail->messageID, mailbox);
        }
        else if (!mail->items.empty())
        {
            list<uint32> guids;
            for (MailItemInfoVec::iterator i = mail->items.begin(); i != mail->items.end(); ++i)
            {
                ItemTemplate const* proto = sObjectMgr->GetItemTemplate(i->item_template);
                if (proto)
                    guids.push_back(i->item_guid);
            }

            for (list<uint32>::iterator i = guids.begin(); i != guids.end(); ++i)
            {
                WorldPacket packet;
                packet << mailbox;
                packet << mail->messageID;
                packet << *i;
                Item* item = bot->GetMItem(*i);
                ostringstream out;
                out << mail->subject << ", " << ChatHelper::formatItem(item->GetProto()) << "|cff00ff00 processed";

                bot->GetSession()->HandleMailTakeItem(packet);
                botAI->TellMaster(out.str());
            }

            RemoveMail(bot, mail->messageID, mailbox);
        }
        return true;
    }

    static TakeMailProcessor instance;

private:
    bool CheckBagSpace(Player* bot)
    {
        uint32 totalused = 0, total = 16;
        for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
        {
            if (bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                totalused++;
        }
        uint32 totalfree = 16 - totalused;
        for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
        {
            if (const Bag* const pBag = (Bag*) bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag))
            {
                ItemTemplate const* pBagProto = pBag->GetProto();
                if (pBagProto->Class == ITEM_CLASS_CONTAINER && pBagProto->SubClass == ITEM_SUBCLASS_CONTAINER)
                    totalfree += pBag->GetFreeSlots();
            }

        }

        return totalfree >= 2;
    }
};

class DeleteMailProcessor : public MailProcessor
{
public:
    virtual bool Process(int index, Mail* mail, PlayerbotAI* botAI)
    {
        ostringstream out;
        out << "|cffffffff" << mail->subject << "|cffff0000 deleted";
        RemoveMail(botAI->GetBot(), mail->messageID, FindMailbox(botAI));
        botAI->TellMaster(out.str());
        return true;
    }

    static DeleteMailProcessor instance;
};

class ReadMailProcessor : public MailProcessor
{
public:
    virtual bool Process(int index, Mail* mail, PlayerbotAI* botAI)
    {
        ostringstream out, body;
        out << "|cffffffff" << mail->subject;
        botAI->TellMaster(out.str());
        if (mail->itemTextId)
        {
            body << "\n" << sObjectMgr->GetItemText(mail->itemTextId);
            botAI->TellMaster(body.str());
        }
        return true;
    }
    static ReadMailProcessor instance;
};

TellMailProcessor TellMailProcessor::instance;
TakeMailProcessor TakeMailProcessor::instance;
DeleteMailProcessor DeleteMailProcessor::instance;
ReadMailProcessor ReadMailProcessor::instance;

bool MailAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    if (!MailProcessor::FindMailbox(botAI))
    {
        botAI->TellError("There is no mailbox nearby");
        return false;
    }

    if (processors.empty())
    {
        processors["?"] = &TellMailProcessor::instance;
        processors["take"] = &TakeMailProcessor::instance;
        processors["delete"] = &DeleteMailProcessor::instance;
        processors["read"] = &ReadMailProcessor::instance;
    }

    string text = event.getParam();
    if (text.empty())
    {
        botAI->TellMaster("whisper 'mail ?' to query mailbox, 'mail take/delete/read filter' to take/delete/read mails by filter");
        return false;
    }

    vector<string> ss = split(text, ' ');
    string action = ss[0];
    string filter = ss.size() > 1 ? ss[1] : "";
    MailProcessor* processor = processors[action];
    if (!processor)
    {
        ostringstream out; out << action << ": I don't know how to do that";
        botAI->TellMaster(out.str());
        return false;
    }

    if (!processor->Before(botAI))
        return false;

    vector<Mail*> mailList;
    time_t cur_time = time(0);
    for (PlayerMails::iterator itr = bot->GetMailBegin(); itr != bot->GetMailEnd(); ++itr)
    {
        if ((*itr)->state == MAIL_STATE_DELETED || cur_time < (*itr)->deliver_time)
            continue;

        Mail *mail = *itr;
        mailList.push_back(mail);
    }

    map<int, Mail*> filtered = filterList(mailList, filter);
    for (map<int, Mail*>::iterator i = filtered.begin(); i != filtered.end(); ++i)
    {
        if (!processor->Process(i->first, i->second, ai))
            break;
    }

    return processor->After(botAI);
}

void MailProcessor::RemoveMail(Player* bot, uint32 id, ObjectGuid mailbox)
{
    WorldPacket packet;
    packet << mailbox;
    packet << id;
    packet << (uint32)0; //mailTemplateId
    bot->GetSession()->HandleMailDelete(packet);
}

ObjectGuid MailProcessor::FindMailbox(PlayerbotAI* botAI)
{
    list<ObjectGuid> gos = *botAI->GetAiObjectContext()->GetValue<list<ObjectGuid> >("nearest game objects");
    ObjectGuid mailbox;
    for (list<ObjectGuid>::iterator i = gos.begin(); i != gos.end(); ++i)
    {
        GameObject* go = botAI->GetGameObject(*i);
        if (go && go->GetGoType() == GAMEOBJECT_TYPE_MAILBOX)
        {
            mailbox = go->GetGUID();
            break;
        }
    }

    return mailbox;
}
