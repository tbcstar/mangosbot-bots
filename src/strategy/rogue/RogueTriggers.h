#pragma once
#include "../triggers/GenericTriggers.h"

namespace botAI
{

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
}
