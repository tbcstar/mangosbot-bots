#include "botpch.h"
#include "../../playerbot.h"
#include "AcceptQuestAction.h"

using namespace ai;

void AcceptAllQuestsAction::ProcessQuest(Quest const* quest, WorldObject* questGiver)
{
    AcceptQuest(quest, questGiver->GetGUID());
}

bool AcceptQuestAction::Execute(Event event)
{
    Player* master = GetMaster();

    if (!master)
        return false;

    Player *bot = botAI->GetBot();
    ObjectGuid guid;
    uint32 quest = 0;

    string text = event.getParam();
    PlayerbotChatHandler ch(master);
    quest = ch.extractQuestId(text);

    if (event.getPacket().empty())
    {
        list<ObjectGuid> npcs = AI_VALUE(list<ObjectGuid>, "nearest npcs");
        for (list<ObjectGuid>::iterator i = npcs.begin(); i != npcs.end(); i++)
        {
            Unit* unit = botAI->GetUnit(*i);
            if (unit && quest && unit->HasQuest(quest))
            {
                guid = unit->GetGUID();
                break;
            }
            if (unit && text == "*" && bot->GetDistance(unit) <= INTERACTION_DISTANCE)
                QuestAction::ProcessQuests(unit);
        }
        list<ObjectGuid> gos = AI_VALUE(list<ObjectGuid>, "nearest game objects");
        for (list<ObjectGuid>::iterator i = gos.begin(); i != gos.end(); i++)
        {
            GameObject* go = botAI->GetGameObject(*i);
            if (go && quest && go->HasQuest(quest))
            {
                guid = go->GetGUID();
                break;
            }
            if (go && text == "*" && bot->GetDistance(go) <= INTERACTION_DISTANCE)
                QuestAction::ProcessQuests(go);
        }
    }
    else
    {
        WorldPacket& p = event.getPacket();
        p.rpos(0);
        p >> guid >> quest;
    }

    if (!quest || !guid)
        return false;

    Quest const* qInfo = sObjectMgr->GetQuestTemplate(quest);
    if (!qInfo)
        return false;

    return AcceptQuest(qInfo, guid);
}

bool AcceptQuestShareAction::Execute(Event event)
{
    Player* master = GetMaster();
    Player *bot = botAI->GetBot();

    WorldPacket& p = event.getPacket();
    p.rpos(0);
    uint32 quest;
    p >> quest;
    Quest const* qInfo = sObjectMgr->GetQuestTemplate(quest);

    if (!qInfo || !bot->GetDivider())
        return false;

    quest = qInfo->GetQuestId();
    if( !bot->CanTakeQuest( qInfo, false ) )
    {
        // can't take quest
        bot->SetDivider(ObjectGuid::Empty);
        botAI->TellError("I can't take this quest");

        return false;
    }

    if( !bot->GetDivider().IsEmpty() )
    {
        // send msg to quest giving player
        master->SendPushToPartyResponse( bot, QUEST_PARTY_MSG_ACCEPT_QUEST );
        bot->SetDivider(ObjectGuid::Empty);
    }

    if( bot->CanAddQuest( qInfo, false ) )
    {
        bot->AddQuest( qInfo, master );

        if( bot->CanCompleteQuest( quest ) )
            bot->CompleteQuest( quest );

        // Runsttren: did not add typeid switch from WorldSession::HandleQuestgiverAcceptQuestOpcode!
        // I think it's not needed, cause typeid should be TYPEID_PLAYER - and this one is not handled
        // there and there is no default case also.

        if( qInfo->GetSrcSpell() > 0 )
        {
            bot->CastSpell( bot, qInfo->GetSrcSpell(), true);
        }

        botAI->TellMaster("Quest accepted");
        return true;
    }

    return false;
}
