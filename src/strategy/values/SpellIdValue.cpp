/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "SpellIdValue.h"
#include "ChatHelper.h"

SpellIdValue::SpellIdValue(PlayerbotAI* botAI) : CalculatedValue<uint32>(botAI, "spell id")
{
}

uint32 SpellIdValue::Calculate()
{
    std::string namepart = qualifier;
    ItemIds itemIds = ChatHelper::parseItems(namepart);

    PlayerbotChatHandler handler(bot);
    uint32 extractedSpellId = handler.extractSpellId(namepart);
    if (extractedSpellId)
        if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(extractedSpellId))
            namepart = spellInfo->SpellName[0];

    wstring wnamepart;
    if (!Utf8toWStr(namepart, wnamepart))
        return 0;

    wstrToLower(wnamepart);
    char firstSymbol = tolower(namepart[0]);
    int spellLength = wnamepart.length();

    LocaleConstant loc = bot->GetSession()->GetSessionDbcLocale();

    std::set<uint32> spellIds;
    for (PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr)
    {
        uint32 spellId = itr->first;

        if (itr->second->State == PLAYERSPELL_REMOVED || !itr->second->Active)
            continue;

        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if (!spellInfo || spellInfo->IsPassive())
            continue;

        if (spellInfo->Effects[0].Effect == SPELL_EFFECT_LEARN_SPELL)
            continue;

        bool useByItem = false;
        for (uint8 i = 0; i < 3; ++i)
        {
            if (spellInfo->Effects[i].Effect == SPELL_EFFECT_CREATE_ITEM && itemIds.find(spellInfo->Effects[i].ItemType) != itemIds.end())
            {
                useByItem = true;
                break;
            }
        }

        char* spellName = spellInfo->SpellName[loc];
        if (!useByItem && (tolower(spellName[0]) != firstSymbol || strlen(spellName) != spellLength || !Utf8FitTo(spellName, wnamepart)))
            continue;

        spellIds.insert(spellId);
    }

    Pet* pet = bot->GetPet();
    if (spellIds.empty() && pet)
    {
        for (PetSpellMap::const_iterator itr = pet->m_spells.begin(); itr != pet->m_spells.end(); ++itr)
        {
            if (itr->second.state == PETSPELL_REMOVED)
                continue;

            uint32 spellId = itr->first;
            SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
            if (!spellInfo)
                continue;

            if (spellInfo->Effects[0].Effect == SPELL_EFFECT_LEARN_SPELL)
                continue;

            char* spellName = spellInfo->SpellName[loc];
            if (tolower(spellName[0]) != firstSymbol || strlen(spellName) != spellLength || !Utf8FitTo(spellName, wnamepart))
                continue;

            spellIds.insert(spellId);
        }
    }

    if (spellIds.empty()) return 0;

    int32 saveMana = (int32)round(AI_VALUE(double, "mana save level"));
    int32 rank = 1;
    int32 highest = 0;
    int32 lowest = 0;
    for (std::set<uint32>::reverse_iterator i = spellIds.rbegin(); i != spellIds.rend(); ++i)
    {
        if (!highest)
            highest = *i;

        if (saveMana == rank)
            return *i;

        lowest = *i;
        ++rank;
    }

    return saveMana > 1 ? lowest : highest;
}
