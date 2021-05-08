#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace ai
{
   
    class SpellCastUsefulValue : public BoolCalculatedValue, public Qualified
	{
	public:
        SpellCastUsefulValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) {}
      
    public:
        virtual bool Calculate();

    };
}
