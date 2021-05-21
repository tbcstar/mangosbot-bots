/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "MovementActions.h"

class Event;
class PlayerbotAI;
class Unit;

class RpgAction : public MovementAction
{
    public:
        RpgAction(PlayerbotAI* botAI) : MovementAction(botAI, "rpg") { }

        bool Execute(Event event) override;
        bool isUseful() const override;

    private:
        typedef void(RpgAction::*RpgElement)(Unit*);

        void stay(Unit* unit);
        void cancel(Unit* unit);
        void emote(Unit* unit);
        void work(Unit* unit);
        void taxi(Unit* unit);
};
