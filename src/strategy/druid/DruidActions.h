#pragma once

#include "../actions/GenericActions.h"
#include "DruidShapeshiftActions.h"
#include "DruidBearActions.h"
#include "DruidCatActions.h"

namespace ai
{
	class CastFaerieFireAction : public CastDebuffSpellAction
	{
	public:
		CastFaerieFireAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "faerie fire") {}
	};

    class CastFaerieFireFeralAction : public CastDebuffSpellAction
    {
    public:
        CastFaerieFireFeralAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "faerie fire (feral)") {}
    };

	class CastRejuvenationAction : public CastHealingSpellAction {
	public:
		CastRejuvenationAction(PlayerbotAI* botAI) : CastHealingSpellAction(botAI, "rejuvenation") {}
	};

	class CastRegrowthAction : public CastHealingSpellAction {
	public:
		CastRegrowthAction(PlayerbotAI* botAI) : CastHealingSpellAction(botAI, "regrowth") {}

	};

    class CastHealingTouchAction : public CastHealingSpellAction {
    public:
        CastHealingTouchAction(PlayerbotAI* botAI) : CastHealingSpellAction(botAI, "healing touch") {}

    };

    class CastRejuvenationOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRejuvenationOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(botAI, "rejuvenation") {}
    };

    class CastRegrowthOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRegrowthOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(botAI, "regrowth") {}
    };

    class CastHealingTouchOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealingTouchOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(botAI, "healing touch") {}
    };

	class CastReviveAction : public ResurrectPartyMemberAction
	{
	public:
		CastReviveAction(PlayerbotAI* botAI) : ResurrectPartyMemberAction(botAI, "revive") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), nullptr), ResurrectPartyMemberAction::getPrerequisites());
		}
	};

	class CastRebirthAction : public ResurrectPartyMemberAction
	{
	public:
		CastRebirthAction(PlayerbotAI* botAI) : ResurrectPartyMemberAction(botAI, "rebirth") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), nullptr), ResurrectPartyMemberAction::getPrerequisites());
		}
	};

	class CastMarkOfTheWildAction : public CastBuffSpellAction {
	public:
		CastMarkOfTheWildAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "mark of the wild") {}
	};

	class CastMarkOfTheWildOnPartyAction : public BuffOnPartyAction {
	public:
		CastMarkOfTheWildOnPartyAction(PlayerbotAI* botAI) : BuffOnPartyAction(botAI, "mark of the wild") {}
	};

	class CastSurvivalInstinctsAction : public CastBuffSpellAction {
	public:
		CastSurvivalInstinctsAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "survival instincts") {}
	};

	class CastThornsAction : public CastBuffSpellAction {
	public:
		CastThornsAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "thorns") {}
	};

	class CastOmenOfClarityAction : public CastBuffSpellAction {
	public:
	    CastOmenOfClarityAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "omen of clarity") {}
	};

	class CastWrathAction : public CastSpellAction
	{
	public:
		CastWrathAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "wrath") {}
	};

	class CastStarfallAction : public CastSpellAction
	{
	public:
		CastStarfallAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "starfall") {}
	};

	class CastHurricaneAction : public CastSpellAction
	{
	public:
	    CastHurricaneAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "hurricane") {}
	};

	class CastMoonfireAction : public CastDebuffSpellAction
	{
	public:
		CastMoonfireAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "moonfire") {}
	};

	class CastInsectSwarmAction : public CastDebuffSpellAction
	{
	public:
		CastInsectSwarmAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "insect swarm") {}
	};

	class CastStarfireAction : public CastSpellAction
	{
	public:
		CastStarfireAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "starfire") {}
	};

	class CastEntanglingRootsAction : public CastSpellAction
	{
	public:
		CastEntanglingRootsAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "entangling roots") {}
	};

    class CastEntanglingRootsCcAction : public CastSpellAction
    {
    public:
        CastEntanglingRootsCcAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "entangling roots on cc") {}
        virtual Value<Unit*>* GetTargetValue();
        bool Execute(Event event) override;
    };

	class CastHibernateAction : public CastSpellAction
	{
	public:
		CastHibernateAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "hibernate") {}
	};

    class CastHibernateCcAction : public CastSpellAction
    {
    public:
        CastHibernateCcAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "hibernate on cc") {}
        virtual Value<Unit*>* GetTargetValue();
        bool Execute(Event event) override;
    };

	class CastNaturesGraspAction : public CastBuffSpellAction
	{
	public:
		CastNaturesGraspAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "nature's grasp") {}
	};

	class CastCurePoisonAction : public CastCureSpellAction
	{
	public:
		CastCurePoisonAction(PlayerbotAI* botAI) : CastCureSpellAction(botAI, "cure poison") {}
	};

    class CastCurePoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCurePoisonOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(botAI, "cure poison", DISPEL_POISON) {}
    };

	class CastAbolishPoisonAction : public CastCureSpellAction
	{
	public:
		CastAbolishPoisonAction(PlayerbotAI* botAI) : CastCureSpellAction(botAI, "abolish poison") {}
		virtual NextAction** getAlternatives();
	};

    class CastAbolishPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastAbolishPoisonOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(botAI, "abolish poison", DISPEL_POISON) {}

        virtual NextAction** getAlternatives();
    };

    class CastBarskinAction : public CastBuffSpellAction
    {
    public:
        CastBarskinAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "barskin") {}
    };

    class CastInnervateAction : public CastSpellAction
    {
    public:
        CastInnervateAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "innervate") {}

        virtual string GetTargetName() { return "self target"; }
    };

    class CastTranquilityAction : public CastAoeHealSpellAction
    {
    public:
        CastTranquilityAction(PlayerbotAI* botAI) : CastAoeHealSpellAction(botAI, "tranquility") {}
    };

    class CastNaturesSwiftnessAction : public CastBuffSpellAction
    {
    public:
        CastNaturesSwiftnessAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "nature's swiftness") {}
    };
}
