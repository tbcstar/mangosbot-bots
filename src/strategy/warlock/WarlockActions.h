#pragma once

#include "../actions/GenericActions.h"

namespace botAI
{
	class CastDemonSkinAction : public CastBuffSpellAction {
	public:
		CastDemonSkinAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "demon skin") { }
	};

	class CastDemonArmorAction : public CastBuffSpellAction
	{
	public:
		CastDemonArmorAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "demon armor") { }
	};

	class CastFelArmorAction : public CastBuffSpellAction
	{
	public:
		CastFelArmorAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "fel armor") { }
	};

    BEGIN_RANGED_SPELL_ACTION(CastShadowBoltAction, "shadow bolt")
    END_SPELL_ACTION()

	class CastDrainSoulAction : public CastSpellAction
	{
	public:
		CastDrainSoulAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "drain soul") { }
		virtual bool isUseful()
		{
			return AI_VALUE2(uint8, "item count", "soul shard") < 2;
		}
	};

	class CastDrainManaAction : public CastSpellAction
	{
	public:
		CastDrainManaAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "drain mana") { }
	};

	class CastDrainLifeAction : public CastSpellAction
	{
	public:
		CastDrainLifeAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "drain life") { }
	};

	class CastCurseOfAgonyAction : public CastDebuffSpellAction
	{
	public:
		CastCurseOfAgonyAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "curse of agony") { }
	};

	class CastCurseOfWeaknessAction : public CastDebuffSpellAction
	{
	public:
		CastCurseOfWeaknessAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "curse of weakness") { }
	};

	class CastCorruptionAction : public CastDebuffSpellAction
	{
	public:
		CastCorruptionAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "corruption") { }
	};

	class CastCorruptionOnAttackerAction : public CastDebuffSpellOnAttackerAction
	{
	public:
	    CastCorruptionOnAttackerAction(PlayerbotAI* botAI) : CastDebuffSpellOnAttackerAction(botAI, "corruption") { }
	};

    class CastCurseOfAgonyOnAttackerAction : public CastDebuffSpellOnAttackerAction
    {
    public:
        CastCurseOfAgonyOnAttackerAction(PlayerbotAI* botAI) : CastDebuffSpellOnAttackerAction(botAI, "curse of agony") { }
    };

	class CastSummonVoidwalkerAction : public CastBuffSpellAction
	{
	public:
		CastSummonVoidwalkerAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "summon voidwalker") { }
	};

	class CastSummonFelguardAction : public CastBuffSpellAction
	{
	public:
		CastSummonFelguardAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "summon felguard") { }
	};

	class CastSummonImpAction : public CastBuffSpellAction
	{
	public:
		CastSummonImpAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "summon imp") { }
	};

	class CastCreateHealthstoneAction : public CastBuffSpellAction
	{
	public:
		CastCreateHealthstoneAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "create healthstone") { }
	};

	class CastCreateFirestoneAction : public CastBuffSpellAction
	{
	public:
		CastCreateFirestoneAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "create firestone") { }
	};

	class CastCreateSpellstoneAction : public CastBuffSpellAction
	{
	public:
		CastCreateSpellstoneAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "create spellstone") { }
	};

    class CastBanishAction : public CastBuffSpellAction
    {
    public:
        CastBanishAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "banish on cc") { }
        virtual Value<Unit*>* GetTargetValue() { return context->GetValue<Unit*>("cc target", "banish"); }
        virtual bool Execute(Event event) { return botAI->CastSpell("banish", GetTarget()); }
    };

    class CastSeedOfCorruptionAction : public CastDebuffSpellAction
    {
    public:
        CastSeedOfCorruptionAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "seed of corruption") { }
    };

    class CastRainOfFireAction : public CastSpellAction
    {
    public:
        CastRainOfFireAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "rain of fire") { }
    };

    class CastShadowfuryAction : public CastSpellAction
    {
    public:
        CastShadowfuryAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "shadowfury") { }
    };

    class CastImmolateAction : public CastDebuffSpellAction
    {
    public:
        CastImmolateAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "immolate") { }
    };

    class CastConflagrateAction : public CastSpellAction
    {
    public:
        CastConflagrateAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "conflagrate") { }
    };

    class CastIncinirateAction : public CastSpellAction
    {
    public:
        CastIncinirateAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "incinirate") { }
    };

    class CastFearAction : public CastDebuffSpellAction
    {
    public:
        CastFearAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "fear") { }
    };

    class CastFearOnCcAction : public CastBuffSpellAction
    {
    public:
        CastFearOnCcAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "fear on cc") { }
        virtual Value<Unit*>* GetTargetValue() { return context->GetValue<Unit*>("cc target", "fear"); }
        virtual bool Execute(Event event) { return botAI->CastSpell("fear", GetTarget()); }
        virtual bool isPossible() { return botAI->CanCastSpell("fear", GetTarget()); }
        virtual bool isUseful() { return true; }
    };

    class CastLifeTapAction: public CastSpellAction
    {
    public:
        CastLifeTapAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "life tap") { }
        std::string const& GetTargetName() override { return "self target"; }
        virtual bool isUseful() { return AI_VALUE2(uint8, "health", "self target") > sPlayerbotAIConfig->lowHealth; }
    };

    class CastAmplifyCurseAction : public CastBuffSpellAction
    {
    public:
        CastAmplifyCurseAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "amplify curse") { }
    };

    class CastSiphonLifeAction : public CastDebuffSpellAction
    {
    public:
        CastSiphonLifeAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "siphon life") { }
    };

    class CastSiphonLifeOnAttackerAction : public CastDebuffSpellOnAttackerAction
    {
    public:
        CastSiphonLifeOnAttackerAction(PlayerbotAI* botAI) : CastDebuffSpellOnAttackerAction(botAI, "siphon life") { }
    };
}
