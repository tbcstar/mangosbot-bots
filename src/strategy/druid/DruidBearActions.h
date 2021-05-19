#pragma once

namespace ai {
	class CastFeralChargeBearAction : public CastReachTargetSpellAction
	{
	public:
		CastFeralChargeBearAction(PlayerbotAI* botAI) : CastReachTargetSpellAction(botAI, "feral charge - bear", 1.5f) {}
	};

	class CastGrowlAction : public CastSpellAction
	{
	public:
		CastGrowlAction(PlayerbotAI* botAI) : CastSpellAction(botAI, "growl") {}
	};

	class CastMaulAction : public CastMeleeSpellAction
	{
	public:
		CastMaulAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "maul") {}
		virtual bool isUseful() { return CastMeleeSpellAction::isUseful() && AI_VALUE2(uint8, "rage", "self target") >= 45; }
	};

	class CastBashAction : public CastMeleeSpellAction
	{
	public:
		CastBashAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "bash") {}
	};

	class CastSwipeAction : public CastMeleeSpellAction
	{
	public:
		CastSwipeAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "swipe") {}
	};

	class CastDemoralizingRoarAction : public CastDebuffSpellAction
	{
	public:
		CastDemoralizingRoarAction(PlayerbotAI* botAI) : CastDebuffSpellAction(botAI, "demoralizing roar") {}
	};

	class CastMangleBearAction : public CastMeleeSpellAction
	{
	public:
		CastMangleBearAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "mangle (bear)") {}
	};

	class CastSwipeBearAction : public CastMeleeSpellAction
	{
	public:
		CastSwipeBearAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "swipe (bear)") {}
	};

    class CastLacerateAction : public CastMeleeSpellAction
    {
    public:
        CastLacerateAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "lacerate") {}
    };

    class CastBashOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastBashOnEnemyHealerAction(PlayerbotAI* botAI) : CastSpellOnEnemyHealerAction(botAI, "bash") {}
    };
}
