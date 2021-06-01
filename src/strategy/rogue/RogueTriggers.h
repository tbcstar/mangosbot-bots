/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "GenericTriggers.h"

class PlayerbotAI;

class KickInterruptSpellTrigger : public InterruptSpellTrigger
{
    public:
        KickInterruptSpellTrigger(PlayerbotAI* botAI) : InterruptSpellTrigger(botAI, "kick") { }
};

class SliceAndDiceTrigger : public BuffTrigger
{
    public:
        SliceAndDiceTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "slice and dice") { }
};

class AdrenalineRushTrigger : public BuffTrigger
{
    public:
        AdrenalineRushTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "adrenaline rush") { }
};

class RuptureTrigger : public DebuffTrigger
{
    public:
        RuptureTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "rupture") { }
};

class ExposeArmorTrigger : public DebuffTrigger
{
    public:
        ExposeArmorTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "expose armor") { }
};

class KickInterruptEnemyHealerSpellTrigger : public InterruptEnemyHealerTrigger
{
    public:
        KickInterruptEnemyHealerSpellTrigger(PlayerbotAI* botAI) : InterruptEnemyHealerTrigger(botAI, "kick") { }
};
