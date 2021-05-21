#pragma once
#include "../triggers/GenericTriggers.h"

namespace botAI
{
	class DemonArmorTrigger : public BuffTrigger
	{
	public:
		DemonArmorTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "demon armor") { }
		bool IsActive() override;
	};

    class SpellstoneTrigger : public BuffTrigger
    {
    public:
        SpellstoneTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "spellstone") { }
        bool IsActive() override;
    };

    DEBUFF_TRIGGER(CurseOfAgonyTrigger, "curse of agony", "curse of agony");
    DEBUFF_TRIGGER(CorruptionTrigger, "corruption", "corruption");
    DEBUFF_TRIGGER(SiphonLifeTrigger, "siphon life", "siphon life");

    class CorruptionOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        CorruptionOnAttackerTrigger(PlayerbotAI* botAI) : DebuffOnAttackerTrigger(botAI, "corruption") { }
    };

    class CastCurseOfAgonyOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        CastCurseOfAgonyOnAttackerTrigger(PlayerbotAI* botAI) : DebuffOnAttackerTrigger(botAI, "curse of agony") { }
    };

    class SiphonLifeOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        SiphonLifeOnAttackerTrigger(PlayerbotAI* botAI) : DebuffOnAttackerTrigger(botAI, "siphon life") { }
    };

    DEBUFF_TRIGGER(ImmolateTrigger, "immolate", "immolate");

    class ShadowTranceTrigger : public HasAuraTrigger
    {
    public:
        ShadowTranceTrigger(PlayerbotAI* botAI) : HasAuraTrigger(botAI, "shadow trance") { }
    };

    class BacklashTrigger : public HasAuraTrigger
    {
    public:
        BacklashTrigger(PlayerbotAI* botAI) : HasAuraTrigger(botAI, "backlash") { }
    };

    class BanishTrigger : public HasCcTargetTrigger
    {
    public:
        BanishTrigger(PlayerbotAI* botAI) : HasCcTargetTrigger(botAI, "banish") { }
    };

    class WarlockConjuredItemTrigger : public ItemCountTrigger
    {
    public:
        WarlockConjuredItemTrigger(PlayerbotAI* botAI, std::string const& item) : ItemCountTrigger(botAI, item, 1) { }

        virtual bool IsActive() { return ItemCountTrigger::IsActive() && AI_VALUE2(uint8, "item count", "soul shard") > 0; }
    };

    class HasSpellstoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasSpellstoneTrigger(PlayerbotAI* botAI) : WarlockConjuredItemTrigger(botAI, "spellstone") { }
    };

    class HasFirestoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasFirestoneTrigger(PlayerbotAI* botAI) : WarlockConjuredItemTrigger(botAI, "firestone") { }
    };

    class HasHealthstoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasHealthstoneTrigger(PlayerbotAI* botAI) : WarlockConjuredItemTrigger(botAI, "healthstone") { }
    };

    class FearTrigger : public HasCcTargetTrigger
    {
    public:
        FearTrigger(PlayerbotAI* botAI) : HasCcTargetTrigger(botAI, "fear") { }
    };

    class AmplifyCurseTrigger : public BuffTrigger
    {
    public:
        AmplifyCurseTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "amplify curse") { }
    };
}
