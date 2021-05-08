#pragma once

#include "../Action.h"
#include "../../RandomPlayerbotMgr.h"

namespace ai
{
    class LeaveGroupAction : public Action {
    public:
        LeaveGroupAction(PlayerbotAI* botAI, string name = "leave") : Action(ai, name) {}

        virtual bool Execute(Event event)
        {
            if (!bot->GetGroup())
                return false;

            botAI->TellMaster("Goodbye!", PLAYERBOT_SECURITY_TALK);

            WorldPacket p;
            string member = bot->GetName();
            p << uint32(PARTY_OP_LEAVE) << member << uint32(0);
            bot->GetSession()->HandleGroupDisbandOpcode(p);

            bool randomBot = sRandomPlayerbotMgr->IsRandomBot(bot);
            if (randomBot)
            {
                bot->GetPlayerbotAI()->SetMaster(NULL);
                sRandomPlayerbotMgr->ScheduleTeleport(bot->GetGUID());
            }

            botAI->ResetStrategies(!randomBot);
            return true;
        }
    };

    class PartyCommandAction : public LeaveGroupAction {
    public:
        PartyCommandAction(PlayerbotAI* botAI) : LeaveGroupAction(ai, "party command") {}

        virtual bool Execute(Event event)
        {
            WorldPacket& p = event.getPacket();
            p.rpos(0);
            uint32 operation;
            string member;

            p >> operation >> member;

            if (operation != PARTY_OP_LEAVE)
                return false;

            Player* master = GetMaster();
            if (master && member == master->GetName())
                return LeaveGroupAction::Execute(event);

            return false;
        }
    };

    class UninviteAction : public LeaveGroupAction {
    public:
        UninviteAction(PlayerbotAI* botAI) : LeaveGroupAction(ai, "party command") {}

        virtual bool Execute(Event event)
        {
            WorldPacket& p = event.getPacket();
            p.rpos(0);
            ObjectGuid guid;

            p >> guid;

            if (bot->GetGUID() == guid)
                return LeaveGroupAction::Execute(event);

            return false;
        }
    };

}
