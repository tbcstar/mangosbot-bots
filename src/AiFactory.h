/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Common.h"

class AiObjectContext;
class Engine;
class Player;
class PlayerbotAI;

class AiFactory
{
    public:
        static AiObjectContext* createAiObjectContext(Player* player, PlayerbotAI* ai);
	    static Engine* createCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext);
	    static Engine* createNonCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext);
        static Engine* createDeadEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext);
        static void AddDefaultNonCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* nonCombatEngine);
        static void AddDefaultDeadStrategies(Player* player, PlayerbotAI* const facade, Engine* deadEngine);
        static void AddDefaultCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* engine);

    public:
        static uint8 GetPlayerSpecTab(Player* player);
        static std::map<uint8, uint32> GetPlayerSpecTabs(Player* player);
};
