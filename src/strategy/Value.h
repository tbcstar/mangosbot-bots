#pragma once
#include "Action.h"
#include "Event.h"
#include "../PlayerbotAIAware.h"
#include "../PerformanceMonitor.h"
#include "AiObject.h"

namespace ai
{
    class UntypedValue : public AiNamedObject
    {
    public:
        UntypedValue(PlayerbotAI* botAI, string name) : AiNamedObject(ai, name) {}
        virtual void Update() {}
        virtual void Reset() {}
        virtual string Format() { return "?"; }
        virtual string Save() { return "?"; }
        virtual bool Load(string value) { return false; }
    };

    template<class T>
    class Value
    {
    public:
        virtual T Get() = 0;
        virtual void Set(T value) = 0;
        operator T() { return Get(); }
    };

    template<class T>
    class CalculatedValue : public UntypedValue, public Value<T>
	{
	public:
        CalculatedValue(PlayerbotAI* botAI, string name = "value", int checkInterval = 1) : UntypedValue(ai, name),
            checkInterval(checkInterval)
        {
            lastCheckTime = time(0) - rand() % checkInterval;
        }
        virtual ~CalculatedValue() {}

	public:
        virtual T Get()
        {
            time_t now = time(0);
            if (!lastCheckTime || checkInterval < 2 || now - lastCheckTime >= checkInterval / 2)
            {
                lastCheckTime = now;

                PerformanceMonitorOperation *pmo = sPerformanceMonitor->start(PERF_MON_VALUE, getName());
                value = Calculate();
                if (pmo) pmo->finish();
            }
            return value;
        }
        virtual void Set(T value) { this->value = value; }
        virtual void Update() { }

    protected:
        virtual T Calculate() = 0;

    protected:
		int checkInterval;
		time_t lastCheckTime;
        T value;
	};

    class Uint8CalculatedValue : public CalculatedValue<uint8>
    {
    public:
        Uint8CalculatedValue(PlayerbotAI* botAI, string name = "value", int checkInterval = 1) :
            CalculatedValue<uint8>(ai, name, checkInterval) {}

        virtual string Format()
        {
            ostringstream out; out << (int)Calculate();
            return out.str();
        }
    };

    class Uint32CalculatedValue : public CalculatedValue<uint32>
    {
    public:
        Uint32CalculatedValue(PlayerbotAI* botAI, string name = "value", int checkInterval = 1) :
            CalculatedValue<uint32>(ai, name, checkInterval) {}

        virtual string Format()
        {
            ostringstream out; out << (int)Calculate();
            return out.str();
        }
    };

    class FloatCalculatedValue : public CalculatedValue<float>
    {
    public:
        FloatCalculatedValue(PlayerbotAI* botAI, string name = "value", int checkInterval = 1) :
            CalculatedValue<float>(ai, name, checkInterval) {}

        virtual string Format()
        {
            ostringstream out; out << Calculate();
            return out.str();
        }
    };

    class BoolCalculatedValue : public CalculatedValue<bool>
    {
    public:
        BoolCalculatedValue(PlayerbotAI* botAI, string name = "value", int checkInterval = 1) :
            CalculatedValue<bool>(ai, name, checkInterval) {}

        virtual string Format()
        {
            return Calculate() ? "true" : "false";
        }
    };

    class UnitCalculatedValue : public CalculatedValue<Unit*>
    {
    public:
        UnitCalculatedValue(PlayerbotAI* botAI, string name = "value", int checkInterval = 1) :
            CalculatedValue<Unit*>(ai, name, checkInterval) {}

        virtual string Format()
        {
            Unit* unit = Calculate();
            return unit ? unit->GetName() : "<none>";
        }
    };

    class ObjectGuidListCalculatedValue : public CalculatedValue<list<ObjectGuid> >
    {
    public:
        ObjectGuidListCalculatedValue(PlayerbotAI* botAI, string name = "value", int checkInterval = 1) :
            CalculatedValue<list<ObjectGuid> >(ai, name, checkInterval) {}

        virtual string Format()
        {
            ostringstream out; out << "{";
            list<ObjectGuid> guids = Calculate();
            for (list<ObjectGuid>::iterator i = guids.begin(); i != guids.end(); ++i)
            {
                ObjectGuid guid = *i;
                out << guid.GetRawValue() << ",";
            }
            out << "}";
            return out.str();
        }
    };

    template<class T>
    class ManualSetValue : public UntypedValue, public Value<T>
    {
    public:
        ManualSetValue(PlayerbotAI* botAI, T defaultValue, string name = "value") :
            UntypedValue(ai, name), value(defaultValue), defaultValue(defaultValue) {}
        virtual ~ManualSetValue() {}

    public:
        virtual T Get() { return value; }
        virtual void Set(T value) { this->value = value; }
        virtual void Update() { }
        virtual void Reset() { value = defaultValue; }

    protected:
        T value;
        T defaultValue;
    };

    class UnitManualSetValue : public ManualSetValue<Unit*>
    {
    public:
        UnitManualSetValue(PlayerbotAI* botAI, Unit* defaultValue, string name = "value") :
            ManualSetValue<Unit*>(ai, defaultValue, name) {}

        virtual string Format()
        {
            Unit* unit = Get();
            return unit ? unit->GetName() : "<none>";
        }
    };
}
