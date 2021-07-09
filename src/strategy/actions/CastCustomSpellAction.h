/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "InventoryAction.h"

class Event;
class PlayerbotAI;
class SpellInfo;
class WorldObject;

class CastCustomSpellAction : public InventoryAction
{
    public:
        CastCustomSpellAction(PlayerbotAI* ai, std::string const& name = "cast custom spell") : InventoryAction(ai, name) { }

        bool Execute(Event event) override;
        virtual std::string const& castString(WorldObject* target) { return "cast"; }

protected:
    bool ncCast = false;
};

class CastCustomNcSpellAction : public CastCustomSpellAction
{
    public:
        CastCustomNcSpellAction(PlayerbotAI* ai, std::string const name = "cast custom nc spell") : CastCustomSpellAction(ai, name) {}

        bool isUseful() override;
        std::string const& castString(WorldObject* target) override;
};

class CastRandomSpellAction : public CastCustomSpellAction
{
    public:
        CastRandomSpellAction(PlayerbotAI* ai, std::string const& name = "cast random spell") : CastCustomSpellAction(ai, name) {}

        virtual bool AcceptSpell(SpellInfo const* pSpellInfo) { return true; }
        bool Execute(Event event) override;

    protected:
        bool MultiCast = false;
};

class CraftRandomItemAction : public CastRandomSpellAction
{
    public:
        CraftRandomItemAction(PlayerbotAI* ai) : CastRandomSpellAction(ai, "craft random item")
        {
            MultiCast = true;
        }

        bool AcceptSpell(SpellInfo const* pSpellInfo) override;
};
