/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Action.h"

class Event;
class Item;
class ObjectGuid;
class PlayerbotAI;

class UseItemAction : public Action
{
	public:
		UseItemAction(PlayerbotAI* botAI, std::string const& name = "use", bool selfOnly = false) : Action(botAI, name), selfOnly(selfOnly) { }

        bool Execute(Event event) override;
        bool isPossible() const override;

    protected:
        bool UseItemAuto(Item* item);
        bool UseItemOnGameObject(Item* item, ObjectGuid go);
        bool UseItemOnItem(Item* item, Item* itemTarget);
        bool UseItem(Item* item, ObjectGuid go, Item* itemTarget);
        bool UseGameObject(ObjectGuid guid);
        void TellConsumableUse(Item* item, std::string const& action, float percent);

    private:
        bool selfOnly;
};

class UseSpellItemAction : public UseItemAction
{
    public:
        UseSpellItemAction(PlayerbotAI* botAI, std::string const& name, bool selfOnly = false) : UseItemAction(botAI, name, selfOnly) { }

        bool isUseful() const override;
};

class UseHealingPotion : public UseItemAction
{
    public:
        UseHealingPotion(PlayerbotAI* botAI) : UseItemAction(botAI, "healing potion") { }

        bool isUseful() const override;
};

class UseManaPotion : public UseItemAction
{
    public:
        UseManaPotion(PlayerbotAI* botAI) : UseItemAction(botAI, "mana potion") { }

        bool isUseful() const override;
};
