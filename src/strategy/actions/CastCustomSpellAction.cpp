/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "CastCustomSpellAction.h"
#include "../Event.h"
#include "../../Playerbot.h"

uint32 FindLastSeparator(std::string const& text, std::string const& sep)
{
    uint32 pos = text.rfind(sep);
    if (pos == std::string::npos)
        return pos;

    uint32 lastLinkBegin = text.rfind("|H");
    uint32 lastLinkEnd = text.find("|h|r", lastLinkBegin + 1);
    if (pos >= lastLinkBegin && pos <= lastLinkEnd)
        pos = text.find_last_of(sep, lastLinkBegin);

    return pos;
}

bool CastCustomSpellAction::Execute(Event event)
{
    Unit* target = nullptr;

    Player* master = GetMaster();
    if (master && master->GetTarget())
        target = botAI->GetUnit(master->GetTarget());

    if (!target)
        target = bot;

    std::string text = event.getParam();

    Item* itemTarget = nullptr;

    uint32 pos = FindLastSeparator(text, " ");
    uint32 castCount = 1;
    if (pos != std::string::npos)
    {
        std:string const& param = text.substr(pos + 1);
        std::vector<Item*> items = InventoryAction::parseItems(param, ITERATE_ITEMS_IN_BAGS);
        if (!items.empty())
            itemTarget = *items.begin();
        else
        {
            castCount = atoi(param.c_str());
            if (castCount > 0)
                text = text.substr(0, pos);
        }
    }

    uint32 spell = AI_VALUE2(uint32, "spell id", text);

    std::ostringstream msg;
    if (!spell)
    {
        msg << "Unknown spell " << text;
        botAI->TellError(msg.str());
        return false;
    }

    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell);
    if (!spellInfo)
    {
        msg << "Unknown spell " << text;
        botAI->TellError(msg.str());
        return false;
    }

    if (target != bot && !bot->IsInFront(target, sPlayerbotAIConfig->sightDistance, CAST_ANGLE_IN_FRONT))
    {
        bot->SetFacingTo(target);
        botAI->SetNextCheckDelay(sPlayerbotAIConfig->globalCoolDown);

        msg << "cast " << text;
        botAI->HandleCommand(CHAT_MSG_WHISPER, msg.str(), *master);
        return true;
    }

    std::ostringstream spellName;
    spellName << ChatHelper::formatSpell(spellInfo) << " on ";

    if (bot->GetTrader())
        spellName << "trade item";
    else if (itemTarget)
        spellName << chat->formatItem(itemTarget->GetTemplate());
    else if (target == bot)
        spellName << "self";
    else
        spellName << target->GetName();

    if (!bot->GetTrader() && !botAI->CanCastSpell(spell, target, true, itemTarget))
    {
        msg << "Cannot cast " << spellName.str();
        botAI->TellError(msg.str());
        return false;
    }

    bool result = spell ? botAI->CastSpell(spell, target, itemTarget) : botAI->CastSpell(text, target, itemTarget);
    if (result)
    {
        msg << "Casting " << spellName.str();

        if (castCount > 1)
        {
            std::ostringstream cmd;
            cmd << "cast " << text << " " << (castCount - 1);
            botAI->HandleCommand(CHAT_MSG_WHISPER, cmd.str(), *master);
            msg << "|cffffff00(x" << (castCount-1) << " left)|r";
        }

        botAI->TellMasterNoFacing(msg.str());
    }
    else
    {
        msg << "Cast " << spellName.str() << " is failed";
        botAI->TellError(msg.str());
    }

    return result;
}
