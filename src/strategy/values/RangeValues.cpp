#include "botpch.h"
#include "../../playerbot.h"
#include "RangeValues.h"

using namespace botAI;

RangeValue::RangeValue(PlayerbotAI* botAI)
    : ManualSetValue<float>(botAI, 0, "range"), Qualified()
{
}

string RangeValue::Save()
{
    ostringstream out; out << value; return out.str();
}

bool RangeValue::Load(string text)
{
    value = atof(text.c_str());
    return true;
}
