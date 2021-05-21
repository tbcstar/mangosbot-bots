#pragma once
#include "../Value.h"
#include "../../PlayerbotAIConfig.h"
#include "Formations.h"

namespace botAI
{
    class Stance : public Formation
    {
    public:
        Stance(PlayerbotAI* botAI, std::string const& name) : Formation (botAI, name) { }

    protected:
        virtual Unit* GetTarget();
        virtual WorldLocation GetLocationInternal() = 0;
        virtual WorldLocation GetNearLocation(float angle, float distance);

    public:
        virtual WorldLocation GetLocation();
        std::string const& GetTargetName() override { return "current target"; }
        virtual float GetMaxDistance() { return sPlayerbotAIConfig->contactDistance; }
    };

    class MoveStance : public Stance
    {
    public:
        MoveStance(PlayerbotAI* botAI, std::string const& name) : Stance (botAI, name) { }

    protected:
        virtual WorldLocation GetLocationInternal();
        virtual float GetAngle() = 0;

    public:
    };


    class StanceValue : public ManualSetValue<Stance*>
	{
	public:
        StanceValue(PlayerbotAI* botAI);
        ~StanceValue() { if (value) { delete value; value = nullptr; } }
        virtual string Save();
        virtual bool Load(string value);
    };

    class SetStanceAction : public Action
    {
    public:
        SetStanceAction(PlayerbotAI* botAI) : Action(botAI, "set Stance") { }
        bool Execute(Event event) override;
    };
};

