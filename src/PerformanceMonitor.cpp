/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "PerformanceMonitor.h"

PerformanceMonitorOperation* PerformanceMonitor::start(PerformanceMetric metric, std::string const& name)
{
    if (!sPlayerbotAIConfig->perfMonEnabled)
        return nullptr;

    std::lock_guard<std::mutex> guard(lock);
    PerformanceData* pd = data[metric][name];
    if (!pd)
    {
        pd = new PerformanceData();
        pd->minTime = 0;
        pd->maxTime = 0;
        pd->totalTime = 0;
        pd->count = 0;
        data[metric][name] = pd;
    }

    return new PerformanceMonitorOperation(pd);
}

void PerformanceMonitor::PrintStats()
{
    for (std::map<PerformanceMetric, std::map<std::string, PerformanceData*> >::iterator i = data.begin(); i != data.end(); ++i)
    {
        std::map<std::string, PerformanceData*> pdMap = i->second;

        std::string key;
        switch (i->first)
        {
            case PERF_MON_TRIGGER:
                key = "T";
                break;
            case PERF_MON_VALUE:
                key = "V";
                break;
            case PERF_MON_ACTION:
                key = "A";
                break;
            case PERF_MON_RNDBOT:
                key = "RndBot";
                break;
            case PERF_MON_TOTAL:
                key = "Total";
                break;
            default:
                key = "?";
                break;
        }

        for (std::map<std::string, PerformanceData*>::iterator j = pdMap.begin(); j != pdMap.end(); ++j)
        {
            PerformanceData* pd = j->second;
            float avg = (float)pd->totalTime / (float)pd->count;
            if (avg >= 0.5f || pd->maxTime > 10)
            {
                LOG_INFO("playerbots", "%6u .. %6u (%.4f of %6u) - %s: %s", pd->minTime, pd->maxTime, avg, pd->count, key.c_str(), j->first.c_str());
            }
        }
    }
}

void PerformanceMonitor::Reset()
{
    for (std::map<PerformanceMetric, std::map<std::string, PerformanceData*> >::iterator i = data.begin(); i != data.end(); ++i)
    {
        std::map<std::string, PerformanceData*> pdMap = i->second;
        for (std::map<std::string, PerformanceData*>::iterator j = pdMap.begin(); j != pdMap.end(); ++j)
        {
            PerformanceData* pd = j->second;
            std::lock_guard<std::mutex> guard(pd->lock);
            pd->minTime = 0;
            pd->maxTime = 0;
            pd->totalTime = 0;
            pd->count = 0;
        }
    }
}

PerformanceMonitorOperation::PerformanceMonitorOperation(PerformanceData* data) : data(data)
{
    started = (std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now())).time_since_epoch();
}

void PerformanceMonitorOperation::finish()
{
    std::chrono::milliseconds finished = (std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now())).time_since_epoch();
    uint32 elapsed = (finished - started).count();

    std::lock_guard<std::mutex> guard(data->lock);
    if (elapsed > 0)
    {
        if (!data->minTime || data->minTime > elapsed)
            data->minTime = elapsed;

        if (!data->maxTime || data->maxTime < elapsed)
            data->maxTime = elapsed;

        data->totalTime += elapsed;
    }

    ++data->count;
    delete this;
}

