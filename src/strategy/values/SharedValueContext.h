/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "NamedObjectContext.h"
#include "PvpValues.h"
#include "QuestValues.h"

class PlayerbotAI;

class SharedValueContext : public NamedObjectContext<UntypedValue>
{
    public:
        SharedValueContext() : NamedObjectContext(true)
        {
            creators["bg masters"] = &SharedValueContext::bg_masters;
            creators["quest guidp map"] = &SharedValueContext::quest_guidp_map;
            creators["quest givers"] = &SharedValueContext::quest_givers;
        }

    private:
        static UntypedValue* bg_masters(PlayerbotAI* ai) { return new BgMastersValue(ai); }
        static UntypedValue* quest_guidp_map(PlayerbotAI* ai) { return new QuestGuidpMapValue(ai); }
        static UntypedValue* quest_givers(PlayerbotAI* ai) { return new QuestGiversValue(ai); }

    //Global acess functions
    public:
        static SharedValueContext* instance()
        {
            static SharedValueContext instance;
            return &instance;
        }

        template<class T>
        Value<T>* getGlobalValue(std::string const& name = "");

        template<class T>
        Value<T>* getGlobalValue(std::string const& name, std::string const& param);

        template<class T>
        Value<T>* getGlobalValue(std::string const& name, uint32 param);
};

#define sSharedValueContext SharedValueContext::instance()
