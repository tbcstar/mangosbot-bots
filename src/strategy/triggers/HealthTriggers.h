#pragma once
#include "../Trigger.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class ValueInRangeTrigger : public Trigger
    {
    public:
        ValueInRangeTrigger(PlayerbotAI* botAI, string name, float maxValue, float minValue) : Trigger(ai, name) {
            this->maxValue = maxValue;
            this->minValue = minValue;
        }
    public:
        virtual float GetValue() = 0;
        virtual bool IsActive() {
            float value = GetValue();
            return value < maxValue && value >= minValue;
        }

    protected:
        float maxValue, minValue;
    };

	class HealthInRangeTrigger : public ValueInRangeTrigger
	{
	public:
		HealthInRangeTrigger(PlayerbotAI* botAI, string name, float maxValue, float minValue = 0) :
		  ValueInRangeTrigger(ai, name, maxValue, minValue) {}

		virtual bool IsActive()
		{
		    return ValueInRangeTrigger::IsActive() && !AI_VALUE2(bool, "dead", GetTargetName());
		}

		virtual float GetValue();
	};

    class LowHealthTrigger : public HealthInRangeTrigger
    {
    public:
        LowHealthTrigger(PlayerbotAI* botAI, string name = "low health",
            float value = sPlayerbotAIConfig->lowHealth, float minValue = sPlayerbotAIConfig->criticalHealth) :
            HealthInRangeTrigger(ai, name, value, minValue) {}

		virtual string GetTargetName() { return "self target"; }
    };

    class CriticalHealthTrigger : public LowHealthTrigger
    {
    public:
        CriticalHealthTrigger(PlayerbotAI* botAI) :
            LowHealthTrigger(ai, "critical health", sPlayerbotAIConfig->criticalHealth, 0) {}
    };

    class MediumHealthTrigger : public LowHealthTrigger
    {
    public:
        MediumHealthTrigger(PlayerbotAI* botAI) :
            LowHealthTrigger(ai, "medium health", sPlayerbotAIConfig->mediumHealth, sPlayerbotAIConfig->lowHealth) {}
    };

    class AlmostFullHealthTrigger : public LowHealthTrigger
    {
    public:
        AlmostFullHealthTrigger(PlayerbotAI* botAI) :
            LowHealthTrigger(ai, "almost full health", sPlayerbotAIConfig->almostFullHealth, sPlayerbotAIConfig->mediumHealth) {}
    };

    class PartyMemberLowHealthTrigger : public HealthInRangeTrigger
    {
    public:
        PartyMemberLowHealthTrigger(PlayerbotAI* botAI, string name = "party member low health", float value = sPlayerbotAIConfig->lowHealth, float minValue = sPlayerbotAIConfig->criticalHealth) :
            HealthInRangeTrigger(ai, name, value, minValue) {}

        virtual string GetTargetName() { return "party member to heal"; }
    };

    class PartyMemberCriticalHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberCriticalHealthTrigger(PlayerbotAI* botAI) :
            PartyMemberLowHealthTrigger(ai, "party member critical health", sPlayerbotAIConfig->criticalHealth, 0) {}
    };

    class PartyMemberMediumHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberMediumHealthTrigger(PlayerbotAI* botAI) :
            PartyMemberLowHealthTrigger(ai, "party member medium health", sPlayerbotAIConfig->mediumHealth,sPlayerbotAIConfig->lowHealth) {}
    };

    class PartyMemberAlmostFullHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberAlmostFullHealthTrigger(PlayerbotAI* botAI) :
            PartyMemberLowHealthTrigger(ai, "party member almost full health", sPlayerbotAIConfig->almostFullHealth,sPlayerbotAIConfig->mediumHealth) {}
    };

    class TargetLowHealthTrigger : public HealthInRangeTrigger {
    public:
        TargetLowHealthTrigger(PlayerbotAI* botAI, float value, float minValue = 0) :
            HealthInRangeTrigger(ai, "target low health", value, minValue) {}
        virtual string GetTargetName() { return "current target"; }
    };

    class TargetCriticalHealthTrigger : public TargetLowHealthTrigger
    {
    public:
        TargetCriticalHealthTrigger(PlayerbotAI* botAI) : TargetLowHealthTrigger(ai, 20) {}
    };

	class PartyMemberDeadTrigger : public Trigger {
	public:
		PartyMemberDeadTrigger(PlayerbotAI* botAI) : Trigger(ai, "resurrect", 3) {}
        virtual string GetTargetName() { return "party member to resurrect"; }
		virtual bool IsActive();
	};

    class DeadTrigger : public Trigger {
    public:
        DeadTrigger(PlayerbotAI* botAI) : Trigger(ai, "dead", 30) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class AoeHealTrigger : public Trigger {
    public:
    	AoeHealTrigger(PlayerbotAI* botAI, string name, string type, int count) :
    		Trigger(ai, name), type(type), count(count) {}
    public:
        virtual bool IsActive();

    protected:
        int count;
        string type;
    };

}
