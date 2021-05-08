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
		CastFaerieFireAction(PlayerbotAI* botAI) : CastDebuffSpellAction(ai, "faerie fire") {}
	};

    class CastFaerieFireFeralAction : public CastDebuffSpellAction
    {
    public:
        CastFaerieFireFeralAction(PlayerbotAI* botAI) : CastDebuffSpellAction(ai, "faerie fire (feral)") {}
    };

	class CastRejuvenationAction : public CastHealingSpellAction {
	public:
		CastRejuvenationAction(PlayerbotAI* botAI) : CastHealingSpellAction(ai, "rejuvenation") {}
	};

	class CastRegrowthAction : public CastHealingSpellAction {
	public:
		CastRegrowthAction(PlayerbotAI* botAI) : CastHealingSpellAction(ai, "regrowth") {}

	};

    class CastHealingTouchAction : public CastHealingSpellAction {
    public:
        CastHealingTouchAction(PlayerbotAI* botAI) : CastHealingSpellAction(ai, "healing touch") {}

    };

    class CastRejuvenationOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRejuvenationOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "rejuvenation") {}
    };

    class CastRegrowthOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRegrowthOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "regrowth") {}
    };

    class CastHealingTouchOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealingTouchOnPartyAction(PlayerbotAI* botAI) : HealPartyMemberAction(ai, "healing touch") {}
    };

	class CastReviveAction : public ResurrectPartyMemberAction
	{
	public:
		CastReviveAction(PlayerbotAI* botAI) : ResurrectPartyMemberAction(ai, "revive") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), ResurrectPartyMemberAction::getPrerequisites());
		}
	};

	class CastRebirthAction : public ResurrectPartyMemberAction
	{
	public:
		CastRebirthAction(PlayerbotAI* botAI) : ResurrectPartyMemberAction(ai, "rebirth") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), ResurrectPartyMemberAction::getPrerequisites());
		}
	};

	class CastMarkOfTheWildAction : public CastBuffSpellAction {
	public:
		CastMarkOfTheWildAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "mark of the wild") {}
	};

	class CastMarkOfTheWildOnPartyAction : public BuffOnPartyAction {
	public:
		CastMarkOfTheWildOnPartyAction(PlayerbotAI* botAI) : BuffOnPartyAction(ai, "mark of the wild") {}
	};

	class CastSurvivalInstinctsAction : public CastBuffSpellAction {
	public:
		CastSurvivalInstinctsAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "survival instincts") {}
	};

	class CastThornsAction : public CastBuffSpellAction {
	public:
		CastThornsAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "thorns") {}
	};

	class CastOmenOfClarityAction : public CastBuffSpellAction {
	public:
	    CastOmenOfClarityAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "omen of clarity") {}
	};

	class CastWrathAction : public CastSpellAction
	{
	public:
		CastWrathAction(PlayerbotAI* botAI) : CastSpellAction(ai, "wrath") {}
	};

	class CastStarfallAction : public CastSpellAction
	{
	public:
		CastStarfallAction(PlayerbotAI* botAI) : CastSpellAction(ai, "starfall") {}
	};

	class CastHurricaneAction : public CastSpellAction
	{
	public:
	    CastHurricaneAction(PlayerbotAI* botAI) : CastSpellAction(ai, "hurricane") {}
	};

	class CastMoonfireAction : public CastDebuffSpellAction
	{
	public:
		CastMoonfireAction(PlayerbotAI* botAI) : CastDebuffSpellAction(ai, "moonfire") {}
	};

	class CastInsectSwarmAction : public CastDebuffSpellAction
	{
	public:
		CastInsectSwarmAction(PlayerbotAI* botAI) : CastDebuffSpellAction(ai, "insect swarm") {}
	};

	class CastStarfireAction : public CastSpellAction
	{
	public:
		CastStarfireAction(PlayerbotAI* botAI) : CastSpellAction(ai, "starfire") {}
	};

	class CastEntanglingRootsAction : public CastSpellAction
	{
	public:
		CastEntanglingRootsAction(PlayerbotAI* botAI) : CastSpellAction(ai, "entangling roots") {}
	};

    class CastEntanglingRootsCcAction : public CastSpellAction
    {
    public:
        CastEntanglingRootsCcAction(PlayerbotAI* botAI) : CastSpellAction(ai, "entangling roots on cc") {}
        virtual Value<Unit*>* GetTargetValue();
        virtual bool Execute(Event event);
    };

	class CastHibernateAction : public CastSpellAction
	{
	public:
		CastHibernateAction(PlayerbotAI* botAI) : CastSpellAction(ai, "hibernate") {}
	};

    class CastHibernateCcAction : public CastSpellAction
    {
    public:
        CastHibernateCcAction(PlayerbotAI* botAI) : CastSpellAction(ai, "hibernate on cc") {}
        virtual Value<Unit*>* GetTargetValue();
        virtual bool Execute(Event event);
    };

	class CastNaturesGraspAction : public CastBuffSpellAction
	{
	public:
		CastNaturesGraspAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "nature's grasp") {}
	};

	class CastCurePoisonAction : public CastCureSpellAction
	{
	public:
		CastCurePoisonAction(PlayerbotAI* botAI) : CastCureSpellAction(ai, "cure poison") {}
	};

    class CastCurePoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCurePoisonOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(ai, "cure poison", DISPEL_POISON) {}
    };

	class CastAbolishPoisonAction : public CastCureSpellAction
	{
	public:
		CastAbolishPoisonAction(PlayerbotAI* botAI) : CastCureSpellAction(ai, "abolish poison") {}
		virtual NextAction** getAlternatives();
	};

    class CastAbolishPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastAbolishPoisonOnPartyAction(PlayerbotAI* botAI) : CurePartyMemberAction(ai, "abolish poison", DISPEL_POISON) {}

        virtual NextAction** getAlternatives();
    };

    class CastBarskinAction : public CastBuffSpellAction
    {
    public:
        CastBarskinAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "barskin") {}
    };

    class CastInnervateAction : public CastSpellAction
    {
    public:
        CastInnervateAction(PlayerbotAI* botAI) : CastSpellAction(ai, "innervate") {}

        virtual string GetTargetName() { return "self target"; }
    };

    class CastTranquilityAction : public CastAoeHealSpellAction
    {
    public:
        CastTranquilityAction(PlayerbotAI* botAI) : CastAoeHealSpellAction(ai, "tranquility") {}
    };

    class CastNaturesSwiftnessAction : public CastBuffSpellAction
    {
    public:
        CastNaturesSwiftnessAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "nature's swiftness") {}
    };
}
