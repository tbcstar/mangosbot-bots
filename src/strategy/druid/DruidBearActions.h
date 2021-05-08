#pragma once

namespace ai {
	class CastFeralChargeBearAction : public CastReachTargetSpellAction
	{
	public:
		CastFeralChargeBearAction(PlayerbotAI* botAI) : CastReachTargetSpellAction(ai, "feral charge - bear", 1.5f) {}
	};

	class CastGrowlAction : public CastSpellAction
	{
	public:
		CastGrowlAction(PlayerbotAI* botAI) : CastSpellAction(ai, "growl") {}
	};

	class CastMaulAction : public CastMeleeSpellAction
	{
	public:
		CastMaulAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "maul") {}
		virtual bool isUseful() { return CastMeleeSpellAction::isUseful() && AI_VALUE2(uint8, "rage", "self target") >= 45; }
	};

	class CastBashAction : public CastMeleeSpellAction
	{
	public:
		CastBashAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "bash") {}
	};

	class CastSwipeAction : public CastMeleeSpellAction
	{
	public:
		CastSwipeAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "swipe") {}
	};

	class CastDemoralizingRoarAction : public CastDebuffSpellAction
	{
	public:
		CastDemoralizingRoarAction(PlayerbotAI* botAI) : CastDebuffSpellAction(ai, "demoralizing roar") {}
	};

	class CastMangleBearAction : public CastMeleeSpellAction
	{
	public:
		CastMangleBearAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "mangle (bear)") {}
	};

	class CastSwipeBearAction : public CastMeleeSpellAction
	{
	public:
		CastSwipeBearAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "swipe (bear)") {}
	};

    class CastLacerateAction : public CastMeleeSpellAction
    {
    public:
        CastLacerateAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "lacerate") {}
    };

    class CastBashOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastBashOnEnemyHealerAction(PlayerbotAI* botAI) : CastSpellOnEnemyHealerAction(ai, "bash") {}
    };
}
