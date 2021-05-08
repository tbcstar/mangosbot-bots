#include "botpch.h"
#include "../../playerbot.h"
#include "WarriorActions.h"
#include "WarriorAiObjectContext.h"
#include "GenericWarriorNonCombatStrategy.h"
#include "TankWarriorStrategy.h"
#include "DpsWarriorStrategy.h"
#include "../generic/PullStrategy.h"
#include "WarriorTriggers.h"
#include "../NamedObjectContext.h"

using namespace ai;


namespace ai
{
    namespace warrior
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &warrior::StrategyFactoryInternal::nc;
                creators["pull"] = &warrior::StrategyFactoryInternal::pull;
                creators["aoe"] = &warrior::StrategyFactoryInternal::aoe;
            }

        private:
            static Strategy* nc(PlayerbotAI* botAI) { return new GenericWarriorNonCombatStrategy(botAI); }
            static Strategy* aoe(PlayerbotAI* botAI) { return new DpsWarrirorAoeStrategy(botAI); }
            static Strategy* pull(PlayerbotAI* botAI) { return new PullStrategy(ai, "shoot"); }
        };

        class CombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            CombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["tank"] = &warrior::CombatStrategyFactoryInternal::tank;
                creators["dps"] = &warrior::CombatStrategyFactoryInternal::dps;
            }

        private:
            static Strategy* tank(PlayerbotAI* botAI) { return new TankWarriorStrategy(botAI); }
            static Strategy* dps(PlayerbotAI* botAI) { return new DpsWarriorStrategy(botAI); }
        };
    };
};

namespace ai
{
    namespace warrior
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["hamstring"] = &TriggerFactoryInternal::hamstring;
                creators["victory rush"] = &TriggerFactoryInternal::victory_rush;
                creators["death wish"] = &TriggerFactoryInternal::death_wish;
                creators["battle shout"] = &TriggerFactoryInternal::battle_shout;
                creators["rend"] = &TriggerFactoryInternal::rend;
                creators["rend on attacker"] = &TriggerFactoryInternal::rend_on_attacker;
                creators["bloodrage"] = &TriggerFactoryInternal::bloodrage;
                creators["shield bash"] = &TriggerFactoryInternal::shield_bash;
                creators["disarm"] = &TriggerFactoryInternal::disarm;
                creators["concussion blow"] = &TriggerFactoryInternal::concussion_blow;
                creators["sword and board"] = &TriggerFactoryInternal::SwordAndBoard;
                creators["shield bash on enemy healer"] = &TriggerFactoryInternal::shield_bash_on_enemy_healer;
                creators["battle stance"] = &TriggerFactoryInternal::battle_stance;
                creators["defensive stance"] = &TriggerFactoryInternal::defensive_stance;
                creators["shield block"] = &TriggerFactoryInternal::shield_block;

            }

        private:
            static Trigger* shield_block(PlayerbotAI* botAI) { return new ShieldBlockTrigger(botAI); }
            static Trigger* defensive_stance(PlayerbotAI* botAI) { return new DefensiveStanceTrigger(botAI); }
            static Trigger* battle_stance(PlayerbotAI* botAI) { return new BattleStanceTrigger(botAI); }
            static Trigger* hamstring(PlayerbotAI* botAI) { return new HamstringTrigger(botAI); }
            static Trigger* victory_rush(PlayerbotAI* botAI) { return new VictoryRushTrigger(botAI); }
            static Trigger* death_wish(PlayerbotAI* botAI) { return new DeathWishTrigger(botAI); }
            static Trigger* battle_shout(PlayerbotAI* botAI) { return new BattleShoutTrigger(botAI); }
            static Trigger* rend(PlayerbotAI* botAI) { return new RendDebuffTrigger(botAI); }
            static Trigger* rend_on_attacker(PlayerbotAI* botAI) { return new RendDebuffOnAttackerTrigger(botAI); }
            static Trigger* bloodrage(PlayerbotAI* botAI) { return new BloodrageDebuffTrigger(botAI); }
            static Trigger* shield_bash(PlayerbotAI* botAI) { return new ShieldBashInterruptSpellTrigger(botAI); }
            static Trigger* disarm(PlayerbotAI* botAI) { return new DisarmDebuffTrigger(botAI); }
            static Trigger* concussion_blow(PlayerbotAI* botAI) { return new ConcussionBlowTrigger(botAI); }
            static Trigger* SwordAndBoard(PlayerbotAI* botAI) { return new SwordAndBoardTrigger(botAI); }
            static Trigger* shield_bash_on_enemy_healer(PlayerbotAI* botAI) { return new ShieldBashInterruptEnemyHealerSpellTrigger(botAI); }
        };
    };
};


namespace ai
{
    namespace warrior
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["devastate"] = &AiObjectContextInternal::devastate;
                creators["overpower"] = &AiObjectContextInternal::overpower;
                creators["charge"] = &AiObjectContextInternal::charge;
                creators["bloodthirst"] = &AiObjectContextInternal::bloodthirst;
                creators["rend"] = &AiObjectContextInternal::rend;
                creators["rend on attacker"] = &AiObjectContextInternal::rend_on_attacker;
                creators["mocking blow"] = &AiObjectContextInternal::mocking_blow;
                creators["death wish"] = &AiObjectContextInternal::death_wish;
                creators["berserker rage"] = &AiObjectContextInternal::berserker_rage;
                creators["victory rush"] = &AiObjectContextInternal::victory_rush;
                creators["execute"] = &AiObjectContextInternal::execute;
                creators["defensive stance"] = &AiObjectContextInternal::defensive_stance;
                creators["hamstring"] = &AiObjectContextInternal::hamstring;
                creators["shield bash"] = &AiObjectContextInternal::shield_bash;
                creators["shield block"] = &AiObjectContextInternal::shield_block;
                creators["bloodrage"] = &AiObjectContextInternal::bloodrage;
                creators["battle stance"] = &AiObjectContextInternal::battle_stance;
                creators["heroic strike"] = &AiObjectContextInternal::heroic_strike;
                creators["intimidating shout"] = &AiObjectContextInternal::intimidating_shout;
                creators["demoralizing shout"] = &AiObjectContextInternal::demoralizing_shout;
                creators["challenging shout"] = &AiObjectContextInternal::challenging_shout;
                creators["shield wall"] = &AiObjectContextInternal::shield_wall;
                creators["battle shout"] = &AiObjectContextInternal::battle_shout;
                creators["battle shout taunt"] = &AiObjectContextInternal::battle_shout_taunt;
                creators["thunder clap"] = &AiObjectContextInternal::thunder_clap;
                creators["taunt"] = &AiObjectContextInternal::taunt;
                creators["revenge"] = &AiObjectContextInternal::revenge;
                creators["slam"] = &AiObjectContextInternal::slam;
                creators["shield slam"] = &AiObjectContextInternal::shield_slam;
                creators["disarm"] = &AiObjectContextInternal::disarm;
                creators["sunder armor"] = &AiObjectContextInternal::sunder_armor;
                creators["last stand"] = &AiObjectContextInternal::last_stand;
                creators["shockwave"] = &AiObjectContextInternal::shockwave;
                creators["cleave"] = &AiObjectContextInternal::cleave;
                creators["concussion blow"] = &AiObjectContextInternal::concussion_blow;
                creators["shield bash on enemy healer"] = &AiObjectContextInternal::shield_bash_on_enemy_healer;
            }

        private:
            static Action* devastate(PlayerbotAI* botAI) { return new CastDevastateAction(botAI); }
            static Action* last_stand(PlayerbotAI* botAI) { return new CastLastStandAction(botAI); }
            static Action* shockwave(PlayerbotAI* botAI) { return new CastShockwaveAction(botAI); }
            static Action* cleave(PlayerbotAI* botAI) { return new CastCleaveAction(botAI); }
            static Action* concussion_blow(PlayerbotAI* botAI) { return new CastConcussionBlowAction(botAI); }
            static Action* taunt(PlayerbotAI* botAI) { return new CastTauntAction(botAI); }
            static Action* revenge(PlayerbotAI* botAI) { return new CastRevengeAction(botAI); }
            static Action* slam(PlayerbotAI* botAI) { return new CastSlamAction(botAI); }
            static Action* shield_slam(PlayerbotAI* botAI) { return new CastShieldSlamAction(botAI); }
            static Action* disarm(PlayerbotAI* botAI) { return new CastDisarmAction(botAI); }
            static Action* sunder_armor(PlayerbotAI* botAI) { return new CastSunderArmorAction(botAI); }
            static Action* overpower(PlayerbotAI* botAI) { return new CastOverpowerAction(botAI); }
            static Action* charge(PlayerbotAI* botAI) { return new CastChargeAction(botAI); }
            static Action* bloodthirst(PlayerbotAI* botAI) { return new CastBloodthirstAction(botAI); }
            static Action* rend(PlayerbotAI* botAI) { return new CastRendAction(botAI); }
            static Action* rend_on_attacker(PlayerbotAI* botAI) { return new CastRendOnAttackerAction(botAI); }
            static Action* mocking_blow(PlayerbotAI* botAI) { return new CastMockingBlowAction(botAI); }
            static Action* death_wish(PlayerbotAI* botAI) { return new CastDeathWishAction(botAI); }
            static Action* berserker_rage(PlayerbotAI* botAI) { return new CastBerserkerRageAction(botAI); }
            static Action* victory_rush(PlayerbotAI* botAI) { return new CastVictoryRushAction(botAI); }
            static Action* execute(PlayerbotAI* botAI) { return new CastExecuteAction(botAI); }
            static Action* defensive_stance(PlayerbotAI* botAI) { return new CastDefensiveStanceAction(botAI); }
            static Action* hamstring(PlayerbotAI* botAI) { return new CastHamstringAction(botAI); }
            static Action* shield_bash(PlayerbotAI* botAI) { return new CastShieldBashAction(botAI); }
            static Action* shield_block(PlayerbotAI* botAI) { return new CastShieldBlockAction(botAI); }
            static Action* bloodrage(PlayerbotAI* botAI) { return new CastBloodrageAction(botAI); }
            static Action* battle_stance(PlayerbotAI* botAI) { return new CastBattleStanceAction(botAI); }
            static Action* heroic_strike(PlayerbotAI* botAI) { return new CastHeroicStrikeAction(botAI); }
            static Action* intimidating_shout(PlayerbotAI* botAI) { return new CastIntimidatingShoutAction(botAI); }
            static Action* demoralizing_shout(PlayerbotAI* botAI) { return new CastDemoralizingShoutAction(botAI); }
            static Action* challenging_shout(PlayerbotAI* botAI) { return new CastChallengingShoutAction(botAI); }
            static Action* shield_wall(PlayerbotAI* botAI) { return new CastShieldWallAction(botAI); }
            static Action* battle_shout(PlayerbotAI* botAI) { return new CastBattleShoutAction(botAI); }
            static Action* battle_shout_taunt(PlayerbotAI* botAI) { return new CastBattleShoutTauntAction(botAI); }
            static Action* thunder_clap(PlayerbotAI* botAI) { return new CastThunderClapAction(botAI); }
            static Action* shield_bash_on_enemy_healer(PlayerbotAI* botAI) { return new CastShieldBashOnEnemyHealerAction(botAI); }

        };
    };
};

WarriorAiObjectContext::WarriorAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new ai::warrior::StrategyFactoryInternal());
    strategyContexts.Add(new ai::warrior::CombatStrategyFactoryInternal());
    actionContexts.Add(new ai::warrior::AiObjectContextInternal());
    triggerContexts.Add(new ai::warrior::TriggerFactoryInternal());
}
