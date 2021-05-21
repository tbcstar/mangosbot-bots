#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace botAI
{
   
    class SpellCastUsefulValue : public BoolCalculatedValue, public Qualified
	{
	public:
        SpellCastUsefulValue(PlayerbotAI* botAI) : BoolCalculatedValue(botAI) { }
      
    public:
        virtual bool Calculate();

    };
}
