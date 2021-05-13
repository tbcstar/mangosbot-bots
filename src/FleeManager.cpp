/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "FleeManager.h"
#include "Playerbot.h"
#include "ServerFacade.h"
#include "strategy/AiObjectContext.h"

void FleeManager::calculateDistanceToCreatures(FleePoint *point)
{
    point->minDistance = -1.0f;
    point->sumDistance = 0.0f;
	GuidVector units = *bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<GuidVector>("possible targets");
	for (GuidVector::iterator i = units.begin(); i != units.end(); ++i)
    {
		Unit* unit = bot->GetPlayerbotAI()->GetUnit(*i);
		if (!unit)
		    continue;

		float d = sServerFacade->GetDistance2d(unit, point->x, point->y);
		point->sumDistance += d;
		if (point->minDistance < 0 || point->minDistance > d)
            point->minDistance = d;
	}
}

bool intersectsOri(float angle, std::vector<float>& angles, float angleIncrement)
{
    for (std::vector<float>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        float ori = *i;
        if (abs(angle - ori) < angleIncrement)
            return true;
    }

    return false;
}

void FleeManager::calculatePossibleDestinations(std::vector<FleePoint*> &points)
{
    Unit* target = *bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<Unit*>("current target");

	float botPosX = bot->GetPositionX();
	float botPosY = bot->GetPositionY();
	float botPosZ = bot->GetPositionZ();

	FleePoint start(bot->GetPlayerbotAI(), botPosX, botPosY, botPosZ);
	calculateDistanceToCreatures(&start);

    std::vector<float> enemyOri;
    GuidVector units = *bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<GuidVector>("possible targets");
    for (GuidVector::iterator i = units.begin(); i != units.end(); ++i)
    {
        Unit* unit = bot->GetPlayerbotAI()->GetUnit(*i);
        if (!unit)
            continue;

        float ori = bot->GetAngle(unit);
        enemyOri.push_back(ori);
    }

    float distIncrement = max(sPlayerbotAIConfig->followDistance, (maxAllowedDistance - sPlayerbotAIConfig->tooCloseDistance) / 10.0f);
    for (float dist = maxAllowedDistance; dist >= sPlayerbotAIConfig->tooCloseDistance ; dist -= distIncrement)
    {
        float angleIncrement = max(M_PI / 20, M_PI / 4 / (1.0 + dist - sPlayerbotAIConfig->tooCloseDistance));
        for (float add = 0.0f; add < M_PI / 4 + angleIncrement; add += angleIncrement)
        {
            for (float angle = add; angle < add + 2 * M_PI + angleIncrement; angle += M_PI / 4)
            {
                if (intersectsOri(angle, enemyOri, angleIncrement))
                    continue;

                float x = botPosX + cos(angle) * maxAllowedDistance, y = botPosY + sin(angle) * maxAllowedDistance, z = botPosZ + CONTACT_DISTANCE;
                if (forceMaxDistance && sServerFacade->IsDistanceLessThan(sServerFacade->GetDistance2d(bot, x, y), maxAllowedDistance - sPlayerbotAIConfig->tooCloseDistance))
                    continue;

                bot->UpdateAllowedPositionZ(x, y, z);

                Map* map = bot->GetMap();
                if (map && map->IsInWater(x, y, z))
                    continue;

                if (!bot->IsWithinLOS(x, y, z) || (target && !target->IsWithinLOS(x, y, z)))
                    continue;

                FleePoint *point = new FleePoint(bot->GetPlayerbotAI(), x, y, z);
                calculateDistanceToCreatures(point);

                if (sServerFacade->IsDistanceGreaterOrEqualThan(point->minDistance - start.minDistance, sPlayerbotAIConfig->followDistance))
                    points.push_back(point);
            }
        }
    }
}

void FleeManager::cleanup(std::vector<FleePoint*> &points)
{
	for (std::vector<FleePoint*>::iterator i = points.begin(); i != points.end(); i++)
    {
		delete *i;
	}

	points.clear();
}

bool FleeManager::isBetterThan(FleePoint* point, FleePoint* other)
{
    return point->sumDistance - other->sumDistance > 0;
}

FleePoint* FleeManager::selectOptimalDestination(std::vector<FleePoint*> &points)
{
	FleePoint* best = NULL;
	for (std::vector<FleePoint*>::iterator i = points.begin(); i != points.end(); i++)
    {
		FleePoint* point = *i;
		if (!best || isBetterThan(point, best))
            best = point;
	}

	return best;
}

bool FleeManager::CalculateDestination(float* rx, float* ry, float* rz)
{
    std::vector<FleePoint*> points;
	calculatePossibleDestinations(points);

    FleePoint* point = selectOptimalDestination(points);
    if (!point)
    {
        cleanup(points);
        return false;
    }

	*rx = point->x;
	*ry = point->y;
	*rz = point->z;

    cleanup(points);
	return true;
}

bool FleeManager::isUseful()
{
    GuidVector units = *bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<GuidVector>("possible targets");
    for (GuidVector::iterator i = units.begin(); i != units.end(); ++i)
    {
        Unit* unit = bot->GetPlayerbotAI()->GetUnit(*i);
        if (!unit)
            continue;

        float d = sServerFacade->GetDistance2d(unit, bot);
        if (sServerFacade->IsDistanceLessThan(d, sPlayerbotAIConfig->aggroDistance))
            return true;
    }

    return false;
}
