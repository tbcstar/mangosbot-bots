/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PriestAiObjectContext.h"
#include "HolyPriestStrategy.h"
#include "PriestActions.h"
#include "PriestNonCombatStrategy.h"
#include "PriestTriggers.h"
#include "ShadowPriestStrategy.h"
#include "NamedObjectContext.h"
#include "PullStrategy.h"
#include "Playerbot.h"

class PriestStrategyFactoryInternal : public NamedObjectContext<Strategy>
{
    public:
        PriestStrategyFactoryInternal()
        {
            creators["nc"] = &PriestStrategyFactoryInternal::nc;
            creators["pull"] = &PriestStrategyFactoryInternal::pull;
            creators["aoe"] = &PriestStrategyFactoryInternal::shadow_aoe;
            creators["shadow aoe"] = &PriestStrategyFactoryInternal::shadow_aoe;
            creators["dps debuff"] = &PriestStrategyFactoryInternal::shadow_debuff;
            creators["shadow debuff"] = &PriestStrategyFactoryInternal::shadow_debuff;
            creators["cure"] = &PriestStrategyFactoryInternal::cure;
            creators["buff"] = &PriestStrategyFactoryInternal::buff;
            creators["boost"] = &PriestStrategyFactoryInternal::boost;
            creators["rshadow"] = &PriestStrategyFactoryInternal::rshadow;
            creators["cc"] = &PriestStrategyFactoryInternal::cc;
        }

    private:
        static Strategy* cc(PlayerbotAI* botAI) { return new PriestCcStrategy(botAI); }
        static Strategy* rshadow(PlayerbotAI* botAI) { return new PriestShadowResistanceStrategy(botAI); }
        static Strategy* boost(PlayerbotAI* botAI) { return new PriestBoostStrategy(botAI); }
        static Strategy* buff(PlayerbotAI* botAI) { return new PriestBuffStrategy(botAI); }
        static Strategy* nc(PlayerbotAI* botAI) { return new PriestNonCombatStrategy(botAI); }
        static Strategy* shadow_aoe(PlayerbotAI* botAI) { return new ShadowPriestAoeStrategy(botAI); }
        static Strategy* pull(PlayerbotAI* botAI) { return new PullStrategy(botAI, "shoot"); }
        static Strategy* shadow_debuff(PlayerbotAI* botAI) { return new ShadowPriestDebuffStrategy(botAI); }
        static Strategy* cure(PlayerbotAI* botAI) { return new PriestCureStrategy(botAI); }
};

class PriestCombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
{
    public:
        PriestCombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
        {
            creators["heal"] = &PriestCombatStrategyFactoryInternal::heal;
            creators["shadow"] = &PriestCombatStrategyFactoryInternal::dps;
            creators["dps"] = &PriestCombatStrategyFactoryInternal::dps;
            creators["holy"] = &PriestCombatStrategyFactoryInternal::holy;
        }

    private:
        static Strategy* heal(PlayerbotAI* botAI) { return new HealPriestStrategy(botAI); }
        static Strategy* dps(PlayerbotAI* botAI) { return new ShadowPriestStrategy(botAI); }
        static Strategy* holy(PlayerbotAI* botAI) { return new HolyPriestStrategy(botAI); }
};

class PriestTriggerFactoryInternal : public NamedObjectContext<Trigger>
{
    public:
        PriestTriggerFactoryInternal()
        {
            creators["devouring plague"] = &PriestTriggerFactoryInternal::devouring_plague;
            creators["shadow word: pain"] = &PriestTriggerFactoryInternal::shadow_word_pain;
            creators["shadow word: pain on attacker"] = &PriestTriggerFactoryInternal::shadow_word_pain_on_attacker;
            creators["dispel magic"] = &PriestTriggerFactoryInternal::dispel_magic;
            creators["dispel magic on party"] = &PriestTriggerFactoryInternal::dispel_magic_party_member;
            creators["cure disease"] = &PriestTriggerFactoryInternal::cure_disease;
            creators["party member cure disease"] = &PriestTriggerFactoryInternal::party_member_cure_disease;
            creators["power word: fortitude"] = &PriestTriggerFactoryInternal::power_word_fortitude;
            creators["power word: fortitude on party"] = &PriestTriggerFactoryInternal::power_word_fortitude_on_party;
            creators["divine spirit"] = &PriestTriggerFactoryInternal::divine_spirit;
            creators["divine spirit on party"] = &PriestTriggerFactoryInternal::divine_spirit_on_party;
            creators["inner fire"] = &PriestTriggerFactoryInternal::inner_fire;
            creators["vampiric touch"] = &PriestTriggerFactoryInternal::vampiric_touch;
            creators["shadowform"] = &PriestTriggerFactoryInternal::shadowform;
            creators["vampiric embrace"] = &PriestTriggerFactoryInternal::vampiric_embrace;
            creators["power infusion"] = &PriestTriggerFactoryInternal::power_infusion;
            creators["inner focus"] = &PriestTriggerFactoryInternal::inner_focus;
            creators["shadow protection"] = &PriestTriggerFactoryInternal::shadow_protection;
            creators["shadow protection on party"] = &PriestTriggerFactoryInternal::shadow_protection_on_party;
            creators["shackle undead"] = &PriestTriggerFactoryInternal::shackle_undead;
            creators["prayer of fortitude on party"] = &PriestTriggerFactoryInternal::prayer_of_fortitude_on_party;
            creators["prayer of spirit on party"] = &PriestTriggerFactoryInternal::prayer_of_spirit_on_party;
        }

    private:
        static Trigger* vampiric_embrace(PlayerbotAI* botAI) { return new VampiricEmbraceTrigger(botAI); }
        static Trigger* shadowform(PlayerbotAI* botAI) { return new ShadowformTrigger(botAI); }
        static Trigger* vampiric_touch(PlayerbotAI* botAI) { return new VampiricTouchTrigger(botAI); }
        static Trigger* devouring_plague(PlayerbotAI* botAI) { return new DevouringPlagueTrigger(botAI); }
        static Trigger* shadow_word_pain(PlayerbotAI* botAI) { return new PowerWordPainTrigger(botAI); }
        static Trigger* shadow_word_pain_on_attacker(PlayerbotAI* botAI) { return new PowerWordPainOnAttackerTrigger(botAI); }
        static Trigger* dispel_magic(PlayerbotAI* botAI) { return new DispelMagicTrigger(botAI); }
        static Trigger* dispel_magic_party_member(PlayerbotAI* botAI) { return new DispelMagicPartyMemberTrigger(botAI); }
        static Trigger* cure_disease(PlayerbotAI* botAI) { return new CureDiseaseTrigger(botAI); }
        static Trigger* party_member_cure_disease(PlayerbotAI* botAI) { return new PartyMemberCureDiseaseTrigger(botAI); }
        static Trigger* power_word_fortitude(PlayerbotAI* botAI) { return new PowerWordFortitudeTrigger(botAI); }
        static Trigger* power_word_fortitude_on_party(PlayerbotAI* botAI) { return new PowerWordFortitudeOnPartyTrigger(botAI); }
        static Trigger* divine_spirit(PlayerbotAI* botAI) { return new DivineSpiritTrigger(botAI); }
        static Trigger* divine_spirit_on_party(PlayerbotAI* botAI) { return new DivineSpiritOnPartyTrigger(botAI); }
        static Trigger* inner_fire(PlayerbotAI* botAI) { return new InnerFireTrigger(botAI); }
        static Trigger* power_infusion(PlayerbotAI* botAI) { return new PowerInfusionTrigger(botAI); }
        static Trigger* inner_focus(PlayerbotAI* botAI) { return new InnerFocusTrigger(botAI); }
        static Trigger* shadow_protection_on_party(PlayerbotAI* botAI) { return new ShadowProtectionOnPartyTrigger(botAI); }
        static Trigger* shadow_protection(PlayerbotAI* botAI) { return new ShadowProtectionTrigger(botAI); }
        static Trigger* shackle_undead(PlayerbotAI* botAI) { return new ShackleUndeadTrigger(botAI); }
        static Trigger* prayer_of_fortitude_on_party(PlayerbotAI* botAI) { return new PrayerOfFortitudeTrigger(botAI); }
        static Trigger* prayer_of_spirit_on_party(PlayerbotAI* botAI) { return new PrayerOfSpiritTrigger(botAI); }
};

class PriestAiObjectContextInternal : public NamedObjectContext<Action>
{
    public:
        PriestAiObjectContextInternal()
        {
            creators["power infusion"] = &PriestAiObjectContextInternal::power_infusion;
            creators["inner focus"] = &PriestAiObjectContextInternal::inner_focus;
            creators["shadow word: pain"] = &PriestAiObjectContextInternal::shadow_word_pain;
            creators["shadow word: pain on attacker"] = &PriestAiObjectContextInternal::shadow_word_pain_on_attacker;
            creators["devouring plague"] = &PriestAiObjectContextInternal::devouring_plague;
            creators["mind flay"] = &PriestAiObjectContextInternal::mind_flay;
            creators["holy fire"] = &PriestAiObjectContextInternal::holy_fire;
            creators["smite"] = &PriestAiObjectContextInternal::smite;
            creators["mind blast"] = &PriestAiObjectContextInternal::mind_blast;
            creators["shadowform"] = &PriestAiObjectContextInternal::shadowform;
            creators["remove shadowform"] = &PriestAiObjectContextInternal::remove_shadowform;
            creators["holy nova"] = &PriestAiObjectContextInternal::holy_nova;
            creators["power word: fortitude"] = &PriestAiObjectContextInternal::power_word_fortitude;
            creators["power word: fortitude on party"] = &PriestAiObjectContextInternal::power_word_fortitude_on_party;
            creators["divine spirit"] = &PriestAiObjectContextInternal::divine_spirit;
            creators["divine spirit on party"] = &PriestAiObjectContextInternal::divine_spirit_on_party;
            creators["power word: shield"] = &PriestAiObjectContextInternal::power_word_shield;
            creators["power word: shield on party"] = &PriestAiObjectContextInternal::power_word_shield_on_party;
            creators["renew"] = &PriestAiObjectContextInternal::renew;
            creators["renew on party"] = &PriestAiObjectContextInternal::renew_on_party;
            creators["greater heal"] = &PriestAiObjectContextInternal::greater_heal;
            creators["greater heal on party"] = &PriestAiObjectContextInternal::greater_heal_on_party;
            creators["heal"] = &PriestAiObjectContextInternal::heal;
            creators["heal on party"] = &PriestAiObjectContextInternal::heal_on_party;
            creators["lesser heal"] = &PriestAiObjectContextInternal::lesser_heal;
            creators["lesser heal on party"] = &PriestAiObjectContextInternal::lesser_heal_on_party;
            creators["flash heal"] = &PriestAiObjectContextInternal::flash_heal;
            creators["flash heal on party"] = &PriestAiObjectContextInternal::flash_heal_on_party;
            creators["dispel magic"] = &PriestAiObjectContextInternal::dispel_magic;
            creators["dispel magic on party"] = &PriestAiObjectContextInternal::dispel_magic_on_party;
            creators["dispel magic on target"] = &PriestAiObjectContextInternal::dispel_magic_on_target;
            creators["cure disease"] = &PriestAiObjectContextInternal::cure_disease;
            creators["cure disease on party"] = &PriestAiObjectContextInternal::cure_disease_on_party;
            creators["abolish disease"] = &PriestAiObjectContextInternal::abolish_disease;
            creators["abolish disease on party"] = &PriestAiObjectContextInternal::abolish_disease_on_party;
            creators["fade"] = &PriestAiObjectContextInternal::fade;
            creators["inner fire"] = &PriestAiObjectContextInternal::inner_fire;
            creators["resurrection"] = &PriestAiObjectContextInternal::resurrection;
            creators["circle of healing"] = &PriestAiObjectContextInternal::circle_of_healing;
            creators["psychic scream"] = &PriestAiObjectContextInternal::psychic_scream;
            creators["vampiric touch"] = &PriestAiObjectContextInternal::vampiric_touch;
            creators["vampiric embrace"] = &PriestAiObjectContextInternal::vampiric_embrace;
            creators["dispersion"] = &PriestAiObjectContextInternal::dispersion;
            creators["shadow protection"] = &PriestAiObjectContextInternal::shadow_protection;
            creators["shadow protection on party"] = &PriestAiObjectContextInternal::shadow_protection_on_party;
            creators["shackle undead"] = &PriestAiObjectContextInternal::shackle_undead;
            creators["prayer of fortitude on party"] = &PriestAiObjectContextInternal::prayer_of_fortitude_on_party;
            creators["prayer of spirit on party"] = &PriestAiObjectContextInternal::prayer_of_spirit_on_party;
        }

    private:
        static Action* shadow_protection_on_party(PlayerbotAI* botAI) { return new CastShadowProtectionOnPartyAction(botAI); }
        static Action* shadow_protection(PlayerbotAI* botAI) { return new CastShadowProtectionAction(botAI); }
        static Action* power_infusion(PlayerbotAI* botAI) { return new CastPowerInfusionAction(botAI); }
        static Action* inner_focus(PlayerbotAI* botAI) { return new CastInnerFocusAction(botAI); }
        static Action* dispersion(PlayerbotAI* botAI) { return new CastDispersionAction(botAI); }
        static Action* vampiric_embrace(PlayerbotAI* botAI) { return new CastVampiricEmbraceAction(botAI); }
        static Action* vampiric_touch(PlayerbotAI* botAI) { return new CastVampiricTouchAction(botAI); }
        static Action* psychic_scream(PlayerbotAI* botAI) { return new CastPsychicScreamAction(botAI); }
        static Action* circle_of_healing(PlayerbotAI* botAI) { return new CastCircleOfHealingAction(botAI); }
        static Action* resurrection(PlayerbotAI* botAI) { return new CastResurrectionAction(botAI); }
        static Action* shadow_word_pain(PlayerbotAI* botAI) { return new CastPowerWordPainAction(botAI); }
        static Action* shadow_word_pain_on_attacker(PlayerbotAI* botAI) { return new CastPowerWordPainOnAttackerAction(botAI); }
        static Action* devouring_plague(PlayerbotAI* botAI) { return new CastDevouringPlagueAction(botAI); }
        static Action* mind_flay(PlayerbotAI* botAI) { return new CastMindFlayAction(botAI); }
        static Action* holy_fire(PlayerbotAI* botAI) { return new CastHolyFireAction(botAI); }
        static Action* smite(PlayerbotAI* botAI) { return new CastSmiteAction(botAI); }
        static Action* mind_blast(PlayerbotAI* botAI) { return new CastMindBlastAction(botAI); }
        static Action* shadowform(PlayerbotAI* botAI) { return new CastShadowformAction(botAI); }
        static Action* remove_shadowform(PlayerbotAI* botAI) { return new CastRemoveShadowformAction(botAI); }
        static Action* holy_nova(PlayerbotAI* botAI) { return new CastHolyNovaAction(botAI); }
        static Action* power_word_fortitude(PlayerbotAI* botAI) { return new CastPowerWordFortitudeAction(botAI); }
        static Action* power_word_fortitude_on_party(PlayerbotAI* botAI) { return new CastPowerWordFortitudeOnPartyAction(botAI); }
        static Action* divine_spirit(PlayerbotAI* botAI) { return new CastDivineSpiritAction(botAI); }
        static Action* divine_spirit_on_party(PlayerbotAI* botAI) { return new CastDivineSpiritOnPartyAction(botAI); }
        static Action* power_word_shield(PlayerbotAI* botAI) { return new CastPowerWordShieldAction(botAI); }
        static Action* power_word_shield_on_party(PlayerbotAI* botAI) { return new CastPowerWordShieldOnPartyAction(botAI); }
        static Action* renew(PlayerbotAI* botAI) { return new CastRenewAction(botAI); }
        static Action* renew_on_party(PlayerbotAI* botAI) { return new CastRenewOnPartyAction(botAI); }
        static Action* greater_heal(PlayerbotAI* botAI) { return new CastGreaterHealAction(botAI); }
        static Action* greater_heal_on_party(PlayerbotAI* botAI) { return new CastGreaterHealOnPartyAction(botAI); }
        static Action* heal(PlayerbotAI* botAI) { return new CastHealAction(botAI); }
        static Action* heal_on_party(PlayerbotAI* botAI) { return new CastHealOnPartyAction(botAI); }
        static Action* lesser_heal(PlayerbotAI* botAI) { return new CastLesserHealAction(botAI); }
        static Action* lesser_heal_on_party(PlayerbotAI* botAI) { return new CastLesserHealOnPartyAction(botAI); }
        static Action* flash_heal(PlayerbotAI* botAI) { return new CastFlashHealAction(botAI); }
        static Action* flash_heal_on_party(PlayerbotAI* botAI) { return new CastFlashHealOnPartyAction(botAI); }
        static Action* dispel_magic(PlayerbotAI* botAI) { return new CastDispelMagicAction(botAI); }
        static Action* dispel_magic_on_party(PlayerbotAI* botAI) { return new CastDispelMagicOnPartyAction(botAI); }
        static Action* dispel_magic_on_target(PlayerbotAI* botAI) { return new CastDispelMagicOnTargetAction(botAI); }
        static Action* cure_disease(PlayerbotAI* botAI) { return new CastCureDiseaseAction(botAI); }
        static Action* cure_disease_on_party(PlayerbotAI* botAI) { return new CastCureDiseaseOnPartyAction(botAI); }
        static Action* abolish_disease(PlayerbotAI* botAI) { return new CastAbolishDiseaseAction(botAI); }
        static Action* abolish_disease_on_party(PlayerbotAI* botAI) { return new CastAbolishDiseaseOnPartyAction(botAI); }
        static Action* fade(PlayerbotAI* botAI) { return new CastFadeAction(botAI); }
        static Action* inner_fire(PlayerbotAI* botAI) { return new CastInnerFireAction(botAI); }
        static Action* shackle_undead(PlayerbotAI* botAI) { return new CastShackleUndeadAction(botAI); }
        static Action* prayer_of_spirit_on_party(PlayerbotAI* botAI) { return new CastPrayerOfSpiritOnPartyAction(botAI); }
        static Action* prayer_of_fortitude_on_party(PlayerbotAI* botAI) { return new CastPrayerOfFortitudeOnPartyAction(botAI); }
};

PriestAiObjectContext::PriestAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new PriestStrategyFactoryInternal());
    strategyContexts.Add(new PriestCombatStrategyFactoryInternal());
    actionContexts.Add(new PriestAiObjectContextInternal());
    triggerContexts.Add(new PriestTriggerFactoryInternal());
}