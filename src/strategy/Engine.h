/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Common.h"
#include "Multiplier.h"
#include "Trigger.h"
#include "Strategy.h"
#include "PlayerbotAIAware.h"

class Action;
class ActionNode;
class AiObjectContext;
class Event;
class NextAction;
class PlayerbotAI;
class Queue;

enum ActionResult
{
    ACTION_RESULT_UNKNOWN,
    ACTION_RESULT_OK,
    ACTION_RESULT_IMPOSSIBLE,
    ACTION_RESULT_USELESS,
    ACTION_RESULT_FAILED
};

class ActionExecutionListener
{
    public:
        virtual ~ActionExecutionListener() { };

        virtual bool Before(Action* action, Event event) = 0;
        virtual bool AllowExecution(Action* action, Event event) = 0;
        virtual void After(Action* action, bool executed, Event event) = 0;
        virtual bool OverrideResult(Action* action, bool executed, Event event) = 0;
};

class ActionExecutionListeners : public ActionExecutionListener
{
    public:
        virtual ~ActionExecutionListeners();

        bool Before(Action* action, Event event) override;
        bool AllowExecution(Action* action, Event event) override;
        void After(Action* action, bool executed, Event event) override;
        bool OverrideResult(Action* action, bool executed, Event event) override;

        void Add(ActionExecutionListener* listener)
        {
            listeners.push_back(listener);
        }

        void Remove(ActionExecutionListener* listener)
        {
            listeners.remove(listener);
        }

    private:
        std::list<ActionExecutionListener*> listeners;
};

class Engine : public PlayerbotAIAware
{
    public:
        Engine(PlayerbotAI* botAI, AiObjectContext* factory);

	    void Init();
        void addStrategy(std::string const& name);
		void addStrategies(std::string const& first, ...);
        bool removeStrategy(std::string const& name);
        bool HasStrategy(std::string const& name);
        void removeAllStrategies();
        void toggleStrategy(std::string const& name);
        std::string ListStrategies();
        std::vector<std::string> GetStrategies();
		bool ContainsStrategy(StrategyType type);
		void ChangeStrategy(std::string const& names);
        std::string GetLastAction() { return lastAction; }

	    virtual bool DoNextAction(Unit*, uint32 depth = 0, bool minimal = false);
	    ActionResult ExecuteAction(std::string const& name, Event event = Event(), std::string const& qualifier = "");

        void AddActionExecutionListener(ActionExecutionListener* listener)
        {
            actionExecutionListeners.Add(listener);
        }

        void removeActionExecutionListener(ActionExecutionListener* listener)
        {
            actionExecutionListeners.Remove(listener);
        }

	    virtual ~Engine(void);

        bool testMode;

    private:
        bool MultiplyAndPush(NextAction** actions, float forceRelevance, bool skipPrerequisites, Event event, const char* pushType);
        void Reset();
        void ProcessTriggers();
        void PushDefaultActions();
        void PushAgain(ActionNode* actionNode, float relevance, Event event);
        ActionNode* CreateActionNode(std::string const& name);
        Action* InitializeAction(ActionNode* actionNode);
        bool ListenAndExecute(Action* action, Event event);

        void LogAction(char const* format, ...);
        void LogValues();

        ActionExecutionListeners actionExecutionListeners;

    protected:
	    Queue queue;
	    std::vector<TriggerNode*> triggers;
        std::vector<Multiplier*> multipliers;
        AiObjectContext* aiObjectContext;
        std::map<std::string, Strategy*> strategies;
        float lastRelevance;
        std::string lastAction;
};