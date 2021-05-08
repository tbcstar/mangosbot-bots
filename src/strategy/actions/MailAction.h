#pragma once

#include "../Action.h"
#include "InventoryAction.h"

namespace ai
{

    class MailProcessor
    {
    public:
        virtual bool Before(PlayerbotAI* botAI) { return true; }
        virtual bool Process(int index, Mail* mail, PlayerbotAI* botAI) = 0;
        virtual bool After(PlayerbotAI* botAI) { return true; }

    public:
        static ObjectGuid FindMailbox(PlayerbotAI* botAI);

    protected:
        void RemoveMail(Player* bot, uint32 id, ObjectGuid mailbox);
    };


    class MailAction : public InventoryAction
    {
    public:
        MailAction(PlayerbotAI* botAI) : InventoryAction(ai, "mail") {}

        virtual bool Execute(Event event);

    private:
        bool CheckMailbox();

    private:
        static map<string, MailProcessor*> processors;
    };

}
