#pragma once
#include "../Value.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class Formation : public AiNamedObject
    {
    public:
        Formation(PlayerbotAI* botAI, string name) : AiNamedObject (ai, name) {}

    public:
        virtual string GetTargetName() { return ""; }
        virtual WorldLocation GetLocation() { return NullLocation; }
        virtual float GetMaxDistance() { return sPlayerbotAIConfig->followDistance; }
        static WorldLocation NullLocation;
		static bool IsNullLocation(WorldLocation const& loc);

    protected:
        float GetFollowAngle();
    };

    class FollowFormation : public Formation
    {
    public:
        FollowFormation(PlayerbotAI* botAI, string name) : Formation(ai, name) {}
    };

    class MoveFormation : public Formation
    {
    public:
        MoveFormation(PlayerbotAI* botAI, string name) : Formation(ai, name) {}

    protected:
        WorldLocation MoveLine(vector<Player*> line, float diff, float cx, float cy, float cz, float orientation, float range);
        WorldLocation MoveSingleLine(vector<Player*> line, float diff, float cx, float cy, float cz, float orientation, float range);
    };

    class MoveAheadFormation : public MoveFormation
    {
    public:
        MoveAheadFormation(PlayerbotAI* botAI, string name) : MoveFormation(ai, name) {}
        virtual WorldLocation GetLocation();
        virtual WorldLocation GetLocationInternal() { return NullLocation; }
    };

    class FormationValue : public ManualSetValue<Formation*>
	{
	public:
        FormationValue(PlayerbotAI* botAI);
        ~FormationValue() { if (value) { delete value; value = nullptr; } }
        virtual string Save();
        virtual bool Load(string value);
    };

    class SetFormationAction : public Action
    {
    public:
        SetFormationAction(PlayerbotAI* botAI) : Action(botAI, "set formation") {}
        bool Execute(Event event) override;
    };
};

