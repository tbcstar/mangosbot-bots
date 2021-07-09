/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "MovementActions.h"

class Event;
class PlayerbotAI;

class AttackAction : public MovementAction
{
	public:
		AttackAction(PlayerbotAI* botAI, std::string const& name) : MovementAction(botAI, name) { }

        bool Execute(Event event) override;

    protected:
        bool Attack(Unit* target);
};

class AttackMyTargetAction : public AttackAction
{
    public:
        AttackMyTargetAction(PlayerbotAI* botAI, std::string const& name = "attack my target") : AttackAction(botAI, name) { }

        bool Execute(Event event) override;
};

class AttackDuelOpponentAction : public AttackAction
    {
    public:
        AttackDuelOpponentAction(PlayerbotAI* botAI, std::string const& name = "attack duel opponent") : AttackAction(botAI, name) { }

    public:
        bool Execute(Event event) override;
        bool isUseful() override;
};
