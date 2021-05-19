#pragma once
#include "../Value.h"

namespace ai
{
    class AoePositionValue : public CalculatedValue<WorldLocation>
	{
	public:
        AoePositionValue() : CalculatedValue<WorldLocation>(ai, "aoe position") {}

	public:
        virtual WorldLocation Calculate();
    };

    class AoeCountValue : public CalculatedValue<uint8>
	{
	public:
        AoeCountValue() : CalculatedValue<uint8>(ai, "aoe count") {}

	public:
        virtual uint8 Calculate();
    };
}
