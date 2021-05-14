/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Common.h"
#include "Action.h"
#include "AiObject.h"
#include "Value.h"

class Event;
class PlayerbotAI;
class Unit;

#define NEXT_TRIGGERS(name, relevance) \
    virtual NextAction* getNextAction() { return new NextAction(name, relevance); }

#define BEGIN_TRIGGER(clazz, super) \
class clazz : public super \
{ \
    public: \
        clazz(PlayerbotAI* botAI) : super(botAI) { } \
    public: \
        virtual bool IsActive();

#define END_TRIGGER() \
};

class Trigger : public AiNamedObject
{
	public:
        Trigger(PlayerbotAI* botAI, std::string const& name = "trigger", int checkInterval = 1) : AiNamedObject(botAI, name), checkInterval(checkInterval),
            lastCheckTime(time(0) - rand() % checkInterval) { }

        virtual ~Trigger() { }

        virtual Event Check();
        virtual void ExternalEvent(std::string const& param, Player* owner = NULL) { }
        virtual void ExternalEvent(WorldPacket& packet, Player* owner = NULL) { }
        virtual bool IsActive() { return false; }
        virtual NextAction** getHandlers() { return NULL; }
        void Update() {}
        virtual void Reset() { }
        virtual Unit* GetTarget();
        virtual Value<Unit*>* GetTargetValue();
        virtual std::string const& GetTargetName() { return "self target"; }

		bool needCheck()
        {
		    if (checkInterval < 2)
                return true;

		    time_t now = time(0);
			if (!lastCheckTime || now - lastCheckTime >= checkInterval)
            {
			    lastCheckTime = now;
				return true;
			}

			return false;
		}

    protected:
		int checkInterval;
		time_t lastCheckTime;
};

class TriggerNode
{
    public:
        TriggerNode(std::string const& name, NextAction** handlers = NULL) : name(name), handlers(handlers), trigger(NULL) { }

        virtual ~TriggerNode()
        {
            NextAction::destroy(handlers);
        }

        Trigger* getTrigger() { return trigger; }
        void setTrigger(Trigger* trigger) { this->trigger = trigger; }
        std::string const& getName() { return name; }

        NextAction** getHandlers()
        {
            return NextAction::merge(NextAction::clone(handlers), trigger->getHandlers());
        }

    private:
        Trigger* trigger;
        NextAction** handlers;
        std::string name;
};
