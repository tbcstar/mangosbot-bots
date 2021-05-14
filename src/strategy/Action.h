/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AiObject.h"
#include "Common.h"
#include "Value.h"

class Event;
class PlayerbotAI;
class Unit;

enum ActionThreatType
{
    ACTION_THREAT_NONE      = 0,
    ACTION_THREAT_SINGLE    = 1,
    ACTION_THREAT_AOE       = 2
};

class NextAction
{
    public:
        NextAction(std::string name, float relevance = 0.0f) : name(name), relevance(relevance) { }
        NextAction(NextAction const& o) : name(o.name), relevance(o.relevance) { }

        std::string const& getName() { return name; }
        float getRelevance() {return relevance;}

        static uint32 size(NextAction** actions);
        static NextAction** clone(NextAction** actions);
        static NextAction** merge(NextAction** what, NextAction** with);
        static NextAction** array(uint8 nil,...);
        static void destroy(NextAction** actions);

    private:
        float relevance;
        std::string name;
};

class Action : public AiNamedObject
{
	public:
        Action(PlayerbotAI* botAI, std::string name = "action") : verbose(false), AiNamedObject(ai, name) { }
        virtual ~Action(void) { }

        virtual bool Execute(Event event) { return true; }
        virtual bool isPossible() { return true; }
        virtual bool isUseful() { return true; }
        virtual NextAction** getPrerequisites() { return NULL; }
        virtual NextAction** getAlternatives() { return NULL; }
        virtual NextAction** getContinuers() { return NULL; }
        virtual ActionThreatType getThreatType() { return ACTION_THREAT_NONE; }
        void Update() { }
        void Reset() { }
        virtual Unit* GetTarget();
        virtual Value<Unit*>* GetTargetValue();
        virtual std::string GetTargetName() { return "self target"; }
        void MakeVerbose() { verbose = true; }

    protected:
        bool verbose;
};

class ActionNode
{
    public:
        ActionNode(std::string name, NextAction** prerequisites = NULL, NextAction** alternatives = NULL, NextAction** continuers = NULL) :
            action(NULL), name(name), prerequisites(prerequisites), alternatives(alternatives), continuers(continuers) { }

        virtual ~ActionNode()
        {
            NextAction::destroy(prerequisites);
            NextAction::destroy(alternatives);
            NextAction::destroy(continuers);
        }

        Action* getAction() { return action; }
        void setAction(Action* action) { this->action = action; }
        std::string const& getName() { return name; }

        NextAction** getContinuers() { return NextAction::merge(NextAction::clone(continuers), action->getContinuers()); }
        NextAction** getAlternatives() { return NextAction::merge(NextAction::clone(alternatives), action->getAlternatives()); }
        NextAction** getPrerequisites() { return NextAction::merge(NextAction::clone(prerequisites), action->getPrerequisites()); }

    private:
        std::string name;
        Action* action;
        NextAction** continuers;
        NextAction** alternatives;
        NextAction** prerequisites;
};

class ActionBasket
{
	public:
        ActionBasket(ActionNode* action, float relevance, bool skipPrerequisites, Event event) :
            action(action), relevance(relevance), skipPrerequisites(skipPrerequisites), event(event), created(time(0)) { }

        virtual ~ActionBasket(void) { }

		float getRelevance() {return relevance;}
		ActionNode* getAction() {return action;}
        Event getEvent() { return event; }
        bool isSkipPrerequisites() { return skipPrerequisites; }
        void AmendRelevance(float k) {relevance *= k; }
        void setRelevance(float relevance) { this->relevance = relevance; }
        bool isExpired(time_t secs) { return time(0) - created >= secs; }

	private:
		ActionNode* action;
		float relevance;
        bool skipPrerequisites;
        Event event;
        time_t created;
};

