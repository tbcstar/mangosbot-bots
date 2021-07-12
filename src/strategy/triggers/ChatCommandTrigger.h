/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Trigger.h"
class ChatCommandTrigger : public Trigger
{
    public:
        ChatCommandTrigger(PlayerbotAI* botAI, std::string const& command) : Trigger(botAI, command), triggered(false) { }

        void ExternalEvent(std::string const& param, Player* owner = nullptr) override;
        Event Check() override;
        void Reset() override;

   private:
        std::string param;
        bool triggered;
        Player* owner;
};
