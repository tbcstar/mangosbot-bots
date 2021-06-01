/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "CustomStrategy.h"
#include "NamedObjectContext.h"
#include "AttackEnemyPlayersStrategy.h"
#include "CastTimeStrategy.h"
#include "ChatCommandHandlerStrategy.h"
#include "ConserveManaStrategy.h"
#include "DeadStrategy.h"
#include "DpsAssistStrategy.h"
#include "DuelStrategy.h"
#include "EmoteStrategy.h"
#include "FleeStrategy.h"
#include "FollowMasterStrategy.h"
#include "GrindingStrategy.h"
#include "GuardStrategy.h"
#include "KiteStrategy.h"
#include "LootNonCombatStrategy.h"
#include "MarkRtiStrategy.h"
#include "MeleeCombatStrategy.h"
#include "NonCombatStrategy.h"
#include "QuestStrategies.h"
#include "PassiveStrategy.h"
#include "PullStrategy.h"
#include "RacialsStrategy.h"
#include "RangedCombatStrategy.h"
#include "ReturnStrategy.h"
#include "RpgStrategy.h"
#include "RunawayStrategy.h"
#include "StayStrategy.h"
#include "TankAoeStrategy.h"
#include "TellTargetStrategy.h"
#include "ThreatStrategy.h"
#include "UseFoodStrategy.h"
#include "UsePotionsStrategy.h"
#include "WorldPacketHandlerStrategy.h"

class StrategyContext : public NamedObjectContext<Strategy>
{
    public:
        StrategyContext()
        {
            creators["racials"] = &StrategyContext::racials;
            creators["loot"] = &StrategyContext::loot;
            creators["gather"] = &StrategyContext::gather;
            creators["emote"] = &StrategyContext::emote;
            creators["passive"] = &StrategyContext::passive;
            creators["conserve mana"] = &StrategyContext::conserve_mana;
            creators["food"] = &StrategyContext::food;
            creators["chat"] = &StrategyContext::chat;
            creators["default"] = &StrategyContext::world_packet;
            creators["ready check"] = &StrategyContext::ready_check;
            creators["dead"] = &StrategyContext::dead;
            creators["flee"] = &StrategyContext::flee;
            creators["duel"] = &StrategyContext::duel;
            creators["kite"] = &StrategyContext::kite;
            creators["potions"] = &StrategyContext::potions;
            creators["cast time"] = &StrategyContext::cast_time;
            creators["threat"] = &StrategyContext::threat;
            creators["tell target"] = &StrategyContext::tell_target;
            creators["pvp"] = &StrategyContext::pvp;
            creators["return"] = &StrategyContext::_return;
            creators["lfg"] = &StrategyContext::lfg;
            creators["custom"] = &StrategyContext::custom;
            creators["reveal"] = &StrategyContext::reveal;
            creators["collision"] = &StrategyContext::collision;
            creators["rpg"] = &StrategyContext::rpg;
            creators["sit"] = &StrategyContext::sit;
            creators["mark rti"] = &StrategyContext::mark_rti;
            creators["ads"] = &StrategyContext::possible_ads;
            creators["close"] = &StrategyContext::close;
            creators["ranged"] = &StrategyContext::ranged;
            creators["behind"] = &StrategyContext::behind;
        }

    private:
        static Strategy* behind() { return new SetBehindCombatStrategy(); }
        static Strategy* ranged() { return new RangedCombatStrategy(); }
        static Strategy* close() { return new MeleeCombatStrategy(); }
        static Strategy* mark_rti() { return new MarkRtiStrategy(); }
        static Strategy* tell_target() { return new TellTargetStrategy(); }
        static Strategy* threat() { return new ThreatStrategy(); }
        static Strategy* cast_time() { return new CastTimeStrategy(); }
        static Strategy* potions() { return new UsePotionsStrategy(); }
        static Strategy* kite() { return new KiteStrategy(); }
        static Strategy* duel() { return new DuelStrategy(); }
        static Strategy* flee() { return new FleeStrategy(); }
        static Strategy* dead() { return new DeadStrategy(); }
        static Strategy* racials() { return new RacialsStrategy(); }
        static Strategy* loot() { return new LootNonCombatStrategy(); }
        static Strategy* gather() { return new GatherStrategy(); }
        static Strategy* emote() { return new EmoteStrategy(); }
        static Strategy* passive() { return new PassiveStrategy(); }
        static Strategy* conserve_mana() { return new ConserveManaStrategy(); }
        static Strategy* food() { return new UseFoodStrategy(); }
        static Strategy* chat() { return new ChatCommandHandlerStrategy(); }
        static Strategy* world_packet() { return new WorldPacketHandlerStrategy(); }
        static Strategy* ready_check() { return new ReadyCheckStrategy(); }
        static Strategy* pvp() { return new AttackEnemyPlayersStrategy(); }
        static Strategy* _return() { return new ReturnStrategy(); }
        static Strategy* lfg() { return new LfgStrategy(); }
        static Strategy* custom() { return new CustomStrategy(); }
        static Strategy* reveal() { return new RevealStrategy(); }
        static Strategy* collision() { return new CollisionStrategy(); }
        static Strategy* rpg() { return new RpgStrategy(); }
        static Strategy* sit() { return new SitStrategy(); }
        static Strategy* possible_ads() { return new PossibleAdsStrategy(); }
};

class MovementStrategyContext : public NamedObjectContext<Strategy>
{
    public:
        MovementStrategyContext() : NamedObjectContext<Strategy>(false, true)
        {
            creators["follow"] = &MovementStrategyContext::follow_master;
            creators["stay"] = &MovementStrategyContext::stay;
            creators["runaway"] = &MovementStrategyContext::runaway;
            creators["flee from adds"] = &MovementStrategyContext::flee_from_adds;
            creators["guard"] = &MovementStrategyContext::guard;
        }

    private:
        static Strategy* guard() { return new GuardStrategy(); }
        static Strategy* follow_master() { return new FollowMasterStrategy(); }
        static Strategy* stay() { return new StayStrategy(); }
        static Strategy* runaway() { return new RunawayStrategy(); }
        static Strategy* flee_from_adds() { return new FleeFromAddsStrategy(); }
    };

    class AssistStrategyContext : public NamedObjectContext<Strategy>
    {
    public:
        AssistStrategyContext() : NamedObjectContext<Strategy>(false, true)
        {
            creators["dps assist"] = &AssistStrategyContext::dps_assist;
            creators["dps aoe"] = &AssistStrategyContext::dps_aoe;
            creators["tank aoe"] = &AssistStrategyContext::tank_aoe;
            creators["grind"] = &AssistStrategyContext::grind;
        }

    private:
        static Strategy* dps_assist() { return new DpsAssistStrategy(); }
        static Strategy* dps_aoe() { return new DpsAoeStrategy(); }
        static Strategy* tank_aoe() { return new TankAoeStrategy(); }
        static Strategy* grind() { return new GrindingStrategy(); }
};

class QuestStrategyContext : public NamedObjectContext<Strategy>
{
    public:
        QuestStrategyContext() : NamedObjectContext<Strategy>(false, true)
        {
            creators["quest"] = &QuestStrategyContext::quest;
            creators["accept all quests"] = &QuestStrategyContext::accept_all_quests;
        }

    private:
        static Strategy* quest() { return new DefaultQuestStrategy(); }
        static Strategy* accept_all_quests() { return new AcceptAllQuestsStrategy(); }
};
