#pragma once

#include "../actions/GenericActions.h"
#include "RogueComboActions.h"
#include "RogueOpeningActions.h"
#include "RogueFinishingActions.h"

namespace ai
{
	class CastEvasionAction : public CastBuffSpellAction
	{
	public:
		CastEvasionAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "evasion") {}
	};

	class CastSprintAction : public CastBuffSpellAction
	{
	public:
		CastSprintAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "sprint") {}
	};

	class CastKickAction : public CastSpellAction
	{
	public:
		CastKickAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "kick") {}
	};

	class CastFeintAction : public CastBuffSpellAction
	{
	public:
		CastFeintAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "feint") {}
	};

	class CastDismantleAction : public CastSpellAction
	{
	public:
		CastDismantleAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "dismantle") {}
	};

	class CastDistractAction : public CastSpellAction
	{
	public:
		CastDistractAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "distract") {}
	};

	class CastVanishAction : public CastBuffSpellAction
	{
	public:
		CastVanishAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "vanish") {}
	};

	class CastBlindAction : public CastDebuffSpellAction
	{
	public:
		CastBlindAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "blind") {}
	};


	class CastBladeFlurryAction : public CastBuffSpellAction
	{
	public:
		CastBladeFlurryAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "blade flurry") {}
	};

	class CastAdrenalineRushAction : public CastBuffSpellAction
	{
	public:
		CastAdrenalineRushAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "adrenaline rush") {}
	};

	class CastKillingSpreeAction : public CastBuffSpellAction
	{
	public:
		CastKillingSpreeAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "killing spree") {}
	};

    class CastKickOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastKickOnEnemyHealerAction(PlayerbotAI* botAI) : CastSpellOnEnemyHealerAction(botAI, "kick") {}
    };
}
