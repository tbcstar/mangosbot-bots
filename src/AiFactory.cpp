/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AiFactory.h"
#include "Playerbot.h"
#include "strategy/Engine.h"
#include "strategy/priest/PriestAiObjectContext.h"
#include "strategy/mage/MageAiObjectContext.h"
#include "strategy/warlock/WarlockAiObjectContext.h"
#include "strategy/warrior/WarriorAiObjectContext.h"
#include "strategy/shaman/ShamanAiObjectContext.h"
#include "strategy/paladin/PaladinAiObjectContext.h"
#include "strategy/druid/DruidAiObjectContext.h"
#include "strategy/hunter/HunterAiObjectContext.h"
#include "strategy/rogue/RogueAiObjectContext.h"

AiObjectContext* AiFactory::createAiObjectContext(Player* player, PlayerbotAI* botAI)
{
    switch (player->getClass())
    {
        case CLASS_PRIEST:
            return new PriestAiObjectContext(botAI);
            break;
        case CLASS_MAGE:
            return new MageAiObjectContext(botAI);
            break;
        case CLASS_WARLOCK:
            return new WarlockAiObjectContext(botAI);
            break;
        case CLASS_WARRIOR:
            return new WarriorAiObjectContext(botAI);
            break;
        case CLASS_SHAMAN:
            return new ShamanAiObjectContext(botAI);
            break;
        case CLASS_PALADIN:
            return new PaladinAiObjectContext(botAI);
            break;
        case CLASS_DRUID:
            return new DruidAiObjectContext(botAI);
            break;
        case CLASS_HUNTER:
            return new HunterAiObjectContext(botAI);
            break;
        case CLASS_ROGUE:
            return new RogueAiObjectContext(botAI);
            break;
    }

    return new AiObjectContext(botAI);
}

uint8 AiFactory::GetPlayerSpecTab(Player* bot)
{
    std::map<uint8, uint32> tabs = GetPlayerSpecTabs(bot);

    int32 tab = -1;
    uint32 max = 0;
    for (uint32 i = 0; i < 3; i++)
    {
        if (tab == -1 || max < tabs[i])
        {
            tab = i;
            max = tabs[i];
        }
    }

    return tab;
}

std::map<uint8, uint32> AiFactory::GetPlayerSpecTabs(Player* bot)
{
    std::map<uint8, uint32> tabs;
    for (uint32 i = 0; i < 3; i++)
        tabs[i] = 0;

    uint32 classMask = bot->getClassMask();
    for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
    {
        TalentEntry const *talentInfo = sTalentStore.LookupEntry(i);
        if (!talentInfo)
            continue;

        TalentTabEntry const *talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);
        if (!talentTabInfo)
            continue;

        if ((classMask & talentTabInfo->ClassMask) == 0)
            continue;

        uint32 maxRank = 0;
        for (uint32 rank = MAX_TALENT_RANK - 1; rank >= 0; --rank)
        {
            if (!talentInfo->RankID[rank])
                continue;

            uint32 spellid = talentInfo->RankID[rank];
            if (spellid && bot->HasSpell(spellid))
                maxRank = rank + 1;

        }

        tabs[talentTabInfo->tabpage] += maxRank;
    }

    return tabs;
}

void AiFactory::AddDefaultCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* engine)
{
    uint8 tab = GetPlayerSpecTab(player);

    engine->addStrategies("racials", "chat", "default", "aoe", "potions", "cast time", "conserve mana", "duel", "pvp", "stay", nullptr);

    switch (player->getClass())
    {
        case CLASS_PRIEST:
            if (tab == 2)
            {
                engine->addStrategies("dps", "threat", nullptr);
                if (player->getLevel() > 19)
                    engine->addStrategy("dps debuff");
            }
            else
                engine->addStrategy("heal");

            engine->addStrategies("dps assist", "flee", "cure", "ranged", "cc", nullptr);
            break;
        case CLASS_MAGE:
            if (tab == 0)
                engine->addStrategies("arcane", "threat", nullptr);
            else if (tab == 1)
                engine->addStrategies("fire", "fire aoe", "threat", nullptr);
            else
                engine->addStrategies("frost", "frost aoe", "threat", nullptr);

            engine->addStrategies("dps assist", "flee", "cure", "ranged", "cc", nullptr);
            break;
        case CLASS_WARRIOR:
            if (tab == 2)
                engine->addStrategies("tank", "tank aoe", "close", nullptr);
            else
                engine->addStrategies("dps", "dps assist", "threat", "close", nullptr);
            break;
        case CLASS_SHAMAN:
            if (tab == 0)
                engine->addStrategies("caster", "caster aoe", "bmana", "threat", "flee", "ranged", nullptr);
            else if (tab == 2)
                engine->addStrategies("heal", "bmana", "flee", "ranged", nullptr);
            else
                engine->addStrategies("dps", "melee aoe", "bdps", "threat", "close", nullptr);

            engine->addStrategies("dps assist", "cure", nullptr);
            break;
        case CLASS_PALADIN:
            if (tab == 1)
                engine->addStrategies("tank", "tank aoe", "bthreat", "cure", "baoe", "close", "cc", nullptr);
            else
                engine->addStrategies("dps", "bdps", "dps assist", "cure", "close", "cc", nullptr);
            break;
        case CLASS_DRUID:
            if (tab == 0)
            {
                engine->addStrategies("caster", "cure", "caster aoe", "threat", "flee", "dps assist", "ranged", "cc", nullptr);
                if (player->getLevel() > 19)
                    engine->addStrategy("caster debuff");
            }
            else if (tab == 2)
                engine->addStrategies("heal", "cure", "flee", "dps assist", "close", "cc", nullptr);
            else
                engine->addStrategies("bear", "tank aoe", "flee", "ranged", nullptr);
            break;
        case CLASS_HUNTER:
            engine->addStrategies("dps", "bdps", "threat", "dps assist", "ranged", "pet", "cc", nullptr);
            if (player->getLevel() > 19)
                engine->addStrategy("dps debuff");
            break;
        case CLASS_ROGUE:
            engine->addStrategies("dps", "threat", "dps assist", "aoe", "close", nullptr);
            break;
        case CLASS_WARLOCK:
            if (tab == 1)
                engine->addStrategies("tank", "threat", nullptr);
            else
                engine->addStrategies("dps", "threat", nullptr);

            if (player->getLevel() > 19)
                engine->addStrategy("dps debuff");

            engine->addStrategies("dps assist", "flee", "ranged", "cc", "pet", nullptr);
            break;
    }

    if (sRandomPlayerbotMgr->IsRandomBot(player))
    {
        if (!player->GetGroup())
        {
            engine->ChangeStrategy(sPlayerbotAIConfig->randomBotCombatStrategies);
            if (player->getClass() == CLASS_DRUID && player->getLevel() < 20)
            {
                engine->addStrategies("bear", "close", nullptr);
            }
        }
    }
    else
    {
        engine->ChangeStrategy(sPlayerbotAIConfig->combatStrategies);
    }
}

Engine* AiFactory::createCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext)
{
	Engine* engine = new Engine(facade, AiObjectContext);
    AddDefaultCombatStrategies(player, facade, engine);
    return engine;
}

void AiFactory::AddDefaultNonCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* nonCombatEngine)
{
    uint8 tab = GetPlayerSpecTab(player);

    switch (player->getClass())
    {
        case CLASS_PRIEST:
            nonCombatEngine->addStrategies("dps assist", "cure", nullptr);
            break;
        case CLASS_PALADIN:
            if (tab == 1)
                nonCombatEngine->addStrategies("bthreat", "tank aoe", nullptr);
            else
                nonCombatEngine->addStrategies("bdps", "dps assist", nullptr);

            nonCombatEngine->addStrategies("cure", nullptr);
            break;
        case CLASS_HUNTER:
            nonCombatEngine->addStrategies("bdps", "dps assist", nullptr);
            break;
        case CLASS_SHAMAN:
            if (tab == 0 || tab == 2)
                nonCombatEngine->addStrategy("bmana");
            else
                nonCombatEngine->addStrategy("bdps");

            nonCombatEngine->addStrategies("dps assist", "cure", nullptr);
            break;
        case CLASS_MAGE:
            if (tab == 1)
                nonCombatEngine->addStrategy("bdps");
            else
                nonCombatEngine->addStrategy("bmana");

            nonCombatEngine->addStrategies("dps assist", "cure", nullptr);
            break;
        case CLASS_DRUID:
            if (tab == 1)
                nonCombatEngine->addStrategy("tank aoe");
            else
                nonCombatEngine->addStrategies("dps assist", "cure", nullptr);
            break;
        case CLASS_WARRIOR:
            if (tab == 2)
                nonCombatEngine->addStrategy("tank aoe");
            else
                nonCombatEngine->addStrategy("dps assist");
            break;
        default:
            nonCombatEngine->addStrategy("dps assist");
            break;
    }

    nonCombatEngine->addStrategies("nc", "food", "stay", "sit", "chat", "default", "quest", "loot", "gather", "duel", "emote", "conserve mana", "buff", nullptr);

    if (sRandomPlayerbotMgr->IsRandomBot(player))
    {
        if (!player->GetGroup())
        {
            nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig->randomBotNonCombatStrategies);
        }
    }
    else
    {
        nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig->nonCombatStrategies);
    }
}

Engine* AiFactory::createNonCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext)
{
	Engine* nonCombatEngine = new Engine(facade, AiObjectContext);

    AddDefaultNonCombatStrategies(player, facade, nonCombatEngine);
	return nonCombatEngine;
}

void AiFactory::AddDefaultDeadStrategies(Player* player, PlayerbotAI* const facade, Engine* deadEngine)
{
    deadEngine->addStrategies("dead", "stay", "chat", "default", "follow", nullptr);

    if (sRandomPlayerbotMgr->IsRandomBot(player) && !player->GetGroup())
    {
        deadEngine->removeStrategy("follow");
    }
}

Engine* AiFactory::createDeadEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext)
{
    Engine* deadEngine = new Engine(facade, AiObjectContext);
    AddDefaultDeadStrategies(player, facade, deadEngine);
    return deadEngine;
}
