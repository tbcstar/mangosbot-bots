#ifndef _ServerFacade_H
#define _ServerFacade_H

#include "Common.h"
#include "PlayerbotAIBase.h"
#include "PlayerbotAIConfig.h"

using namespace std;

class ServerFacade
{
    public:
        ServerFacade();
        virtual ~ServerFacade();
        static ServerFacade* instance()
        {
            static ServerFacade instance;
            return &instance;
        }

	public:
        bool UnitIsDead(Unit *unit)
        {
            return unit->isDead();
        }

        float GetDistance2d(Unit *unit, WorldObject* wo);

        float GetDistance2d(Unit *unit, float x, float y);

        DeathState GetDeathState(Unit *unit)
        {
            return unit->getDeathState();
        }

        bool isSpawned(GameObject *go)
        {
            return go->isSpawned();
        }

        bool IsAlive(Unit *unit)
        {
            return unit->IsAlive();
        }

        bool isMoving(Unit *unit);

        bool IsInCombat(Unit *unit)
        {
            return unit->IsInCombat();
        }

        bool IsFrozen(Unit *unit)
        {
            return unit->isFrozen();
        }

        bool IsInRoots(Unit *unit)
        {
            return unit->isInRoots();
        }

        bool IsCharmed(Unit *unit)
        {
            return unit->GetCharmerGuid() && unit->GetCharmerGuid().IsPlayer();
        }

        bool IsFeared(Unit *unit)
        {
            return unit->isFeared();
        }

        bool IsInFront(Unit *unit, WorldObject const* target, float distance,  float arc /*= M_PI_F*/)
        {
            return unit->isInFront(target, distance, arc);
        }

        HostileRefManager& GetHostileRefManager(Unit *unit)
        {
            return unit->getHostileRefManager();
        }

        ThreatManager& GetThreatManager(Unit *unit)
        {
            return unit->getThreatManager();
        }

        void SendPacket(Player *player, WorldPacket &packet)
        {
            return player->GetSession()->SendPacket(&packet);
        }

        void SendMessageToSet(Player *player, WorldPacket &packet, bool self)
        {
            return player->SendMessageToSet(&packet, self);
        }

        SpellEntry const* LookupSpellInfo(uint32 spellId)
        {
            return sSpellStore.LookupEntry(spellId);
        }

        uint32 GetSpellInfoRows()
        {
            return sSpellStore.GetNumRows();
        }

        bool IsWithinLOSInMap(Player* bot, WorldObject *wo)
        {
            return bot->IsWithinLOSInMap(wo);
        }

        bool IsDistanceLessThan(float dist1, float dist2);
        bool IsDistanceGreaterThan(float dist1, float dist2);
        bool IsDistanceGreaterOrEqualThan(float dist1, float dist2);
        bool IsDistanceLessOrEqualThan(float dist1, float dist2);

        void SetFacingTo(Player* bot, WorldObject* wo, bool force = false);

        bool IsFriendlyTo(Unit* bot, Unit* to);
        bool IsHostileTo(Unit* bot, Unit* to);

        bool IsSpellReady(Player* bot, uint32 spell);

        bool IsUnderwater(Unit *unit);
        FactionTemplateEntry const* GetFactionTemplateEntry(Unit *unit);
        Unit* GetChaseTarget(Unit* target);
};

#define sServerFacade ServerFacade::instance()

#endif
