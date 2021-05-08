#pragma once

#include "CustomStrategy.h"
#include "generic/NonCombatStrategy.h"
#include "generic/RacialsStrategy.h"
#include "generic/ChatCommandHandlerStrategy.h"
#include "generic/WorldPacketHandlerStrategy.h"
#include "generic/DeadStrategy.h"
#include "generic/QuestStrategies.h"
#include "generic/LootNonCombatStrategy.h"
#include "generic/DuelStrategy.h"
#include "generic/KiteStrategy.h"
#include "generic/FleeStrategy.h"
#include "generic/FollowMasterStrategy.h"
#include "generic/RunawayStrategy.h"
#include "generic/StayStrategy.h"
#include "generic/UseFoodStrategy.h"
#include "generic/ConserveManaStrategy.h"
#include "generic/EmoteStrategy.h"
#include "generic/TankAoeStrategy.h"
#include "generic/DpsAssistStrategy.h"
#include "generic/PassiveStrategy.h"
#include "generic/GrindingStrategy.h"
#include "generic/UsePotionsStrategy.h"
#include "generic/GuardStrategy.h"
#include "generic/CastTimeStrategy.h"
#include "generic/ThreatStrategy.h"
#include "generic/TellTargetStrategy.h"
#include "generic/AttackEnemyPlayersStrategy.h"
#include "generic/MarkRtiStrategy.h"
#include "generic/MeleeCombatStrategy.h"
#include "generic/PullStrategy.h"
#include "generic/RangedCombatStrategy.h"
#include "generic/ReturnStrategy.h"
#include "generic/RpgStrategy.h"

namespace ai
{
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
        static Strategy* behind(PlayerbotAI* botAI) { return new SetBehindCombatStrategy(botAI); }
        static Strategy* ranged(PlayerbotAI* botAI) { return new RangedCombatStrategy(botAI); }
        static Strategy* close(PlayerbotAI* botAI) { return new MeleeCombatStrategy(botAI); }
        static Strategy* mark_rti(PlayerbotAI* botAI) { return new MarkRtiStrategy(botAI); }
        static Strategy* tell_target(PlayerbotAI* botAI) { return new TellTargetStrategy(botAI); }
        static Strategy* threat(PlayerbotAI* botAI) { return new ThreatStrategy(botAI); }
        static Strategy* cast_time(PlayerbotAI* botAI) { return new CastTimeStrategy(botAI); }
        static Strategy* potions(PlayerbotAI* botAI) { return new UsePotionsStrategy(botAI); }
        static Strategy* kite(PlayerbotAI* botAI) { return new KiteStrategy(botAI); }
        static Strategy* duel(PlayerbotAI* botAI) { return new DuelStrategy(botAI); }
        static Strategy* flee(PlayerbotAI* botAI) { return new FleeStrategy(botAI); }
        static Strategy* dead(PlayerbotAI* botAI) { return new DeadStrategy(botAI); }
        static Strategy* racials(PlayerbotAI* botAI) { return new RacialsStrategy(botAI); }
        static Strategy* loot(PlayerbotAI* botAI) { return new LootNonCombatStrategy(botAI); }
        static Strategy* gather(PlayerbotAI* botAI) { return new GatherStrategy(botAI); }
        static Strategy* emote(PlayerbotAI* botAI) { return new EmoteStrategy(botAI); }
        static Strategy* passive(PlayerbotAI* botAI) { return new PassiveStrategy(botAI); }
        static Strategy* conserve_mana(PlayerbotAI* botAI) { return new ConserveManaStrategy(botAI); }
        static Strategy* food(PlayerbotAI* botAI) { return new UseFoodStrategy(botAI); }
        static Strategy* chat(PlayerbotAI* botAI) { return new ChatCommandHandlerStrategy(botAI); }
        static Strategy* world_packet(PlayerbotAI* botAI) { return new WorldPacketHandlerStrategy(botAI); }
        static Strategy* ready_check(PlayerbotAI* botAI) { return new ReadyCheckStrategy(botAI); }
        static Strategy* pvp(PlayerbotAI* botAI) { return new AttackEnemyPlayersStrategy(botAI); }
        static Strategy* _return(PlayerbotAI* botAI) { return new ReturnStrategy(botAI); }
        static Strategy* lfg(PlayerbotAI* botAI) { return new LfgStrategy(botAI); }
        static Strategy* custom(PlayerbotAI* botAI) { return new CustomStrategy(botAI); }
        static Strategy* reveal(PlayerbotAI* botAI) { return new RevealStrategy(botAI); }
        static Strategy* collision(PlayerbotAI* botAI) { return new CollisionStrategy(botAI); }
        static Strategy* rpg(PlayerbotAI* botAI) { return new RpgStrategy(botAI); }
        static Strategy* sit(PlayerbotAI* botAI) { return new SitStrategy(botAI); }
        static Strategy* possible_ads(PlayerbotAI* botAI) { return new PossibleAdsStrategy(botAI); }
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
        static Strategy* guard(PlayerbotAI* botAI) { return new GuardStrategy(botAI); }
        static Strategy* follow_master(PlayerbotAI* botAI) { return new FollowMasterStrategy(botAI); }
        static Strategy* stay(PlayerbotAI* botAI) { return new StayStrategy(botAI); }
        static Strategy* runaway(PlayerbotAI* botAI) { return new RunawayStrategy(botAI); }
        static Strategy* flee_from_adds(PlayerbotAI* botAI) { return new FleeFromAddsStrategy(botAI); }
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
        static Strategy* dps_assist(PlayerbotAI* botAI) { return new DpsAssistStrategy(botAI); }
        static Strategy* dps_aoe(PlayerbotAI* botAI) { return new DpsAoeStrategy(botAI); }
        static Strategy* tank_aoe(PlayerbotAI* botAI) { return new TankAoeStrategy(botAI); }
        static Strategy* grind(PlayerbotAI* botAI) { return new GrindingStrategy(botAI); }
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
        static Strategy* quest(PlayerbotAI* botAI) { return new DefaultQuestStrategy(botAI); }
        static Strategy* accept_all_quests(PlayerbotAI* botAI) { return new AcceptAllQuestsStrategy(botAI); }
    };
};
