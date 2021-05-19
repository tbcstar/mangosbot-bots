#pragma once
#include "StatsValues.h"

namespace ai
{

    class AttackerCountValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        AttackerCountValue() : Uint8CalculatedValue(botAI) {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual uint8 Calculate();
    };

    class MyAttackerCountValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        MyAttackerCountValue() : Uint8CalculatedValue(botAI) {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual uint8 Calculate();
    };

    class HasAggroValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasAggroValue() : BoolCalculatedValue(botAI) {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual bool Calculate();
    };

    class BalancePercentValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        BalancePercentValue() : Uint8CalculatedValue(botAI) {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual uint8 Calculate();
    };

}
