#pragma once

namespace ai {
	class CastFeralChargeCatAction : public CastReachTargetSpellAction
	{
	public:
		CastFeralChargeCatAction(PlayerbotAI* botAI) : CastReachTargetSpellAction(ai, "feral charge - cat", 1.5f) {}
	};

	class CastCowerAction : public CastBuffSpellAction
	{
	public:
		CastCowerAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "cower") {}
	};


	class CastBerserkAction : public CastBuffSpellAction
	{
	public:
		CastBerserkAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "berserk") {}
	};

	class CastTigersFuryAction : public CastBuffSpellAction
	{
	public:
		CastTigersFuryAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "tiger's fury") {}
	};

	class CastRakeAction : public CastDebuffSpellAction
	{
	public:
		CastRakeAction(PlayerbotAI* botAI) : CastDebuffSpellAction(ai, "rake") {}
	};


	class CastClawAction : public CastMeleeSpellAction {
	public:
		CastClawAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "claw") {}
	};

	class CastMangleCatAction : public CastMeleeSpellAction {
	public:
		CastMangleCatAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "mangle (cat)") {}
	};

	class CastSwipeCatAction : public CastMeleeSpellAction {
	public:
		CastSwipeCatAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "swipe (cat)") {}
	};

	class CastFerociousBiteAction : public CastMeleeSpellAction {
	public:
		CastFerociousBiteAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "ferocious bite") {}
	};


	class CastRipAction : public CastMeleeSpellAction {
	public:
		CastRipAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "rip") {}
	};



}
