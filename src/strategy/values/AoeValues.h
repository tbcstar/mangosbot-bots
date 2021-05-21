#pragma once
#include "../Value.h"

namespace botAI
{
    class AoePositionValue : public CalculatedValue<WorldLocation>
	{
	public:
        AoePositionValue() : CalculatedValue<WorldLocation>(botAI, "aoe position") { }

	public:
        virtual WorldLocation Calculate();
    };

    class AoeCountValue : public CalculatedValue<uint8>
	{
	public:
        AoeCountValue() : CalculatedValue<uint8>(botAI, "aoe count") { }

	public:
        virtual uint8 Calculate();
    };
}
