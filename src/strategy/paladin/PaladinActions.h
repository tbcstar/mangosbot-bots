#pragma once
#include "../actions/GenericActions.h"

namespace ai
{
    class CastJudgementOfLightAction : public CastMeleeSpellAction
    {
    public:
        CastJudgementOfLightAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "judgement of light") {}
    };

    class CastJudgementOfWisdomAction : public CastMeleeSpellAction
    {
    public:
        CastJudgementOfWisdomAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "judgement of wisdom") {}
    };

    class CastJudgementOfJusticeAction : public CastMeleeSpellAction
    {
    public:
        CastJudgementOfJusticeAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "judgement of justice") {}
    };

	class CastRighteousFuryAction : public CastBuffSpellAction
	{
	public:
		CastRighteousFuryAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "righteous fury") {}
	};

	class CastDevotionAuraAction : public CastBuffSpellAction
	{
	public:
		CastDevotionAuraAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "devotion aura") {}
	};

	class CastRetributionAuraAction : public CastBuffSpellAction
	{
	public:
		CastRetributionAuraAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "retribution aura") {}
	};

	class CastConcentrationAuraAction : public CastBuffSpellAction
	{
	public:
		CastConcentrationAuraAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "concentration aura") {}
	};

	class CastDivineStormAction : public CastBuffSpellAction
	{
	public:
		CastDivineStormAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "divine storm") {}
	};

	class CastCrusaderStrikeAction : public CastMeleeSpellAction
	{
	public:
		CastCrusaderStrikeAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "crusader strike") {}
	};

	class CastShadowResistanceAuraAction : public CastBuffSpellAction
	{
	public:
		CastShadowResistanceAuraAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "shadow resistance aura") {}
	};

	class CastFrostResistanceAuraAction : public CastBuffSpellAction
	{
	public:
		CastFrostResistanceAuraAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "frost resistance aura") {}
	};

	class CastFireResistanceAuraAction : public CastBuffSpellAction
	{
	public:
		CastFireResistanceAuraAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "fire resistance aura") {}
	};

	class CastCrusaderAuraAction : public CastBuffSpellAction
	{
	public:
		CastCrusaderAuraAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "crusader aura") {}
	};

    class CastSealSpellAction : public CastBuffSpellAction
    {
    public:
        CastSealSpellAction(PlayerbotAI* botAI, string name) : CastBuffSpellAction(ai, name) {}
        virtual bool isUseful() { return AI_VALUE2(bool, "combat", "self target"); }
    };

	class CastSealOfRighteousnessAction : public CastSealSpellAction
	{
	public:
		CastSealOfRighteousnessAction(PlayerbotAI* botAI) : CastSealSpellAction(ai, "seal of righteousness") {}
	};

	class CastSealOfJusticeAction : public CastSealSpellAction
	{
	public:
		CastSealOfJusticeAction(PlayerbotAI* botAI) : CastSealSpellAction(ai, "seal of justice") {}
	};


	class CastSealOfLightAction : public CastSealSpellAction
	{
	public:
		CastSealOfLightAction(PlayerbotAI* botAI) : CastSealSpellAction(ai, "seal of light") {}
	};

	class CastSealOfWisdomAction : public CastSealSpellAction
	{
	public:
		CastSealOfWisdomAction(PlayerbotAI* botAI) : CastSealSpellAction(ai, "seal of wisdom") {}
	};

	class CastSealOfCommandAction : public CastSealSpellAction
	{
	public:
		CastSealOfCommandAction(PlayerbotAI* botAI) : CastSealSpellAction(ai, "seal of command") {}
	};

	class CastSealOfVengeanceAction : public CastSealSpellAction
	{
	public:
	    CastSealOfVengeanceAction(PlayerbotAI* botAI) : CastSealSpellAction(ai, "seal of vengeance") {}
	};


	class CastBlessingOfMightAction : public CastBuffSpellAction
	{
	public:
		CastBlessingOfMightAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "blessing of might") {}
		virtual bool Execute(Event event);
	};

    class CastBlessingOnPartyAction : public BuffOnPartyAction
    {
    public:
	    CastBlessingOnPartyAction(PlayerbotAI* botAI, string name) : BuffOnPartyAction(ai, name) {}
        virtual Value<Unit*>* GetTargetValue();
    };

	class CastBlessingOfMightOnPartyAction : public CastBlessingOnPartyAction
	{
	public:
		CastBlessingOfMightOnPartyAction(PlayerbotAI* botAI) : CastBlessingOnPartyAction(ai, "blessing of might") {}
        virtual string getName() { return "blessing of might on party";}
        virtual bool Execute(Event event);
	};

	class CastBlessingOfWisdomAction : public CastBuffSpellAction
	{
	public:
		CastBlessingOfWisdomAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "blessing of wisdom") {}
		virtual bool Execute(Event event);
	};

	class CastBlessingOfWisdomOnPartyAction : public CastBlessingOnPartyAction
	{
	public:
		CastBlessingOfWisdomOnPartyAction(PlayerbotAI* botAI) : CastBlessingOnPartyAction(ai, "blessing of wisdom") {}
        virtual string getName() { return "blessing of wisdom on party";}
        virtual bool Execute(Event event);
	};

	class CastBlessingOfKingsAction : public CastBuffSpellAction
	{
	public:
		CastBlessingOfKingsAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "blessing of kings") {}
	};

	class CastBlessingOfKingsOnPartyAction : public CastBlessingOnPartyAction
	{
	public:
		CastBlessingOfKingsOnPartyAction(PlayerbotAI* botAI) : CastBlessingOnPartyAction(ai, "blessing of kings") {}
        virtual string getName() { return "blessing of kings on party";}
	};

	class CastBlessingOfSanctuaryAction : public CastBuffSpellAction
	{
	public:
		CastBlessingOfSanctuaryAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "blessing of sanctuary") {}
	};

	class CastBlessingOfSanctuaryOnPartyAction : public CastBlessingOnPartyAction
	{
	public:
		CastBlessingOfSanctuaryOnPartyAction(PlayerbotAI* botAI) : CastBlessingOnPartyAction(ai, "blessing of sanctuary") {}
        virtual string getName() { return "blessing of sanctuary on party";}
	};

    class CastHolyLightAction : public CastHealingSpellAction
    {
    public:
        CastHolyLightAction(PlayerbotAI* botAI) : CastHealingSpellAction(ai, "holy light") {}
    };

    class CastHolyLightOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHolyLightOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "holy light") {}

        virtual string getName() { return "holy light on party"; }
    };

    class CastFlashOfLightAction : public CastHealingSpellAction
    {
    public:
        CastFlashOfLightAction(PlayerbotAI* botAI) : CastHealingSpellAction(ai, "flash of light") {}
    };

    class CastFlashOfLightOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastFlashOfLightOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "flash of light") {}

        virtual string getName() { return "flash of light on party"; }
    };

    class CastLayOnHandsAction : public CastHealingSpellAction
    {
    public:
        CastLayOnHandsAction(PlayerbotAI* botAI) : CastHealingSpellAction(ai, "lay on hands") {}
    };

    class CastLayOnHandsOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLayOnHandsOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "lay on hands") {}

        virtual string getName() { return "lay on hands on party"; }
    };

	class CastDivineProtectionAction : public CastBuffSpellAction
	{
	public:
		CastDivineProtectionAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "divine protection") {}
	};

    class CastDivineProtectionOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastDivineProtectionOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "divine protection") {}

        virtual string getName() { return "divine protection on party"; }
    };

	class CastDivineShieldAction: public CastBuffSpellAction
	{
	public:
		CastDivineShieldAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "divine shield") {}
	};

    class CastConsecrationAction : public CastMeleeSpellAction
    {
    public:
	    CastConsecrationAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "consecration") {}
    };

    class CastHolyWrathAction : public CastMeleeSpellAction
    {
    public:
        CastHolyWrathAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "holy wrath") {}
    };

    class CastHammerOfJusticeAction : public CastMeleeSpellAction
    {
    public:
        CastHammerOfJusticeAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "hammer of justice") {}
    };

	class CastHammerOfWrathAction : public CastMeleeSpellAction
	{
	public:
		CastHammerOfWrathAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "hammer of wrath") {}
	};

	class CastHammerOfTheRighteousAction : public CastMeleeSpellAction
	{
	public:
		CastHammerOfTheRighteousAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "hammer of the righteous") {}
	};

	class CastPurifyPoisonAction : public CastCureSpellAction
	{
	public:
		CastPurifyPoisonAction(PlayerbotAI* botAI) : CastCureSpellAction(ai, "purify") {}
	};

	class CastPurifyDiseaseAction : public CastCureSpellAction
	{
	public:
		CastPurifyDiseaseAction(PlayerbotAI* botAI) : CastCureSpellAction(ai, "purify") {}
	};

    class CastPurifyPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastPurifyPoisonOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(ai, "purify", DISPEL_POISON) {}

        virtual string getName() { return "purify poison on party"; }
    };

	class CastPurifyDiseaseOnPartyAction : public CurePartyMemberAction
	{
	public:
		CastPurifyDiseaseOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(ai, "purify", DISPEL_DISEASE) {}

		virtual string getName() { return "purify disease on party"; }
	};

	class CastHandOfReckoningAction : public CastSpellAction
	{
	public:
		CastHandOfReckoningAction(PlayerbotAI* botAI) : CastSpellAction(ai, "hand of reckoning") {}
	};

	class CastCleansePoisonAction : public CastCureSpellAction
	{
	public:
		CastCleansePoisonAction(PlayerbotAI* botAI) : CastCureSpellAction(ai, "cleanse") {}
	};

	class CastCleanseDiseaseAction : public CastCureSpellAction
	{
	public:
		CastCleanseDiseaseAction(PlayerbotAI* botAI) : CastCureSpellAction(ai, "cleanse") {}
	};

	class CastCleanseMagicAction : public CastCureSpellAction
	{
	public:
		CastCleanseMagicAction(PlayerbotAI* botAI) : CastCureSpellAction(ai, "cleanse") {}
	};

    class CastCleansePoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCleansePoisonOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(ai, "cleanse", DISPEL_POISON) {}

        virtual string getName() { return "cleanse poison on party"; }
    };

	class CastCleanseDiseaseOnPartyAction : public CurePartyMemberAction
	{
	public:
		CastCleanseDiseaseOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(ai, "cleanse", DISPEL_DISEASE) {}

		virtual string getName() { return "cleanse disease on party"; }
	};

	class CastCleanseMagicOnPartyAction : public CurePartyMemberAction
	{
	public:
		CastCleanseMagicOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(ai, "cleanse", DISPEL_MAGIC) {}

		virtual string getName() { return "cleanse magic on party"; }
	};

    BEGIN_SPELL_ACTION(CastAvengersShieldAction, "avenger's shield")
    END_SPELL_ACTION()

	BEGIN_SPELL_ACTION(CastExorcismAction, "exorcism")
	END_SPELL_ACTION()

	class CastHolyShieldAction : public CastBuffSpellAction
	{
	public:
		CastHolyShieldAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "holy shield") {}
	};

	class CastRedemptionAction : public ResurrectPartyMemberAction
	{
	public:
		CastRedemptionAction(PlayerbotAI* botAI) : ResurrectPartyMemberAction(ai, "redemption") {}
	};

    class CastHammerOfJusticeOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastHammerOfJusticeOnEnemyHealerAction(PlayerbotAI* botAI) : CastSpellOnEnemyHealerAction(ai, "hammer of justice") {}
    };

    class CastHammerOfJusticeSnareAction : public CastSnareSpellAction
    {
    public:
        CastHammerOfJusticeSnareAction(PlayerbotAI* botAI) : CastSnareSpellAction(ai, "hammer of justice") {}
    };

    class CastDivineFavorAction : public CastBuffSpellAction
    {
    public:
        CastDivineFavorAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "divine favor") {}
    };

    class CastTurnUndeadAction : public CastBuffSpellAction
    {
    public:
        CastTurnUndeadAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "turn undead") {}
        virtual Value<Unit*>* GetTargetValue() { return context->GetValue<Unit*>("cc target", getName()); }
    };
}
