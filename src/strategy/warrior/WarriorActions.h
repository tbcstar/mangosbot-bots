#pragma once
#include "../actions/GenericActions.h"

namespace ai
{
    // all
    class CastHeroicStrikeAction : public CastMeleeSpellAction {
    public:
        CastHeroicStrikeAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "heroic strike") {}
    };

    // all
    class CastCleaveAction : public CastMeleeSpellAction {
    public:
        CastCleaveAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "cleave") {}
    };

    // battle, berserker
    class CastMockingBlowAction : public CastMeleeSpellAction {
    public:
        CastMockingBlowAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "mocking blow") {}
    };

    class CastBloodthirstAction : public CastMeleeSpellAction {
    public:
        CastBloodthirstAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "bloodthirst") {}
    };

    // battle, berserker
    class CastExecuteAction : public CastMeleeSpellAction {
    public:
        CastExecuteAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "execute") {}
    };

    // battle
    class CastOverpowerAction : public CastMeleeSpellAction {
    public:
        CastOverpowerAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "overpower") {}
    };

    // battle, berserker
    class CastHamstringAction : public CastSnareSpellAction {
    public:
        CastHamstringAction(PlayerbotAI* botAI) : CastSnareSpellAction(ai, "hamstring") {}
    };

    // defensive
    class CastTauntAction : public CastMeleeSpellAction {
    public:
        CastTauntAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "taunt") {}
    };

    // defensive
    class CastShieldBlockAction : public CastBuffSpellAction {
    public:
        CastShieldBlockAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "shield block") {}
    };

    // defensive
    class CastShieldWallAction : public CastMeleeSpellAction {
    public:
        CastShieldWallAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "shield wall") {}
    };

    class CastBloodrageAction : public CastBuffSpellAction {
    public:
        CastBloodrageAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "bloodrage") {}
    };

    // defensive
    class CastDevastateAction : public CastMeleeSpellAction {
    public:
        CastDevastateAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "devastate") {}
    };

    // all
    class CastSlamAction : public CastMeleeSpellAction {
    public:
        CastSlamAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "slam") {}
    };

	// all
	class CastShieldSlamAction : public CastMeleeSpellAction {
	public:
		CastShieldSlamAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "shield slam") {}
	};

    // after dodge
    BEGIN_MELEE_SPELL_ACTION(CastRevengeAction, "revenge")
    END_SPELL_ACTION()


    //debuffs
    BEGIN_DEBUFF_ACTION(CastRendAction, "rend")
    END_SPELL_ACTION()

    class CastRendOnAttackerAction : public CastDebuffSpellOnAttackerAction
    {
    public:
        CastRendOnAttackerAction(PlayerbotAI* botAI) : CastDebuffSpellOnAttackerAction(ai, "rend") {}
    };

    BEGIN_DEBUFF_ACTION(CastDisarmAction, "disarm")
    END_SPELL_ACTION()

    class CastSunderArmorAction : public CastDebuffSpellAction
    {
    public:
        CastSunderArmorAction(PlayerbotAI* botAI) : CastDebuffSpellAction(ai, "sunder armor") {
            range = ATTACK_DISTANCE;
        }
        virtual bool isUseful() { return CastSpellAction::isUseful(); }
    };

    class CastDemoralizingShoutAction : public CastDebuffSpellAction {
    public:
        CastDemoralizingShoutAction(PlayerbotAI* botAI) : CastDebuffSpellAction(ai, "demoralizing shout") {
            range = ATTACK_DISTANCE;
        }
    };

    BEGIN_MELEE_SPELL_ACTION(CastChallengingShoutAction, "challenging shout")
    END_SPELL_ACTION()

    // stuns
    BEGIN_MELEE_SPELL_ACTION(CastShieldBashAction, "shield bash")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastIntimidatingShoutAction, "intimidating shout")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastThunderClapAction, "thunder clap")
    END_SPELL_ACTION()

    // buffs
	class CastBattleShoutAction : public CastBuffSpellAction {
	public:
		CastBattleShoutAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "battle shout") {
		    range = ATTACK_DISTANCE;
		}
		virtual bool isUseful() { return CastSpellAction::isUseful(); }
	};

	class CastDefensiveStanceAction : public CastBuffSpellAction {
	public:
		CastDefensiveStanceAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "defensive stance") {}
	};

	class CastBattleStanceAction : public CastBuffSpellAction {
	public:
		CastBattleStanceAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "battle stance") {}
	};

    BEGIN_RANGED_SPELL_ACTION(CastChargeAction, "charge")
    END_SPELL_ACTION()

	class CastDeathWishAction : public CastBuffSpellAction {
	public:
		CastDeathWishAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "death wish") {}
	};

	class CastBerserkerRageAction : public CastBuffSpellAction {
	public:
		CastBerserkerRageAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "berserker rage") {}
	};

	class CastLastStandAction : public CastBuffSpellAction {
	public:
		CastLastStandAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "last stand") {}
	};

	// defensive
	class CastShockwaveAction : public CastMeleeSpellAction {
	public:
		CastShockwaveAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "shockwave") {}
	};

	// defensive
	class CastConcussionBlowAction : public CastSnareSpellAction {
	public:
		CastConcussionBlowAction(PlayerbotAI* botAI) : CastSnareSpellAction(ai, "concussion blow") {}
	};

	BEGIN_MELEE_SPELL_ACTION(CastVictoryRushAction, "victory rush")
	END_SPELL_ACTION()

    class CastShieldBashOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastShieldBashOnEnemyHealerAction(PlayerbotAI* botAI) : CastSpellOnEnemyHealerAction(ai, "shield bash") {}
    };

    class CastBattleShoutTauntAction : public CastMeleeSpellAction
    {
    public:
	    CastBattleShoutTauntAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "battle shout") {}
	    virtual bool isUseful() { return CastSpellAction::isUseful(); }
    };
}
