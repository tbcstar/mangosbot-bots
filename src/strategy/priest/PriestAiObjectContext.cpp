#include "botpch.h"
#include "../../playerbot.h"
#include "PriestActions.h"
#include "PriestAiObjectContext.h"
#include "PriestNonCombatStrategy.h"
#include "ShadowPriestStrategy.h"
#include "../generic/PullStrategy.h"
#include "PriestTriggers.h"
#include "../NamedObjectContext.h"
#include "HolyPriestStrategy.h"

using namespace botAI;


namespace botAI
{
    namespace priest
    {
        using namespace botAI;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &priest::StrategyFactoryInternal::nc;
                creators["pull"] = &priest::StrategyFactoryInternal::pull;
                creators["aoe"] = &priest::StrategyFactoryInternal::shadow_aoe;
                creators["shadow aoe"] = &priest::StrategyFactoryInternal::shadow_aoe;
                creators["dps debuff"] = &priest::StrategyFactoryInternal::shadow_debuff;
                creators["shadow debuff"] = &priest::StrategyFactoryInternal::shadow_debuff;
                creators["cure"] = &priest::StrategyFactoryInternal::cure;
                creators["buff"] = &priest::StrategyFactoryInternal::buff;
                creators["boost"] = &priest::StrategyFactoryInternal::boost;
                creators["rshadow"] = &priest::StrategyFactoryInternal::rshadow;
                creators["cc"] = &priest::StrategyFactoryInternal::cc;
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

        class CombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            CombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["heal"] = &priest::CombatStrategyFactoryInternal::heal;
                creators["shadow"] = &priest::CombatStrategyFactoryInternal::dps;
                creators["dps"] = &priest::CombatStrategyFactoryInternal::dps;
                creators["holy"] = &priest::CombatStrategyFactoryInternal::holy;
            }

        private:
            static Strategy* heal(PlayerbotAI* botAI) { return new HealPriestStrategy(botAI); }
            static Strategy* dps(PlayerbotAI* botAI) { return new ShadowPriestStrategy(botAI); }
            static Strategy* holy(PlayerbotAI* botAI) { return new HolyPriestStrategy(botAI); }
        };
    };
};

namespace botAI
{
    namespace priest
    {
        using namespace botAI;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["devouring plague"] = &TriggerFactoryInternal::devouring_plague;
                creators["shadow word: pain"] = &TriggerFactoryInternal::shadow_word_pain;
                creators["shadow word: pain on attacker"] = &TriggerFactoryInternal::shadow_word_pain_on_attacker;
                creators["dispel magic"] = &TriggerFactoryInternal::dispel_magic;
                creators["dispel magic on party"] = &TriggerFactoryInternal::dispel_magic_party_member;
                creators["cure disease"] = &TriggerFactoryInternal::cure_disease;
                creators["party member cure disease"] = &TriggerFactoryInternal::party_member_cure_disease;
                creators["power word: fortitude"] = &TriggerFactoryInternal::power_word_fortitude;
                creators["power word: fortitude on party"] = &TriggerFactoryInternal::power_word_fortitude_on_party;
                creators["divine spirit"] = &TriggerFactoryInternal::divine_spirit;
                creators["divine spirit on party"] = &TriggerFactoryInternal::divine_spirit_on_party;
                creators["inner fire"] = &TriggerFactoryInternal::inner_fire;
                creators["vampiric touch"] = &TriggerFactoryInternal::vampiric_touch;
                creators["shadowform"] = &TriggerFactoryInternal::shadowform;
                creators["vampiric embrace"] = &TriggerFactoryInternal::vampiric_embrace;
                creators["power infusion"] = &TriggerFactoryInternal::power_infusion;
                creators["inner focus"] = &TriggerFactoryInternal::inner_focus;
                creators["shadow protection"] = &TriggerFactoryInternal::shadow_protection;
                creators["shadow protection on party"] = &TriggerFactoryInternal::shadow_protection_on_party;
                creators["shackle undead"] = &TriggerFactoryInternal::shackle_undead;

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
        };
    };
};



namespace botAI
{
    namespace priest
    {
        using namespace botAI;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["power infusion"] = &AiObjectContextInternal::power_infusion;
                creators["inner focus"] = &AiObjectContextInternal::inner_focus;
                creators["shadow word: pain"] = &AiObjectContextInternal::shadow_word_pain;
                creators["shadow word: pain on attacker"] = &AiObjectContextInternal::shadow_word_pain_on_attacker;
                creators["devouring plague"] = &AiObjectContextInternal::devouring_plague;
                creators["mind flay"] = &AiObjectContextInternal::mind_flay;
                creators["holy fire"] = &AiObjectContextInternal::holy_fire;
                creators["smite"] = &AiObjectContextInternal::smite;
                creators["mind blast"] = &AiObjectContextInternal::mind_blast;
                creators["shadowform"] = &AiObjectContextInternal::shadowform;
                creators["remove shadowform"] = &AiObjectContextInternal::remove_shadowform;
                creators["holy nova"] = &AiObjectContextInternal::holy_nova;
                creators["power word: fortitude"] = &AiObjectContextInternal::power_word_fortitude;
                creators["power word: fortitude on party"] = &AiObjectContextInternal::power_word_fortitude_on_party;
                creators["divine spirit"] = &AiObjectContextInternal::divine_spirit;
                creators["divine spirit on party"] = &AiObjectContextInternal::divine_spirit_on_party;
                creators["power word: shield"] = &AiObjectContextInternal::power_word_shield;
                creators["power word: shield on party"] = &AiObjectContextInternal::power_word_shield_on_party;
                creators["renew"] = &AiObjectContextInternal::renew;
                creators["renew on party"] = &AiObjectContextInternal::renew_on_party;
                creators["greater heal"] = &AiObjectContextInternal::greater_heal;
                creators["greater heal on party"] = &AiObjectContextInternal::greater_heal_on_party;
                creators["heal"] = &AiObjectContextInternal::heal;
                creators["heal on party"] = &AiObjectContextInternal::heal_on_party;
                creators["lesser heal"] = &AiObjectContextInternal::lesser_heal;
                creators["lesser heal on party"] = &AiObjectContextInternal::lesser_heal_on_party;
                creators["flash heal"] = &AiObjectContextInternal::flash_heal;
                creators["flash heal on party"] = &AiObjectContextInternal::flash_heal_on_party;
                creators["dispel magic"] = &AiObjectContextInternal::dispel_magic;
                creators["dispel magic on party"] = &AiObjectContextInternal::dispel_magic_on_party;
                creators["dispel magic on target"] = &AiObjectContextInternal::dispel_magic_on_target;
                creators["cure disease"] = &AiObjectContextInternal::cure_disease;
                creators["cure disease on party"] = &AiObjectContextInternal::cure_disease_on_party;
                creators["abolish disease"] = &AiObjectContextInternal::abolish_disease;
                creators["abolish disease on party"] = &AiObjectContextInternal::abolish_disease_on_party;
                creators["fade"] = &AiObjectContextInternal::fade;
                creators["inner fire"] = &AiObjectContextInternal::inner_fire;
                creators["resurrection"] = &AiObjectContextInternal::resurrection;
                creators["circle of healing"] = &AiObjectContextInternal::circle_of_healing;
                creators["psychic scream"] = &AiObjectContextInternal::psychic_scream;
                creators["vampiric touch"] = &AiObjectContextInternal::vampiric_touch;
                creators["vampiric embrace"] = &AiObjectContextInternal::vampiric_embrace;
                creators["dispersion"] = &AiObjectContextInternal::dispersion;
                creators["shadow protection"] = &AiObjectContextInternal::shadow_protection;
                creators["shadow protection on party"] = &AiObjectContextInternal::shadow_protection_on_party;
                creators["shackle undead"] = &AiObjectContextInternal::shackle_undead;
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
        };
    };
};

PriestAiObjectContext::PriestAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new botAI::priest::StrategyFactoryInternal());
    strategyContexts.Add(new botAI::priest::CombatStrategyFactoryInternal());
    actionContexts.Add(new botAI::priest::AiObjectContextInternal());
    triggerContexts.Add(new botAI::priest::TriggerFactoryInternal());
}
