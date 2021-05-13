#pragma once

#include "../Action.h"

namespace ai
{
    class AcceptInvitationAction : public Action {
    public:
        AcceptInvitationAction(PlayerbotAI* botAI) : Action(ai, "accept invitation") {}

        virtual bool Execute(Event event)
        {
            Player* master = GetMaster();

            Group* grp = bot->GetGroupInvite();
            if (!grp)
                return false;

            Player* inviter = ObjectAccessor::FindPlayer(grp->GetLeaderGUID());
            if (!inviter)
                return false;

			if (!botAI->GetSecurity()->CheckLevelFor(PLAYERBOT_SECURITY_INVITE, false, inviter))
            {
                WorldPacket data(SMSG_GROUP_DECLINE, 10);
                data << bot->GetName();
                sServerFacade->SendPacket(inviter, data);
                bot->UninviteFromGroup();
                return false;
            }

            WorldPacket p;
            uint32 roles_mask = 0;
            p << roles_mask;
            bot->GetSession()->HandleGroupAcceptOpcode(p);

            if (sRandomPlayerbotMgr->IsRandomBot(bot))
                bot->GetPlayerbotAI()->SetMaster(inviter);

            botAI->ResetStrategies();
            botAI->TellMaster("Hello");
            return true;
        }
    };

}
