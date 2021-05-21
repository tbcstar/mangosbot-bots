/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Common.h"
#include "NamedObjectContext.h"
#include "Value.h"
#include "../PlayerbotAIAware.h"

class Action;
class PlayerbotAI;
class Strategy;
class Trigger;

class AiObjectContext : public PlayerbotAIAware
{
    public:
        AiObjectContext(PlayerbotAI* botAI);
        virtual ~AiObjectContext() { }

        virtual Strategy* GetStrategy(std::string const& name);
        virtual std::set<std::string> GetSiblingStrategy(std::string const& name);
        virtual Trigger* GetTrigger(std::string const& name);
        virtual Action* GetAction(std::string const& name);
        virtual UntypedValue* GetUntypedValue(std::string const& name);

        template<class T>
        Value<T>* GetValue(std::string const& name);

        template<class T>
        Value<T>* GetValue(std::string const& name, std::string const& param);

        template<class T>
        Value<T>* GetValue(std::string const& name, uint32 param);

        std::set<std::string> GetSupportedStrategies();
        std::string FormatValues();

        virtual void Update();
        virtual void Reset();
        virtual void AddShared(NamedObjectContext<UntypedValue>* sharedValues);

        std::vector<std::string> Save();
        void Load(std::vector<std::string> data);

    protected:
        NamedObjectContextList<Strategy> strategyContexts;
        NamedObjectContextList<Action> actionContexts;
        NamedObjectContextList<Trigger> triggerContexts;
        NamedObjectContextList<UntypedValue> valueContexts;
};
