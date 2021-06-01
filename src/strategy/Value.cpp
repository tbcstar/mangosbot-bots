/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Value.h"
#include "PerformanceMonitor.h"

template<class T>
T CalculatedValue<T>::Get()
{
    time_t now = time(0);
    if (!lastCheckTime || checkInterval < 2 || now - lastCheckTime >= checkInterval / 2)
    {
        lastCheckTime = now;

        PerformanceMonitorOperation* pmo = sPerformanceMonitor->start(PERF_MON_VALUE, getName());
        value = Calculate();
        if (pmo)
            pmo->finish();
    }

    return value;
}

std::string const& UnitCalculatedValue::Format()
{
    Unit* unit = Calculate();
    return unit ? unit->GetName() : "<none>";
}

std::string const& UnitManualSetValue::Format()
{
    Unit* unit = Get();
    return unit ? unit->GetName() : "<none>";
}

