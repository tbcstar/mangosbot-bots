/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "WarriorAiObjectContext.h"
#include "DpsWarriorStrategy.h"
#include "GenericWarriorNonCombatStrategy.h"
#include "TankWarriorStrategy.h"
#include "WarriorActions.h"
#include "WarriorTriggers.h"
#include "../NamedObjectContext.h"
#include "../generic/PullStrategy.h"
#include "../../Playerbot.h"

class WarriorStrategyFactoryInternal : public NamedObjectContext<Strategy>
{
    public:
        WarriorStrategyFactoryInternal()
        {
            creators["nc"] = &WarriorStrategyFactoryInternal::nc;
            creators["pull"] = &WarriorStrategyFactoryInternal::pull;
            creators["aoe"] = &WarriorStrategyFactoryInternal::aoe;
        }

    private:
        static Strategy* nc(PlayerbotAI* botAI) { return new GenericWarriorNonCombatStrategy(botAI); }
        static Strategy* aoe(PlayerbotAI* botAI) { return new DpsWarrirorAoeStrategy(botAI); }
        static Strategy* pull(PlayerbotAI* botAI) { return new PullStrategy(botAI, "shoot"); }
};

class WarriorCombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
{
    public:
        WarriorCombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
        {
            creators["tank"] = &WarriorCombatStrategyFactoryInternal::tank;
            creators["dps"] = &WarriorCombatStrategyFactoryInternal::dps;
        }

    private:
        static Strategy* tank(PlayerbotAI* botAI) { return new TankWarriorStrategy(botAI); }
        static Strategy* dps(PlayerbotAI* botAI) { return new DpsWarriorStrategy(botAI); }
};

class WarriorTriggerFactoryInternal : public NamedObjectContext<Trigger>
{
    public:
        WarriorTriggerFactoryInternal()
        {
            creators["hamstring"] = &WarriorTriggerFactoryInternal::hamstring;
            creators["victory rush"] = &WarriorTriggerFactoryInternal::victory_rush;
            creators["death wish"] = &WarriorTriggerFactoryInternal::death_wish;
            creators["battle shout"] = &WarriorTriggerFactoryInternal::battle_shout;
            creators["rend"] = &WarriorTriggerFactoryInternal::rend;
            creators["rend on attacker"] = &WarriorTriggerFactoryInternal::rend_on_attacker;
            creators["bloodrage"] = &WarriorTriggerFactoryInternal::bloodrage;
            creators["shield bash"] = &WarriorTriggerFactoryInternal::shield_bash;
            creators["disarm"] = &WarriorTriggerFactoryInternal::disarm;
            creators["concussion blow"] = &WarriorTriggerFactoryInternal::concussion_blow;
            creators["sword and board"] = &WarriorTriggerFactoryInternal::SwordAndBoard;
            creators["shield bash on enemy healer"] = &WarriorTriggerFactoryInternal::shield_bash_on_enemy_healer;
            creators["battle stance"] = &WarriorTriggerFactoryInternal::battle_stance;
            creators["defensive stance"] = &WarriorTriggerFactoryInternal::defensive_stance;
            creators["shield block"] = &WarriorTriggerFactoryInternal::shield_block;

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


class WarriorAiObjectContextInternal : public NamedObjectContext<Action>
{
    public:
        WarriorAiObjectContextInternal()
        {
            creators["devastate"] = &WarriorAiObjectContextInternal::devastate;
            creators["overpower"] = &WarriorAiObjectContextInternal::overpower;
            creators["charge"] = &WarriorAiObjectContextInternal::charge;
            creators["bloodthirst"] = &WarriorAiObjectContextInternal::bloodthirst;
            creators["rend"] = &WarriorAiObjectContextInternal::rend;
            creators["rend on attacker"] = &WarriorAiObjectContextInternal::rend_on_attacker;
            creators["mocking blow"] = &WarriorAiObjectContextInternal::mocking_blow;
            creators["death wish"] = &WarriorAiObjectContextInternal::death_wish;
            creators["berserker rage"] = &WarriorAiObjectContextInternal::berserker_rage;
            creators["victory rush"] = &WarriorAiObjectContextInternal::victory_rush;
            creators["execute"] = &WarriorAiObjectContextInternal::execute;
            creators["defensive stance"] = &WarriorAiObjectContextInternal::defensive_stance;
            creators["hamstring"] = &WarriorAiObjectContextInternal::hamstring;
            creators["shield bash"] = &WarriorAiObjectContextInternal::shield_bash;
            creators["shield block"] = &WarriorAiObjectContextInternal::shield_block;
            creators["bloodrage"] = &WarriorAiObjectContextInternal::bloodrage;
            creators["battle stance"] = &WarriorAiObjectContextInternal::battle_stance;
            creators["heroic strike"] = &WarriorAiObjectContextInternal::heroic_strike;
            creators["intimidating shout"] = &WarriorAiObjectContextInternal::intimidating_shout;
            creators["demoralizing shout"] = &WarriorAiObjectContextInternal::demoralizing_shout;
            creators["challenging shout"] = &WarriorAiObjectContextInternal::challenging_shout;
            creators["shield wall"] = &WarriorAiObjectContextInternal::shield_wall;
            creators["battle shout"] = &WarriorAiObjectContextInternal::battle_shout;
            creators["battle shout taunt"] = &WarriorAiObjectContextInternal::battle_shout_taunt;
            creators["thunder clap"] = &WarriorAiObjectContextInternal::thunder_clap;
            creators["taunt"] = &WarriorAiObjectContextInternal::taunt;
            creators["revenge"] = &WarriorAiObjectContextInternal::revenge;
            creators["slam"] = &WarriorAiObjectContextInternal::slam;
            creators["shield slam"] = &WarriorAiObjectContextInternal::shield_slam;
            creators["disarm"] = &WarriorAiObjectContextInternal::disarm;
            creators["sunder armor"] = &WarriorAiObjectContextInternal::sunder_armor;
            creators["last stand"] = &WarriorAiObjectContextInternal::last_stand;
            creators["shockwave"] = &WarriorAiObjectContextInternal::shockwave;
            creators["cleave"] = &WarriorAiObjectContextInternal::cleave;
            creators["concussion blow"] = &WarriorAiObjectContextInternal::concussion_blow;
            creators["shield bash on enemy healer"] = &WarriorAiObjectContextInternal::shield_bash_on_enemy_healer;
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

WarriorAiObjectContext::WarriorAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new WarriorStrategyFactoryInternal());
    strategyContexts.Add(new WarriorCombatStrategyFactoryInternal());
    actionContexts.Add(new WarriorAiObjectContextInternal());
    triggerContexts.Add(new WarriorTriggerFactoryInternal());
}
