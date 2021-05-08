#pragma once

#include "../actions/GenericActions.h"

namespace ai
{
    class CastGreaterHealAction : public CastHealingSpellAction {
    public:
        CastGreaterHealAction(PlayerbotAI* botAI) : CastHealingSpellAction(ai, "greater heal") {}
    };

    class CastGreaterHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastGreaterHealOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "greater heal") {}

        virtual string getName() { return "greater heal on party"; }
    };

    class CastLesserHealAction : public CastHealingSpellAction {
    public:
        CastLesserHealAction(PlayerbotAI* botAI) : CastHealingSpellAction(ai, "lesser heal") {}
    };

    class CastLesserHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLesserHealOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "lesser heal") {}

        virtual string getName() { return "lesser heal on party"; }
    };

    class CastFlashHealAction : public CastHealingSpellAction {
    public:
        CastFlashHealAction(PlayerbotAI* botAI) : CastHealingSpellAction(ai, "flash heal") {}
    };

    class CastFlashHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastFlashHealOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "flash heal") {}

        virtual string getName() { return "flash heal on party"; }
    };

    class CastHealAction : public CastHealingSpellAction {
    public:
        CastHealAction(PlayerbotAI* botAI) : CastHealingSpellAction(ai, "heal") {}
    };

    class CastHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "heal") {}

        virtual string getName() { return "heal on party"; }
    };

    class CastRenewAction : public CastHealingSpellAction {
    public:
        CastRenewAction(PlayerbotAI* botAI) : CastHealingSpellAction(ai, "renew") {}
    };

    class CastRenewOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRenewOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "renew") {}

        virtual string getName() { return "renew on party"; }
    };

    class CastFadeAction : public CastBuffSpellAction {
    public:
        CastFadeAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "fade") {}
    };

    class CastShadowformAction : public CastBuffSpellAction {
    public:
        CastShadowformAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "shadowform") {}
    };

    class CastRemoveShadowformAction : public Action {
    public:
        CastRemoveShadowformAction(PlayerbotAI* botAI) : Action(ai, "remove shadowform") {}
        virtual bool isUseful() { return botAI->HasAura("shadowform", AI_VALUE(Unit*, "self target")); }
        virtual bool isPossible() { return true; }
        virtual bool Execute(Event event) {
            botAI->RemoveAura("shadowform");
            return true;
        }
    };

	class CastVampiricEmbraceAction : public CastBuffSpellAction {
	public:
		CastVampiricEmbraceAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "vampiric embrace") {}
	};

	class CastPowerWordShieldAction : public CastBuffSpellAction {
	public:
		CastPowerWordShieldAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "power word: shield") {}
	};

    class CastPowerWordShieldOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastPowerWordShieldOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "power word: shield") {}

        virtual string getName() { return "power word: shield on party"; }
    };

	class CastPowerWordFortitudeAction : public CastBuffSpellAction {
	public:
		CastPowerWordFortitudeAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "power word: fortitude") {}
	};

	class CastDivineSpiritAction : public CastBuffSpellAction {
	public:
		CastDivineSpiritAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "divine spirit") {}
	};

	class CastInnerFireAction : public CastBuffSpellAction {
	public:
		CastInnerFireAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "inner fire") {}
	};

    BEGIN_SPELL_ACTION(CastHolyNovaAction, "holy nova")
    virtual bool isUseful() {
        return !botAI->HasAura("shadowform", AI_VALUE(Unit*, "self target"));
    }
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastHolyFireAction, "holy fire")
        virtual bool isUseful() {
            return !botAI->HasAura("shadowform", AI_VALUE(Unit*, "self target"));
        }
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastSmiteAction, "smite")
        virtual bool isUseful() {
			return !botAI->HasAura("shadowform", AI_VALUE(Unit*, "self target"));
        }
    END_SPELL_ACTION()

	class CastPowerWordFortitudeOnPartyAction : public BuffOnPartyAction {
	public:
		CastPowerWordFortitudeOnPartyAction(PlayerbotAI* botAI) : BuffOnPartyAction(ai, "power word: fortitude") {}
	};

	class CastDivineSpiritOnPartyAction : public BuffOnPartyAction {
	public:
		CastDivineSpiritOnPartyAction(PlayerbotAI* botAI) : BuffOnPartyAction(ai, "divine spirit") {}
	};

	class CastPowerWordPainAction : public CastDebuffSpellAction
	{
    public:
	    CastPowerWordPainAction(PlayerbotAI* botAI) : CastDebuffSpellAction(ai, "shadow word: pain") {}
	};

	class CastPowerWordPainOnAttackerAction : public CastDebuffSpellOnAttackerAction
	{
    public:
	    CastPowerWordPainOnAttackerAction(PlayerbotAI* botAI) : CastDebuffSpellOnAttackerAction(ai, "shadow word: pain") {}
	};

    BEGIN_DEBUFF_ACTION(CastDevouringPlagueAction, "devouring plague")
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastVampiricTouchAction, "vampiric touch")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastMindBlastAction, "mind blast")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastMindFlayAction, "mind flay")
    END_SPELL_ACTION()

	class CastCureDiseaseAction : public CastCureSpellAction {
	public:
		CastCureDiseaseAction(PlayerbotAI* botAI) : CastCureSpellAction(ai, "cure disease") {}
	};

    class CastCureDiseaseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCureDiseaseOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(ai, "cure disease", DISPEL_DISEASE) {}
        virtual string getName() { return "cure disease on party"; }
    };

	class CastAbolishDiseaseAction : public CastCureSpellAction {
	public:
		CastAbolishDiseaseAction(PlayerbotAI* botAI) : CastCureSpellAction(ai, "abolish disease") {}
		virtual NextAction** getAlternatives();
	};

    class CastAbolishDiseaseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastAbolishDiseaseOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(ai, "abolish disease", DISPEL_DISEASE) {}
        virtual string getName() { return "abolish disease on party"; }
        virtual NextAction** getAlternatives();
    };

	class CastDispelMagicAction : public CastCureSpellAction {
	public:
		CastDispelMagicAction(PlayerbotAI* botAI) : CastCureSpellAction(ai, "dispel magic") {}
	};

    class CastDispelMagicOnTargetAction : public CastSpellAction {
    public:
        CastDispelMagicOnTargetAction(PlayerbotAI* botAI) : CastSpellAction(ai, "dispel magic") {}
    };

    class CastDispelMagicOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastDispelMagicOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(ai, "dispel magic", DISPEL_MAGIC) {}
        virtual string getName() { return "dispel magic on party"; }
    };

	class CastResurrectionAction : public ResurrectPartyMemberAction
	{
	public:
		CastResurrectionAction(PlayerbotAI* botAI) : ResurrectPartyMemberAction(ai, "resurrection") {}
	};

	class CastCircleOfHealingAction : public CastAoeHealSpellAction
	{
	public:
		CastCircleOfHealingAction(PlayerbotAI* botAI) : CastAoeHealSpellAction(ai, "circle of healing") {}
	};

	class CastPsychicScreamAction : public CastSpellAction
	{
	public:
	    CastPsychicScreamAction(PlayerbotAI* botAI) : CastSpellAction(ai, "psychic scream") {}
	};

	class CastDispersionAction : public CastSpellAction
	{
	public:
	    CastDispersionAction(PlayerbotAI* botAI) : CastSpellAction(ai, "dispersion") {}
	    virtual string GetTargetName() { return "self target"; }
	};

    class CastInnerFocusAction : public CastBuffSpellAction
    {
    public:
	    CastInnerFocusAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "inner focus") {}
    };

    class CastPowerInfusionAction : public CastBuffSpellAction
    {
    public:
        CastPowerInfusionAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "power infusion") {}
    };

    class CastShadowProtectionAction : public CastBuffSpellAction
    {
    public:
        CastShadowProtectionAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "shadow protection") {}
    };

    class CastShadowProtectionOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastShadowProtectionOnPartyAction(PlayerbotAI* botAI) : BuffOnPartyAction(ai, "shadow protection") {}
    };

    class CastShackleUndeadAction : public CastBuffSpellAction
    {
    public:
        CastShackleUndeadAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "shackle undead") {}
        virtual Value<Unit*>* GetTargetValue() { return context->GetValue<Unit*>("cc target", getName()); }
    };
}
