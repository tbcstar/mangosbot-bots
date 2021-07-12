/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NamedObjectContext.h"
#include "Value.h"
class AttackerCountValue : public Uint8CalculatedValue, public Qualified
{
    public:
        AttackerCountValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

        Unit* GetTarget();
        uint8 Calculate() override;
};

class MyAttackerCountValue : public Uint8CalculatedValue, public Qualified
{
    public:
        MyAttackerCountValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

        Unit* GetTarget();
        uint8 Calculate() override;
};

class HasAggroValue : public BoolCalculatedValue, public Qualified
{
    public:
        HasAggroValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }

        Unit* GetTarget();
        bool Calculate() override;
};

class BalancePercentValue : public Uint8CalculatedValue, public Qualified
{
    public:
        BalancePercentValue(PlayerbotAI* botAI) : Uint8CalculatedValue(botAI) { }

        Unit* GetTarget();
        uint8 Calculate() override;
};
