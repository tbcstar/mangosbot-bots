/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ReviveFromCorpseAction.h"
#include "Event.h"
#include "Playerbot.h"
#include "PlayerbotFactory.h"
#include "ServerFacade.h"

bool ReviveFromCorpseAction::Execute(Event event)
{
    Player* master = GetMaster();
    Corpse* corpse = bot->GetCorpse();

    // follow master when master revives
    WorldPacket& p = event.getPacket();
    if (!p.empty() && p.GetOpcode() == CMSG_RECLAIM_CORPSE && master && !corpse && sServerFacade.IsAlive(bot))
    {
        if (sServerFacade->IsDistanceLessThan(AI_VALUE2(float, "distance", "master target"), sPlayerbotAIConfig.farDistance))
        {
            if (!ai->HasStrategy("follow", BOT_STATE_NON_COMBAT))
            {
                ai->TellMasterNoFacing("Welcome back!");
                ai->ChangeStrategy("+follow,-stay", BOT_STATE_NON_COMBAT);
                return true;
            }
        }
    }

    if (!corpse)
        return false;

    if (corpse->GetGhostTime() + bot->GetCorpseReclaimDelay(corpse->GetType() == CORPSE_RESURRECTABLE_PVP) > time(nullptr))
        return false;

    if (master)
    {
        if (!master->GetPlayerbotAI() && master->isDead() && master->GetCorpse()
            && sServerFacade.IsDistanceLessThan(AI_VALUE2(float, "distance", "master target"), sPlayerbotAIConfig.farDistance))
            return false;
    }

    sLog.outDetail("Bot #%d %s:%d <%s> revives at body", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName());

    WorldPacket packet(CMSG_RECLAIM_CORPSE);
    packet << bot->GetGUID();
    bot->GetSession()->HandleReclaimCorpseOpcode(packet);

    return true;
}

bool FindCorpseAction::Execute(Event event)
{
    if (bot->InBattleGround())
        return false;

    Corpse* corpse = bot->GetCorpse();
    if (!corpse)
        return false;

    if (corpse->GetMapId() != bot->GetMapId())
        return false;

    if (Player* master = GetMaster())
    {
        if (!master->GetPlayerbotAI() &&
            sServerFacade.IsDistanceLessThan(AI_VALUE2(float, "distance", "master target"), sPlayerbotAIConfig.farDistance))
            return false;
    }

    uint32 dCount = AI_VALUE(uint32, "death count");

    if (!ai->HasRealPlayerMaster())
    {
        if (dCount >= 5)
        {
            sLog.outBasic("Bot #%d %s:%d <%s>: died too many times and was sent to an inn", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName());
            context->GetValue<uint32>("death count")->Set(0);
            sRandomPlayerbotMgr.RandomTeleportForRpg(bot);
            return true;
        }
    }

    if (!corpse->IsWithinDistInMap(bot, CORPSE_RECLAIM_RADIUS - 5.f, true))
    {
        float x = corpse->GetPositionX();
        float y = corpse->GetPositionY();
        float z = corpse->GetPositionZ();

        bot->GetMap()->GetReachableRandomPointOnGround(bot->GetPhaseMask(), x, y, z, CORPSE_RECLAIM_RADIUS - 5.0f, true);

        int64 deadTime = time(nullptr) - corpse->GetGhostTime();

        sLog.outDetail("Bot #%d %s:%d <%s> looks for body", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName());

        if (!botAI->AllowActive(ALL_ACTIVITY))
        {
            uint32 delay = sServerFacade.GetDistance2d(bot, corpse) / bot->GetSpeed(MOVE_RUN); //Time a bot would take to travel to it's corpse.
            delay = min(delay, uint32(10 * MINUTE)); //Cap time to get to corpse at 10 minutes.

            if (deadTime > delay)
            {
                bot->GetMotionMaster()->Clear();
                bot->TeleportTo(corpse->GetMapId(), x, y, z, 0);
            }
        }
        else
        {
            if (bot->IsMoving())
                return false;

            bool moved = false;
            if (deadTime < 30 * MINUTE && dCount < 5) //Look for corpse up to 30 minutes.
            {
                if (bot->IsWithinLOS(x, y, z))
                    moved = MoveNear(bot->GetMapId(), x, y, z, 0);
                else
                    moved = MoveTo(bot->GetMapId(), x, y, z, false, false);
            }

            if (!moved)
            {
                moved = ai->DoSpecificAction("spirit healer");

                if (moved)
                    sLog.outBasic("Bot #%d %s:%d <%s> moves to graveyard", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName());
            }

            return moved;
        }

        return false;
    }

    return false;
}

bool FindCorpseAction::isUseful()
{
    if (bot->InBattleground())
        return false;

    return bot->GetCorpse() && !bot->GetCorpse()->IsWithinDistInMap(bot, CORPSE_RECLAIM_RADIUS - 5, true);
}

bool SpiritHealerAction::Execute(Event event)
{
    Corpse* corpse = bot->GetCorpse();
    if (!corpse)
    {
        botAI->TellError("I am not a spirit");
        return false;
    }

    GuidVector npcs = AI_VALUE(GuidVector, "nearest npcs");
    for (ObjectGuid const guid : npcs)
    {
        if (Unit* unit = botAI->GetUnit(guid))
            if (unit->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPIRITHEALER))
            {
                sLog.outBasic("Bot #%d %s:%d <%s> revives at spirit healer", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName());

                PlayerbotChatHandler ch(bot);
                bot->ResurrectPlayer(0.5f);
                bot->SpawnCorpseBones();
                bot->SaveToDB(false, false);
                context->GetValue<Unit*>("current target")->Set(nullptr);
                bot->SetTarget(ObjectGuid::Empty);
                botAI->TellMaster("Hello");

                uint32 dCount = AI_VALUE(uint32, "death count");
                if (dCount > 10)
                    context->GetValue<uint32>("death count")->Set(0);

                return true;
            }
    }

    AreaTableEntry const* zone = GetAreaEntryByAreaID(bot->GetAreaId());

    WorldSafeLocsEntry const* ClosestGrave = nullptr;
    ClosestGrave = sObjectMgr.GetClosestGraveYard(bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ(), bot->GetMapId(), bot->GetTeam());

    if (!ClosestGrave)
    {
        return false;
    }

    float x = ClosestGrave->x;
    float y = ClosestGrave->y;
    float z = ClosestGrave->z;

    bool moved = false;

    if (bot->IsWithinLOS(x, y, z))
        moved = MoveNear(bot->GetMapId(), x, y, z, 0);
    else
        moved = MoveTo(bot->GetMapId(), x, y, z, false, false);

    if (moved)
        return true;

    if (!ai->HasRealPlayerMaster())
        bot->RepopAtGraveyard();

    sLog.outBasic("Bot #%d %s:%d <%s> can't find a spirit healer", bot->GetGUIDLow(), bot->GetTeam() == ALLIANCE ? "A" : "H", bot->getLevel(), bot->GetName());

    ai->TellError("Cannot find any spirit healer nearby");
    return false;
}
