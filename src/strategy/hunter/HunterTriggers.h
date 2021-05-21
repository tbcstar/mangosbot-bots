#pragma once

#include "../triggers/GenericTriggers.h"

namespace botAI
{
    BEGIN_TRIGGER(HunterNoStingsActiveTrigger, Trigger)
    END_TRIGGER()

    class HunterAspectOfTheHawkTrigger : public BuffTrigger
    {
    public:
        HunterAspectOfTheHawkTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "aspect of the hawk") {
			checkInterval = 1;
		}
    };

	class HunterAspectOfTheWildTrigger : public BuffTrigger
	{
	public:
		HunterAspectOfTheWildTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "aspect of the wild") {
			checkInterval = 1;
		}
	};

    class HunterAspectOfTheViperTrigger : public BuffTrigger
    {
    public:
        HunterAspectOfTheViperTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "aspect of the viper") { }
        virtual bool IsActive()
        {
            return SpellTrigger::IsActive() && !botAI->HasAura(spell, GetTarget());
        }
    };

    class HunterAspectOfThePackTrigger : public BuffTrigger
    {
    public:
        HunterAspectOfThePackTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "aspect of the pack") { }
        virtual bool IsActive() {
			return BuffTrigger::IsActive() && !botAI->HasAura("aspect of the cheetah", GetTarget());
        };
    };

    BEGIN_TRIGGER(HuntersPetDeadTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(HuntersPetLowHealthTrigger, Trigger)
    END_TRIGGER()

    class BlackArrowTrigger : public DebuffTrigger
    {
    public:
        BlackArrowTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "black arrow") { }
    };

    class HuntersMarkTrigger : public DebuffTrigger
    {
    public:
        HuntersMarkTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "hunter's mark") { }
    };

    class FreezingTrapTrigger : public HasCcTargetTrigger
    {
    public:
        FreezingTrapTrigger(PlayerbotAI* botAI) : HasCcTargetTrigger(botAI, "freezing trap") { }
    };

    class RapidFireTrigger : public BuffTrigger
    {
    public:
        RapidFireTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "rapid fire") { }
    };

    class TrueshotAuraTrigger : public BuffTrigger
    {
    public:
        TrueshotAuraTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "trueshot aura") { }
    };

    class SerpentStingOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        SerpentStingOnAttackerTrigger(PlayerbotAI* botAI) : DebuffOnAttackerTrigger(botAI, "serpent sting") { }
    };

    BEGIN_TRIGGER(HunterPetNotHappy, Trigger)
    END_TRIGGER()

    class ConsussiveShotSnareTrigger : public SnareTargetTrigger
    {
    public:
        ConsussiveShotSnareTrigger(PlayerbotAI* botAI) : SnareTargetTrigger(botAI, "concussive shot") { }
    };

    class ScareBeastTrigger : public HasCcTargetTrigger
    {
    public:
        ScareBeastTrigger(PlayerbotAI* botAI) : HasCcTargetTrigger(botAI, "scare beast") { }
    };
}
