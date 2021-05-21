/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "DruidAiObjectContext.h"
#include "BearTankDruidStrategy.h"
#include "CatDpsDruidStrategy.h"
#include "CasterDruidStrategy.h"
#include "GenericDruidNonCombatStrategy.h"
#include "DruidActions.h"
#include "DruidTriggers.h"
#include "HealDruidStrategy.h"
#include "MeleeDruidStrategy.h"
#include "../../Playerbot.h"

class StrategyFactoryInternal : public NamedObjectContext<Strategy>
{
    public:
        StrategyFactoryInternal()
        {
            creators["nc"] = &StrategyFactoryInternal::nc;
            creators["cat aoe"] = &StrategyFactoryInternal::cat_aoe;
            creators["caster aoe"] = &StrategyFactoryInternal::caster_aoe;
            creators["caster debuff"] = &StrategyFactoryInternal::caster_debuff;
            creators["dps debuff"] = &StrategyFactoryInternal::caster_debuff;
            creators["cure"] = &StrategyFactoryInternal::cure;
            creators["melee"] = &StrategyFactoryInternal::melee;
            creators["buff"] = &StrategyFactoryInternal::buff;
            creators["boost"] = &StrategyFactoryInternal::boost;
            creators["cc"] = &StrategyFactoryInternal::cc;
        }

    private:
        static Strategy* nc(PlayerbotAI* botAI) { return new GenericDruidNonCombatStrategy(botAI); }
        static Strategy* cat_aoe(PlayerbotAI* botAI) { return new CatAoeDruidStrategy(botAI); }
        static Strategy* caster_aoe(PlayerbotAI* botAI) { return new CasterDruidAoeStrategy(botAI); }
        static Strategy* caster_debuff(PlayerbotAI* botAI) { return new CasterDruidDebuffStrategy(botAI); }
        static Strategy* cure(PlayerbotAI* botAI) { return new DruidCureStrategy(botAI); }
        static Strategy* melee(PlayerbotAI* botAI) { return new MeleeDruidStrategy(botAI); }
        static Strategy* buff(PlayerbotAI* botAI) { return new GenericDruidBuffStrategy(botAI); }
        static Strategy* boost(PlayerbotAI* botAI) { return new DruidBoostStrategy(botAI); }
        static Strategy* cc(PlayerbotAI* botAI) { return new DruidCcStrategy(botAI); }
};

class DruidStrategyFactoryInternal : public NamedObjectContext<Strategy>
{
    public:
        DruidStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
        {
            creators["bear"] = &DruidStrategyFactoryInternal::bear;
            creators["tank"] = &DruidStrategyFactoryInternal::bear;
            creators["cat"] = &DruidStrategyFactoryInternal::cat;
            creators["caster"] = &DruidStrategyFactoryInternal::caster;
            creators["dps"] = &DruidStrategyFactoryInternal::cat;
            creators["heal"] = &DruidStrategyFactoryInternal::heal;
        }

    private:
        static Strategy* bear(PlayerbotAI* botAI) { return new BearTankDruidStrategy(botAI); }
        static Strategy* cat(PlayerbotAI* botAI) { return new CatDpsDruidStrategy(botAI); }
        static Strategy* caster(PlayerbotAI* botAI) { return new CasterDruidStrategy(botAI); }
        static Strategy* heal(PlayerbotAI* botAI) { return new HealDruidStrategy(botAI); }
};

class TriggerFactoryInternal : public NamedObjectContext<Trigger>
{
    public:
        TriggerFactoryInternal()
        {
            creators["omen of clarity"] = &TriggerFactoryInternal::omen_of_clarity;
            creators["thorns"] = &TriggerFactoryInternal::Thorns;
            creators["bash"] = &TriggerFactoryInternal::bash;
            creators["faerie fire (feral)"] = &TriggerFactoryInternal::faerie_fire_feral;
            creators["faerie fire"] = &TriggerFactoryInternal::faerie_fire;
            creators["insect swarm"] = &TriggerFactoryInternal::insect_swarm;
            creators["moonfire"] = &TriggerFactoryInternal::moonfire;
            creators["nature's grasp"] = &TriggerFactoryInternal::natures_grasp;
            creators["tiger's fury"] = &TriggerFactoryInternal::tigers_fury;
            creators["rake"] = &TriggerFactoryInternal::rake;
            creators["mark of the wild"] = &TriggerFactoryInternal::mark_of_the_wild;
            creators["mark of the wild on party"] = &TriggerFactoryInternal::mark_of_the_wild_on_party;
            creators["cure poison"] = &TriggerFactoryInternal::cure_poison;
            creators["party member cure poison"] = &TriggerFactoryInternal::party_member_cure_poison;
            creators["entangling roots"] = &TriggerFactoryInternal::entangling_roots;
            creators["hibernate"] = &TriggerFactoryInternal::hibernate;
            creators["bear form"] = &TriggerFactoryInternal::bear_form;
            creators["cat form"] = &TriggerFactoryInternal::cat_form;
            creators["tree form"] = &TriggerFactoryInternal::tree_form;
            creators["eclipse (solar)"] = &TriggerFactoryInternal::eclipse_solar;
            creators["eclipse (lunar)"] = &TriggerFactoryInternal::eclipse_lunar;
            creators["bash on enemy healer"] = &TriggerFactoryInternal::bash_on_enemy_healer;
            creators["nature's swiftness"] = &TriggerFactoryInternal::natures_swiftness;
        }

    private:
        static Trigger* natures_swiftness(PlayerbotAI* botAI) { return new NaturesSwiftnessTrigger(botAI); }
        static Trigger* eclipse_solar(PlayerbotAI* botAI) { return new EclipseSolarTrigger(botAI); }
        static Trigger* eclipse_lunar(PlayerbotAI* botAI) { return new EclipseLunarTrigger(botAI); }
        static Trigger* Thorns(PlayerbotAI* botAI) { return new ThornsTrigger(botAI); }
        static Trigger* bash(PlayerbotAI* botAI) { return new BashInterruptSpellTrigger(botAI); }
        static Trigger* faerie_fire_feral(PlayerbotAI* botAI) { return new FaerieFireFeralTrigger(botAI); }
        static Trigger* insect_swarm(PlayerbotAI* botAI) { return new InsectSwarmTrigger(botAI); }
        static Trigger* moonfire(PlayerbotAI* botAI) { return new MoonfireTrigger(botAI); }
        static Trigger* faerie_fire(PlayerbotAI* botAI) { return new FaerieFireTrigger(botAI); }
        static Trigger* natures_grasp(PlayerbotAI* botAI) { return new NaturesGraspTrigger(botAI); }
        static Trigger* tigers_fury(PlayerbotAI* botAI) { return new TigersFuryTrigger(botAI); }
        static Trigger* rake(PlayerbotAI* botAI) { return new RakeTrigger(botAI); }
        static Trigger* mark_of_the_wild(PlayerbotAI* botAI) { return new MarkOfTheWildTrigger(botAI); }
        static Trigger* mark_of_the_wild_on_party(PlayerbotAI* botAI) { return new MarkOfTheWildOnPartyTrigger(botAI); }
        static Trigger* cure_poison(PlayerbotAI* botAI) { return new CurePoisonTrigger(botAI); }
        static Trigger* party_member_cure_poison(PlayerbotAI* botAI) { return new PartyMemberCurePoisonTrigger(botAI); }
        static Trigger* entangling_roots(PlayerbotAI* botAI) { return new EntanglingRootsTrigger(botAI); }
        static Trigger* hibernate(PlayerbotAI* botAI) { return new HibernateTrigger(botAI); }
        static Trigger* bear_form(PlayerbotAI* botAI) { return new BearFormTrigger(botAI); }
        static Trigger* cat_form(PlayerbotAI* botAI) { return new CatFormTrigger(botAI); }
        static Trigger* tree_form(PlayerbotAI* botAI) { return new TreeFormTrigger(botAI); }
        static Trigger* bash_on_enemy_healer(PlayerbotAI* botAI) { return new BashInterruptEnemyHealerSpellTrigger(botAI); }
        static Trigger* omen_of_clarity(PlayerbotAI* botAI) { return new OmenOfClarityTrigger(botAI); }
};

class AiObjectContextInternal : public NamedObjectContext<Action>
{
    public:
        AiObjectContextInternal()
        {
            creators["feral charge - bear"] = &AiObjectContextInternal::feral_charge_bear;
            creators["feral charge - cat"] = &AiObjectContextInternal::feral_charge_cat;
            creators["swipe (bear)"] = &AiObjectContextInternal::swipe_bear;
            creators["faerie fire (feral)"] = &AiObjectContextInternal::faerie_fire_feral;
            creators["faerie fire"] = &AiObjectContextInternal::faerie_fire;
            creators["bear form"] = &AiObjectContextInternal::bear_form;
            creators["dire bear form"] = &AiObjectContextInternal::dire_bear_form;
            creators["moonkin form"] = &AiObjectContextInternal::moonkin_form;
            creators["cat form"] = &AiObjectContextInternal::cat_form;
            creators["tree form"] = &AiObjectContextInternal::tree_form;
            creators["caster form"] = &AiObjectContextInternal::caster_form;
            creators["mangle (bear)"] = &AiObjectContextInternal::mangle_bear;
            creators["maul"] = &AiObjectContextInternal::maul;
            creators["bash"] = &AiObjectContextInternal::bash;
            creators["swipe"] = &AiObjectContextInternal::swipe;
            creators["growl"] = &AiObjectContextInternal::growl;
            creators["demoralizing roar"] = &AiObjectContextInternal::demoralizing_roar;
            creators["hibernate"] = &AiObjectContextInternal::hibernate;
            creators["entangling roots"] = &AiObjectContextInternal::entangling_roots;
            creators["entangling roots on cc"] = &AiObjectContextInternal::entangling_roots_on_cc;
            creators["hibernate"] = &AiObjectContextInternal::hibernate;
            creators["hibernate on cc"] = &AiObjectContextInternal::hibernate_on_cc;
            creators["wrath"] = &AiObjectContextInternal::wrath;
            creators["starfall"] = &AiObjectContextInternal::starfall;
            creators["insect swarm"] = &AiObjectContextInternal::insect_swarm;
            creators["moonfire"] = &AiObjectContextInternal::moonfire;
            creators["starfire"] = &AiObjectContextInternal::starfire;
            creators["nature's grasp"] = &AiObjectContextInternal::natures_grasp;
            creators["claw"] = &AiObjectContextInternal::claw;
            creators["mangle (cat)"] = &AiObjectContextInternal::mangle_cat;
            creators["swipe (cat)"] = &AiObjectContextInternal::swipe_cat;
            creators["rake"] = &AiObjectContextInternal::rake;
            creators["ferocious bite"] = &AiObjectContextInternal::ferocious_bite;
            creators["rip"] = &AiObjectContextInternal::rip;
            creators["cower"] = &AiObjectContextInternal::cower;
            creators["survival instincts"] = &AiObjectContextInternal::survival_instincts;
            creators["thorns"] = &AiObjectContextInternal::thorns;
            creators["cure poison"] = &AiObjectContextInternal::cure_poison;
            creators["cure poison on party"] = &AiObjectContextInternal::cure_poison_on_party;
            creators["abolish poison"] = &AiObjectContextInternal::abolish_poison;
            creators["abolish poison on party"] = &AiObjectContextInternal::abolish_poison_on_party;
            creators["berserk"] = &AiObjectContextInternal::berserk;
            creators["tiger's fury"] = &AiObjectContextInternal::tigers_fury;
            creators["mark of the wild"] = &AiObjectContextInternal::mark_of_the_wild;
            creators["mark of the wild on party"] = &AiObjectContextInternal::mark_of_the_wild_on_party;
            creators["regrowth"] = &AiObjectContextInternal::regrowth;
            creators["rejuvenation"] = &AiObjectContextInternal::rejuvenation;
            creators["healing touch"] = &AiObjectContextInternal::healing_touch;
            creators["regrowth on party"] = &AiObjectContextInternal::regrowth_on_party;
            creators["rejuvenation on party"] = &AiObjectContextInternal::rejuvenation_on_party;
            creators["healing touch on party"] = &AiObjectContextInternal::healing_touch_on_party;
            creators["rebirth"] = &AiObjectContextInternal::rebirth;
            creators["revive"] = &AiObjectContextInternal::revive;
            creators["barskin"] = &AiObjectContextInternal::barskin;
            creators["lacerate"] = &AiObjectContextInternal::lacerate;
            creators["hurricane"] = &AiObjectContextInternal::hurricane;
            creators["innervate"] = &AiObjectContextInternal::innervate;
            creators["tranquility"] = &AiObjectContextInternal::tranquility;
            creators["bash on enemy healer"] = &AiObjectContextInternal::bash_on_enemy_healer;
            creators["omen of clarity"] = &AiObjectContextInternal::omen_of_clarity;
            creators["nature's swiftness"] = &AiObjectContextInternal::natures_swiftness;
        }

    private:
        static Action* natures_swiftness(PlayerbotAI* botAI) { return new CastNaturesSwiftnessAction(botAI); }
        static Action* omen_of_clarity(PlayerbotAI* botAI) { return new CastOmenOfClarityAction(botAI); }
        static Action* tranquility(PlayerbotAI* botAI) { return new CastTranquilityAction(botAI); }
        static Action* feral_charge_bear(PlayerbotAI* botAI) { return new CastFeralChargeBearAction(botAI); }
        static Action* feral_charge_cat(PlayerbotAI* botAI) { return new CastFeralChargeCatAction(botAI); }
        static Action* swipe_bear(PlayerbotAI* botAI) { return new CastSwipeBearAction(botAI); }
        static Action* faerie_fire_feral(PlayerbotAI* botAI) { return new CastFaerieFireFeralAction(botAI); }
        static Action* faerie_fire(PlayerbotAI* botAI) { return new CastFaerieFireAction(botAI); }
        static Action* bear_form(PlayerbotAI* botAI) { return new CastBearFormAction(botAI); }
        static Action* dire_bear_form(PlayerbotAI* botAI) { return new CastDireBearFormAction(botAI); }
        static Action* cat_form(PlayerbotAI* botAI) { return new CastCatFormAction(botAI); }
        static Action* tree_form(PlayerbotAI* botAI) { return new CastTreeFormAction(botAI); }
        static Action* caster_form(PlayerbotAI* botAI) { return new CastCasterFormAction(botAI); }
        static Action* mangle_bear(PlayerbotAI* botAI) { return new CastMangleBearAction(botAI); }
        static Action* maul(PlayerbotAI* botAI) { return new CastMaulAction(botAI); }
        static Action* bash(PlayerbotAI* botAI) { return new CastBashAction(botAI); }
        static Action* swipe(PlayerbotAI* botAI) { return new CastSwipeAction(botAI); }
        static Action* growl(PlayerbotAI* botAI) { return new CastGrowlAction(botAI); }
        static Action* demoralizing_roar(PlayerbotAI* botAI) { return new CastDemoralizingRoarAction(botAI); }
        static Action* moonkin_form(PlayerbotAI* botAI) { return new CastMoonkinFormAction(botAI); }
        static Action* hibernate(PlayerbotAI* botAI) { return new CastHibernateAction(botAI); }
        static Action* entangling_roots(PlayerbotAI* botAI) { return new CastEntanglingRootsAction(botAI); }
        static Action* hibernate_on_cc(PlayerbotAI* botAI) { return new CastHibernateCcAction(botAI); }
        static Action* entangling_roots_on_cc(PlayerbotAI* botAI) { return new CastEntanglingRootsCcAction(botAI); }
        static Action* wrath(PlayerbotAI* botAI) { return new CastWrathAction(botAI); }
        static Action* starfall(PlayerbotAI* botAI) { return new CastStarfallAction(botAI); }
        static Action* insect_swarm(PlayerbotAI* botAI) { return new CastInsectSwarmAction(botAI); }
        static Action* moonfire(PlayerbotAI* botAI) { return new CastMoonfireAction(botAI); }
        static Action* starfire(PlayerbotAI* botAI) { return new CastStarfireAction(botAI); }
        static Action* natures_grasp(PlayerbotAI* botAI) { return new CastNaturesGraspAction(botAI); }
        static Action* claw(PlayerbotAI* botAI) { return new CastClawAction(botAI); }
        static Action* mangle_cat(PlayerbotAI* botAI) { return new CastMangleCatAction(botAI); }
        static Action* swipe_cat(PlayerbotAI* botAI) { return new CastSwipeCatAction(botAI); }
        static Action* rake(PlayerbotAI* botAI) { return new CastRakeAction(botAI); }
        static Action* ferocious_bite(PlayerbotAI* botAI) { return new CastFerociousBiteAction(botAI); }
        static Action* rip(PlayerbotAI* botAI) { return new CastRipAction(botAI); }
        static Action* cower(PlayerbotAI* botAI) { return new CastCowerAction(botAI); }
        static Action* survival_instincts(PlayerbotAI* botAI) { return new CastSurvivalInstinctsAction(botAI); }
        static Action* thorns(PlayerbotAI* botAI) { return new CastThornsAction(botAI); }
        static Action* cure_poison(PlayerbotAI* botAI) { return new CastCurePoisonAction(botAI); }
        static Action* cure_poison_on_party(PlayerbotAI* botAI) { return new CastCurePoisonOnPartyAction(botAI); }
        static Action* abolish_poison(PlayerbotAI* botAI) { return new CastAbolishPoisonAction(botAI); }
        static Action* abolish_poison_on_party(PlayerbotAI* botAI) { return new CastAbolishPoisonOnPartyAction(botAI); }
        static Action* berserk(PlayerbotAI* botAI) { return new CastBerserkAction(botAI); }
        static Action* tigers_fury(PlayerbotAI* botAI) { return new CastTigersFuryAction(botAI); }
        static Action* mark_of_the_wild(PlayerbotAI* botAI) { return new CastMarkOfTheWildAction(botAI); }
        static Action* mark_of_the_wild_on_party(PlayerbotAI* botAI) { return new CastMarkOfTheWildOnPartyAction(botAI); }
        static Action* regrowth(PlayerbotAI* botAI) { return new CastRegrowthAction(botAI); }
        static Action* rejuvenation(PlayerbotAI* botAI) { return new CastRejuvenationAction(botAI); }
        static Action* healing_touch(PlayerbotAI* botAI) { return new CastHealingTouchAction(botAI); }
        static Action* regrowth_on_party(PlayerbotAI* botAI) { return new CastRegrowthOnPartyAction(botAI); }
        static Action* rejuvenation_on_party(PlayerbotAI* botAI) { return new CastRejuvenationOnPartyAction(botAI); }
        static Action* healing_touch_on_party(PlayerbotAI* botAI) { return new CastHealingTouchOnPartyAction(botAI); }
        static Action* rebirth(PlayerbotAI* botAI) { return new CastRebirthAction(botAI); }
        static Action* revive(PlayerbotAI* botAI) { return new CastReviveAction(botAI); }
        static Action* barskin(PlayerbotAI* botAI) { return new CastBarskinAction(botAI); }
        static Action* lacerate(PlayerbotAI* botAI) { return new CastLacerateAction(botAI); }
        static Action* hurricane(PlayerbotAI* botAI) { return new CastHurricaneAction(botAI); }
        static Action* innervate(PlayerbotAI* botAI) { return new CastInnervateAction(botAI); }
        static Action* bash_on_enemy_healer(PlayerbotAI* botAI) { return new CastBashOnEnemyHealerAction(botAI); }
};

DruidAiObjectContext::DruidAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new StrategyFactoryInternal());
    strategyContexts.Add(new DruidStrategyFactoryInternal());
    actionContexts.Add(new AiObjectContextInternal());
    triggerContexts.Add(new TriggerFactoryInternal());
}
