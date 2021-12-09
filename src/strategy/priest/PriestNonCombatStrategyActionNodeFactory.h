/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Action.h"
#include "NamedObjectContext.h"

class PlayerbotAI;

class PriestNonCombatStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        PriestNonCombatStrategyActionNodeFactory()
        {
            creators["holy nova"] = &holy_nova;
            creators["power word: shield"] = &power_word_shield;
            creators["power word: shield on party"] = &power_word_shield_on_party;
            creators["renew"] = &renew;
            creators["renew on party"] = &renew_on_party;
            creators["greater heal"] = &greater_heal;
            creators["greater heal on party"] = &greater_heal_on_party;
            creators["heal"] = &heal;
            creators["heal on party"] = &heal_on_party;
            creators["lesser heal"] = &lesser_heal;
            creators["lesser heal on party"] = &lesser_heal_on_party;
            creators["flash heal"] = &flash_heal;
            creators["flash heal on party"] = &flash_heal_on_party;
            creators["circle of healing"] = &circle_of_healing;
        }

    private:
        static ActionNode* holy_nova(PlayerbotAI* botAI)
        {
            return new ActionNode ("holy nova",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* power_word_shield(PlayerbotAI* botAI)
        {
            return new ActionNode ("power word: shield",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("renew", 50.0f), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* power_word_shield_on_party(PlayerbotAI* botAI)
        {
            return new ActionNode ("power word: shield on party",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("renew on party", 50.0f), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* renew(PlayerbotAI* botAI)
        {
            return new ActionNode ("renew",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* renew_on_party(PlayerbotAI* botAI)
        {
            return new ActionNode ("renew on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* greater_heal(PlayerbotAI* botAI)
        {
            return new ActionNode ("greater heal",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), nullptr),
                /*A*/ NextAction::array(0, new NextAction("heal"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* greater_heal_on_party(PlayerbotAI* botAI)
        {
            return new ActionNode ("greater heal on party",
                /*P*/ nullptr,
                /*A*/ NextAction::array(0, new NextAction("heal on party"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* heal(PlayerbotAI* botAI)
        {
            return new ActionNode ("heal",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), nullptr),
                /*A*/ NextAction::array(0, new NextAction("lesser heal"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* heal_on_party(PlayerbotAI* botAI)
        {
            return new ActionNode ("heal on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), nullptr),
                /*A*/ NextAction::array(0, new NextAction("lesser heal on party"), nullptr),
                /*C*/ nullptr);
        }

        static ActionNode* lesser_heal(PlayerbotAI* botAI)
        {
            return new ActionNode ("lesser heal",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* lesser_heal_on_party(PlayerbotAI* botAI)
        {
            return new ActionNode ("lesser heal on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* flash_heal(PlayerbotAI* botAI)
        {
            return new ActionNode ("flash heal",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* flash_heal_on_party(PlayerbotAI* botAI)
        {
            return new ActionNode ("flash heal on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), nullptr),
                /*A*/ nullptr,
                /*C*/ nullptr);
        }

        static ActionNode* circle_of_healing(PlayerbotAI* botAI)
        {
            return new ActionNode ("circle of healing",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), nullptr),
                /*A*/ NextAction::array(0, new NextAction("flash heal on party"), nullptr),
                /*C*/ nullptr);
        }
};