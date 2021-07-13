/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "EquipAction.h"
#include "ChatHelper.h"

class Event;
class PlayerbotAI;

class OutfitAction : public EquipAction
{
    public:
        OutfitAction(PlayerbotAI* botAI) : EquipAction(botAI, "outfit") { }

        bool Execute(Event event) override;

    private:
        void List();
        void Save(std::string const& name, ItemIds outfit);
        void Update(std::string const& name);
};
