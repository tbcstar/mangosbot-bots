#pragma once
#include "../Value.h"

class Unit;

namespace botAI
{
    class HealthValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        HealthValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual uint8 Calculate();
    };

    class IsDeadValue : public BoolCalculatedValue, public Qualified
    {
    public:
        IsDeadValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual bool Calculate();
    };

    class PetIsDeadValue : public BoolCalculatedValue
    {
    public:
        PetIsDeadValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }
        virtual bool Calculate();
    };

    class PetIsHappyValue : public BoolCalculatedValue
    {
    public:
        PetIsHappyValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }
        virtual bool Calculate();
    };

    class RageValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        RageValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual uint8 Calculate();
    };

    class EnergyValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        EnergyValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual uint8 Calculate();
    };

    class ManaValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        ManaValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual uint8 Calculate();
    };

    class HasManaValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasManaValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual bool Calculate();
    };

    class ComboPointsValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        ComboPointsValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual uint8 Calculate();
    };

    class IsMountedValue : public BoolCalculatedValue, public Qualified
    {
    public:
        IsMountedValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual bool Calculate();
    };

    class IsInCombatValue : public BoolCalculatedValue, public Qualified
    {
    public:
        IsInCombatValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual bool Calculate() ;
    };

    class BagSpaceValue : public Uint8CalculatedValue
    {
    public:
        BagSpaceValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

        virtual uint8 Calculate();
    };

    class SpeedValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        SpeedValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual uint8 Calculate();
    };

    class IsInGroupValue : public BoolCalculatedValue
    {
    public:
        IsInGroupValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }

        virtual bool Calculate() { return bot->GetGroup(); }
    };
}
