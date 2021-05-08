#include "botpch.h"
#include "../../playerbot.h"
#include "PaladinActions.h"
#include "PaladinTriggers.h"
#include "PaladinAiObjectContext.h"
#include "GenericPaladinNonCombatStrategy.h"
#include "TankPaladinStrategy.h"
#include "DpsPaladinStrategy.h"
#include "PaladinBuffStrategies.h"
#include "../NamedObjectContext.h"
#include "HealPaladinStrategy.h"

using namespace ai;

namespace ai
{
    namespace paladin
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &paladin::StrategyFactoryInternal::nc;
                creators["cure"] = &paladin::StrategyFactoryInternal::cure;
                creators["boost"] = &paladin::StrategyFactoryInternal::boost;
                creators["cc"] = &paladin::StrategyFactoryInternal::cc;
                creators["bthreat"] = &paladin::StrategyFactoryInternal::bthreat;
            }

        private:
            static Strategy* nc(PlayerbotAI* botAI) { return new GenericPaladinNonCombatStrategy(botAI); }
            static Strategy* cure(PlayerbotAI* botAI) { return new PaladinCureStrategy(botAI); }
            static Strategy* boost(PlayerbotAI* botAI) { return new PaladinBoostStrategy(botAI); }
            static Strategy* cc(PlayerbotAI* botAI) { return new PaladinCcStrategy(botAI); }
            static Strategy* bthreat(PlayerbotAI* botAI) { return new PaladinBuffThreatStrategy(botAI); }
        };

        class ResistanceStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            ResistanceStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["rshadow"] = &paladin::ResistanceStrategyFactoryInternal::rshadow;
                creators["rfrost"] = &paladin::ResistanceStrategyFactoryInternal::rfrost;
                creators["rfire"] = &paladin::ResistanceStrategyFactoryInternal::rfire;
                creators["baoe"] = &paladin::ResistanceStrategyFactoryInternal::baoe;
                creators["barmor"] = &paladin::ResistanceStrategyFactoryInternal::barmor;
            }

        private:
            static Strategy* rshadow(PlayerbotAI* botAI) { return new PaladinShadowResistanceStrategy(botAI); }
            static Strategy* rfrost(PlayerbotAI* botAI) { return new PaladinFrostResistanceStrategy(botAI); }
            static Strategy* rfire(PlayerbotAI* botAI) { return new PaladinFireResistanceStrategy(botAI); }
            static Strategy* baoe(PlayerbotAI* botAI) { return new PaladinBuffAoeStrategy(botAI); }
            static Strategy* barmor(PlayerbotAI* botAI) { return new PaladinBuffArmorStrategy(botAI); }
        };

        class BuffStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            BuffStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["bhealth"] = &paladin::BuffStrategyFactoryInternal::bhealth;
                creators["bmana"] = &paladin::BuffStrategyFactoryInternal::bmana;
                creators["bdps"] = &paladin::BuffStrategyFactoryInternal::bdps;
                creators["bstats"] = &paladin::BuffStrategyFactoryInternal::bstats;
            }

        private:
            static Strategy* bhealth(PlayerbotAI* botAI) { return new PaladinBuffHealthStrategy(botAI); }
            static Strategy* bmana(PlayerbotAI* botAI) { return new PaladinBuffManaStrategy(botAI); }
            static Strategy* bdps(PlayerbotAI* botAI) { return new PaladinBuffDpsStrategy(botAI); }
            static Strategy* bstats(PlayerbotAI* botAI) { return new PaladinBuffStatsStrategy(botAI); }
        };

        class CombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            CombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["tank"] = &paladin::CombatStrategyFactoryInternal::tank;
                creators["dps"] = &paladin::CombatStrategyFactoryInternal::dps;
                creators["heal"] = &paladin::CombatStrategyFactoryInternal::heal;
            }

        private:
            static Strategy* tank(PlayerbotAI* botAI) { return new TankPaladinStrategy(botAI); }
            static Strategy* dps(PlayerbotAI* botAI) { return new DpsPaladinStrategy(botAI); }
            static Strategy* heal(PlayerbotAI* botAI) { return new HealPaladinStrategy(botAI); }
        };
    };
};

namespace ai
{
    namespace paladin
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["judgement of wisdom"] = &TriggerFactoryInternal::judgement_of_wisdom;
                creators["judgement of light"] = &TriggerFactoryInternal::judgement_of_light;
                creators["blessing"] = &TriggerFactoryInternal::blessing;
                creators["seal"] = &TriggerFactoryInternal::seal;
                creators["art of war"] = &TriggerFactoryInternal::art_of_war;
                creators["blessing on party"] = &TriggerFactoryInternal::blessing_on_party;
                creators["crusader aura"] = &TriggerFactoryInternal::crusader_aura;
                creators["retribution aura"] = &TriggerFactoryInternal::retribution_aura;
                creators["devotion aura"] = &TriggerFactoryInternal::devotion_aura;
                creators["shadow resistance aura"] = &TriggerFactoryInternal::shadow_resistance_aura;
                creators["frost resistance aura"] = &TriggerFactoryInternal::frost_resistance_aura;
                creators["fire resistance aura"] = &TriggerFactoryInternal::fire_resistance_aura;
                creators["hammer of justice snare"] = &TriggerFactoryInternal::hammer_of_justice_snare;
                creators["hammer of justice interrupt"] = &TriggerFactoryInternal::hammer_of_justice_interrupt;
                creators["cleanse cure disease"] = &TriggerFactoryInternal::CleanseCureDisease;
                creators["cleanse party member cure disease"] = &TriggerFactoryInternal::CleanseCurePartyMemberDisease;
                creators["cleanse cure poison"] = &TriggerFactoryInternal::CleanseCurePoison;
                creators["cleanse party member cure poison"] = &TriggerFactoryInternal::CleanseCurePartyMemberPoison;
                creators["cleanse cure magic"] = &TriggerFactoryInternal::CleanseCureMagic;
                creators["cleanse party member cure magic"] = &TriggerFactoryInternal::CleanseCurePartyMemberMagic;
                creators["righteous fury"] = &TriggerFactoryInternal::righteous_fury;
                creators["holy shield"] = &TriggerFactoryInternal::holy_shield;
                creators["hammer of justice on enemy healer"] = &TriggerFactoryInternal::hammer_of_justice_on_enemy_target;
                creators["hammer of justice on snare target"] = &TriggerFactoryInternal::hammer_of_justice_on_snare_target;
                creators["divine favor"] = &TriggerFactoryInternal::divine_favor;
                creators["turn undead"] = &TriggerFactoryInternal::turn_undead;
            }

        private:
            static Trigger* turn_undead(PlayerbotAI* botAI) { return new TurnUndeadTrigger(botAI); }
            static Trigger* divine_favor(PlayerbotAI* botAI) { return new DivineFavorTrigger(botAI); }
            static Trigger* holy_shield(PlayerbotAI* botAI) { return new HolyShieldTrigger(botAI); }
            static Trigger* righteous_fury(PlayerbotAI* botAI) { return new RighteousFuryTrigger(botAI); }
            static Trigger* judgement_of_wisdom(PlayerbotAI* botAI) { return new JudgementOfWisdomTrigger(botAI); }
            static Trigger* judgement_of_light(PlayerbotAI* botAI) { return new JudgementOfLightTrigger(botAI); }
            static Trigger* blessing(PlayerbotAI* botAI) { return new BlessingTrigger(botAI); }
            static Trigger* seal(PlayerbotAI* botAI) { return new SealTrigger(botAI); }
            static Trigger* art_of_war(PlayerbotAI* botAI) { return new ArtOfWarTrigger(botAI); }
            static Trigger* blessing_on_party(PlayerbotAI* botAI) { return new BlessingOnPartyTrigger(botAI); }
            static Trigger* crusader_aura(PlayerbotAI* botAI) { return new CrusaderAuraTrigger(botAI); }
            static Trigger* retribution_aura(PlayerbotAI* botAI) { return new RetributionAuraTrigger(botAI); }
            static Trigger* devotion_aura(PlayerbotAI* botAI) { return new DevotionAuraTrigger(botAI); }
            static Trigger* shadow_resistance_aura(PlayerbotAI* botAI) { return new ShadowResistanceAuraTrigger(botAI); }
            static Trigger* frost_resistance_aura(PlayerbotAI* botAI) { return new FrostResistanceAuraTrigger(botAI); }
            static Trigger* fire_resistance_aura(PlayerbotAI* botAI) { return new FireResistanceAuraTrigger(botAI); }
            static Trigger* hammer_of_justice_snare(PlayerbotAI* botAI) { return new HammerOfJusticeSnareTrigger(botAI); }
            static Trigger* hammer_of_justice_interrupt(PlayerbotAI* botAI) { return new HammerOfJusticeInterruptSpellTrigger(botAI); }
            static Trigger* CleanseCureDisease(PlayerbotAI* botAI) { return new CleanseCureDiseaseTrigger(botAI); }
            static Trigger* CleanseCurePartyMemberDisease(PlayerbotAI* botAI) { return new CleanseCurePartyMemberDiseaseTrigger(botAI); }
            static Trigger* CleanseCurePoison(PlayerbotAI* botAI) { return new CleanseCurePoisonTrigger(botAI); }
            static Trigger* CleanseCurePartyMemberPoison(PlayerbotAI* botAI) { return new CleanseCurePartyMemberPoisonTrigger(botAI); }
            static Trigger* CleanseCureMagic(PlayerbotAI* botAI) { return new CleanseCureMagicTrigger(botAI); }
            static Trigger* CleanseCurePartyMemberMagic(PlayerbotAI* botAI) { return new CleanseCurePartyMemberMagicTrigger(botAI); }
            static Trigger* hammer_of_justice_on_enemy_target(PlayerbotAI* botAI) { return new HammerOfJusticeEnemyHealerTrigger(botAI); }
            static Trigger* hammer_of_justice_on_snare_target(PlayerbotAI* botAI) { return new HammerOfJusticeSnareTrigger(botAI); }
        };
    };
};

namespace ai
{
    namespace paladin
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["seal of command"] = &AiObjectContextInternal::seal_of_command;
                creators["seal of vengeance"] = &AiObjectContextInternal::seal_of_vengeance;
                creators["blessing of might"] = &AiObjectContextInternal::blessing_of_might;
                creators["blessing of wisdom"] = &AiObjectContextInternal::blessing_of_wisdom;
                creators["blessing of kings"] = &AiObjectContextInternal::blessing_of_kings;
                creators["blessing of sanctuary"] = &AiObjectContextInternal::blessing_of_sanctuary;
                creators["divine storm"] = &AiObjectContextInternal::divine_storm;
                creators["blessing of kings on party"] = &AiObjectContextInternal::blessing_of_kings_on_party;
                creators["blessing of might on party"] = &AiObjectContextInternal::blessing_of_might_on_party;
                creators["blessing of wisdom on party"] = &AiObjectContextInternal::blessing_of_wisdom_on_party;
                creators["redemption"] = &AiObjectContextInternal::redemption;
                creators["crusader strike"] = &AiObjectContextInternal::crusader_strike;
                creators["crusader aura"] = &AiObjectContextInternal::crusader_aura;
                creators["seal of light"] = &AiObjectContextInternal::seal_of_light;
                creators["devotion aura"] = &AiObjectContextInternal::devotion_aura;
                creators["holy wrath"] = &AiObjectContextInternal::holy_wrath;
                creators["consecration"] = &AiObjectContextInternal::consecration;
                creators["cleanse disease"] = &AiObjectContextInternal::cleanse_disease;
                creators["cleanse poison"] = &AiObjectContextInternal::cleanse_poison;
                creators["cleanse magic"] = &AiObjectContextInternal::cleanse_magic;
                creators["purify disease"] = &AiObjectContextInternal::purify_disease;
                creators["purify poison"] = &AiObjectContextInternal::purify_poison;
                creators["cleanse poison on party"] = &AiObjectContextInternal::cleanse_poison_on_party;
                creators["cleanse disease on party"] = &AiObjectContextInternal::cleanse_disease_on_party;
                creators["cleanse magic on party"] = &AiObjectContextInternal::cleanse_magic_on_party;
                creators["purify poison on party"] = &AiObjectContextInternal::purify_poison_on_party;
                creators["purify disease on party"] = &AiObjectContextInternal::purify_disease_on_party;
                creators["seal of wisdom"] = &AiObjectContextInternal::seal_of_wisdom;
                creators["seal of justice"] = &AiObjectContextInternal::seal_of_justice;
                creators["seal of righteousness"] = &AiObjectContextInternal::seal_of_righteousness;
                creators["flash of light"] = &AiObjectContextInternal::flash_of_light;
                creators["hand of reckoning"] = &AiObjectContextInternal::hand_of_reckoning;
                creators["avenger's shield"] = &AiObjectContextInternal::avengers_shield;
                creators["exorcism"] = &AiObjectContextInternal::exorcism;
                creators["judgement of light"] = &AiObjectContextInternal::judgement_of_light;
                creators["judgement of wisdom"] = &AiObjectContextInternal::judgement_of_wisdom;
                creators["divine shield"] = &AiObjectContextInternal::divine_shield;
                creators["divine protection"] = &AiObjectContextInternal::divine_protection;
                creators["divine protection on party"] =&AiObjectContextInternal::divine_protection_on_party;
                creators["hammer of justice"] = &AiObjectContextInternal::hammer_of_justice;
                creators["flash of light on party"] = &AiObjectContextInternal::flash_of_light_on_party;
                creators["holy light"] = &AiObjectContextInternal::holy_light;
                creators["holy light on party"] = &AiObjectContextInternal::holy_light_on_party;
                creators["lay on hands"] = &AiObjectContextInternal::lay_on_hands;
                creators["lay on hands on party"] = &AiObjectContextInternal::lay_on_hands_on_party;
                creators["judgement of justice"] = &AiObjectContextInternal::judgement_of_justice;
                creators["hammer of wrath"] = &AiObjectContextInternal::hammer_of_wrath;
                creators["holy shield"] = &AiObjectContextInternal::holy_shield;
                creators["hammer of the righteous"] = &AiObjectContextInternal::hammer_of_the_righteous;
                creators["retribution aura"] = &AiObjectContextInternal::retribution_aura;
                creators["shadow resistance aura"] = &AiObjectContextInternal::shadow_resistance_aura;
                creators["frost resistance aura"] = &AiObjectContextInternal::frost_resistance_aura;
                creators["fire resistance aura"] = &AiObjectContextInternal::fire_resistance_aura;
                creators["righteous fury"] = &AiObjectContextInternal::righteous_fury;
                creators["hammer of justice on enemy healer"] = &AiObjectContextInternal::hammer_of_justice_on_enemy_healer;
                creators["hammer of justice on snare target"] = &AiObjectContextInternal::hammer_of_justice_on_snare_target;
                creators["divine favor"] = &AiObjectContextInternal::divine_favor;
                creators["turn undead"] = &AiObjectContextInternal::turn_undead;
            }

        private:
            static Action* turn_undead(PlayerbotAI* botAI) { return new CastTurnUndeadAction(botAI); }
            static Action* divine_favor(PlayerbotAI* botAI) { return new CastDivineFavorAction(botAI); }
            static Action* righteous_fury(PlayerbotAI* botAI) { return new CastRighteousFuryAction(botAI); }
            static Action* seal_of_command(PlayerbotAI* botAI) { return new CastSealOfCommandAction(botAI); }
            static Action* seal_of_vengeance(PlayerbotAI* botAI) { return new CastSealOfVengeanceAction(botAI); }
            static Action* blessing_of_sanctuary(PlayerbotAI* botAI) { return new CastBlessingOfSanctuaryAction(botAI); }
            static Action* blessing_of_might(PlayerbotAI* botAI) { return new CastBlessingOfMightAction(botAI); }
            static Action* blessing_of_wisdom(PlayerbotAI* botAI) { return new CastBlessingOfWisdomAction(botAI); }
            static Action* blessing_of_kings(PlayerbotAI* botAI) { return new CastBlessingOfKingsAction(botAI); }
            static Action* divine_storm(PlayerbotAI* botAI) { return new CastDivineStormAction(botAI); }
            static Action* blessing_of_kings_on_party(PlayerbotAI* botAI) { return new CastBlessingOfKingsOnPartyAction(botAI); }
            static Action* blessing_of_might_on_party(PlayerbotAI* botAI) { return new CastBlessingOfMightOnPartyAction(botAI); }
            static Action* blessing_of_wisdom_on_party(PlayerbotAI* botAI) { return new CastBlessingOfWisdomOnPartyAction(botAI); }
            static Action* redemption(PlayerbotAI* botAI) { return new CastRedemptionAction(botAI); }
            static Action* crusader_strike(PlayerbotAI* botAI) { return new CastCrusaderStrikeAction(botAI); }
            static Action* crusader_aura(PlayerbotAI* botAI) { return new CastCrusaderAuraAction(botAI); }
            static Action* seal_of_light(PlayerbotAI* botAI) { return new CastSealOfLightAction(botAI); }
            static Action* devotion_aura(PlayerbotAI* botAI) { return new CastDevotionAuraAction(botAI); }
            static Action* holy_wrath(PlayerbotAI* botAI) { return new CastHolyWrathAction(botAI); }
            static Action* consecration(PlayerbotAI* botAI) { return new CastConsecrationAction(botAI); }
            static Action* cleanse_poison(PlayerbotAI* botAI) { return new CastCleansePoisonAction(botAI); }
            static Action* cleanse_disease(PlayerbotAI* botAI) { return new CastCleanseDiseaseAction(botAI); }
            static Action* cleanse_magic(PlayerbotAI* botAI) { return new CastCleanseMagicAction(botAI); }
            static Action* purify_poison(PlayerbotAI* botAI) { return new CastPurifyPoisonAction(botAI); }
            static Action* purify_disease(PlayerbotAI* botAI) { return new CastPurifyDiseaseAction(botAI); }
            static Action* cleanse_poison_on_party(PlayerbotAI* botAI) { return new CastCleansePoisonOnPartyAction(botAI); }
            static Action* cleanse_disease_on_party(PlayerbotAI* botAI) { return new CastCleanseDiseaseOnPartyAction(botAI); }
            static Action* cleanse_magic_on_party(PlayerbotAI* botAI) { return new CastCleanseMagicOnPartyAction(botAI); }
            static Action* purify_poison_on_party(PlayerbotAI* botAI) { return new CastPurifyPoisonOnPartyAction(botAI); }
            static Action* purify_disease_on_party(PlayerbotAI* botAI) { return new CastPurifyDiseaseOnPartyAction(botAI); }
            static Action* seal_of_wisdom(PlayerbotAI* botAI) { return new CastSealOfWisdomAction(botAI); }
            static Action* seal_of_justice(PlayerbotAI* botAI) { return new CastSealOfJusticeAction(botAI); }
            static Action* seal_of_righteousness(PlayerbotAI* botAI) { return new CastSealOfRighteousnessAction(botAI); }
            static Action* flash_of_light(PlayerbotAI* botAI) { return new CastFlashOfLightAction(botAI); }
            static Action* hand_of_reckoning(PlayerbotAI* botAI) { return new CastHandOfReckoningAction(botAI); }
            static Action* avengers_shield(PlayerbotAI* botAI) { return new CastAvengersShieldAction(botAI); }
            static Action* exorcism(PlayerbotAI* botAI) { return new CastExorcismAction(botAI); }
            static Action* judgement_of_light(PlayerbotAI* botAI) { return new CastJudgementOfLightAction(botAI); }
            static Action* judgement_of_wisdom(PlayerbotAI* botAI) { return new CastJudgementOfWisdomAction(botAI); }
            static Action* divine_shield(PlayerbotAI* botAI) { return new CastDivineShieldAction(botAI); }
            static Action* divine_protection(PlayerbotAI* botAI) { return new CastDivineProtectionAction(botAI); }
            static Action* divine_protection_on_party(PlayerbotAI* botAI) { return new CastDivineProtectionOnPartyAction(botAI); }
            static Action* hammer_of_justice(PlayerbotAI* botAI) { return new CastHammerOfJusticeAction(botAI); }
            static Action* flash_of_light_on_party(PlayerbotAI* botAI) { return new CastFlashOfLightOnPartyAction(botAI); }
            static Action* holy_light(PlayerbotAI* botAI) { return new CastHolyLightAction(botAI); }
            static Action* holy_light_on_party(PlayerbotAI* botAI) { return new CastHolyLightOnPartyAction(botAI); }
            static Action* lay_on_hands(PlayerbotAI* botAI) { return new CastLayOnHandsAction(botAI); }
            static Action* lay_on_hands_on_party(PlayerbotAI* botAI) { return new CastLayOnHandsOnPartyAction(botAI); }
            static Action* judgement_of_justice(PlayerbotAI* botAI) { return new CastJudgementOfJusticeAction(botAI); }
            static Action* hammer_of_wrath(PlayerbotAI* botAI) { return new CastHammerOfWrathAction(botAI); }
            static Action* holy_shield(PlayerbotAI* botAI) { return new CastHolyShieldAction(botAI); }
            static Action* hammer_of_the_righteous(PlayerbotAI* botAI) { return new CastHammerOfTheRighteousAction(botAI); }
            static Action* retribution_aura(PlayerbotAI* botAI) { return new CastRetributionAuraAction(botAI); }
            static Action* shadow_resistance_aura(PlayerbotAI* botAI) { return new CastShadowResistanceAuraAction(botAI); }
            static Action* frost_resistance_aura(PlayerbotAI* botAI) { return new CastFrostResistanceAuraAction(botAI); }
            static Action* fire_resistance_aura(PlayerbotAI* botAI) { return new CastFireResistanceAuraAction(botAI); }
            static Action* hammer_of_justice_on_enemy_healer(PlayerbotAI* botAI) { return new CastHammerOfJusticeOnEnemyHealerAction(botAI); }
            static Action* hammer_of_justice_on_snare_target(PlayerbotAI* botAI) { return new CastHammerOfJusticeSnareAction(botAI); }
        };
    };
};


PaladinAiObjectContext::PaladinAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new ai::paladin::StrategyFactoryInternal());
    strategyContexts.Add(new ai::paladin::CombatStrategyFactoryInternal());
    strategyContexts.Add(new ai::paladin::BuffStrategyFactoryInternal());
    strategyContexts.Add(new ai::paladin::ResistanceStrategyFactoryInternal());
    actionContexts.Add(new ai::paladin::AiObjectContextInternal());
    triggerContexts.Add(new ai::paladin::TriggerFactoryInternal());
}
