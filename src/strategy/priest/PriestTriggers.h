#pragma once

#include "../triggers/GenericTriggers.h"

namespace ai
{
    class PowerWordFortitudeOnPartyTrigger : public BuffOnPartyTrigger {
    public:
        PowerWordFortitudeOnPartyTrigger(PlayerbotAI* botAI) : BuffOnPartyTrigger(ai, "power word: fortitude", 2) {}

        virtual bool IsActive() { return BuffOnPartyTrigger::IsActive() && !botAI->HasAura("prayer of fortitude", GetTarget()); }
    };

    class PowerWordFortitudeTrigger : public BuffTrigger {
    public:
        PowerWordFortitudeTrigger(PlayerbotAI* botAI) : BuffTrigger(ai, "power word: fortitude", 2) {}

        virtual bool IsActive() { return BuffTrigger::IsActive() && !botAI->HasAura("prayer of fortitude", GetTarget()); }
    };

    class DivineSpiritOnPartyTrigger : public BuffOnPartyTrigger {
    public:
        DivineSpiritOnPartyTrigger(PlayerbotAI* botAI) : BuffOnPartyTrigger(ai, "divine spirit", 2) {}

        virtual bool IsActive() { return BuffOnPartyTrigger::IsActive() && !botAI->HasAura("prayer of spirit", GetTarget()); }
    };

    class DivineSpiritTrigger : public BuffTrigger {
    public:
        DivineSpiritTrigger(PlayerbotAI* botAI) : BuffTrigger(ai, "divine spirit", 2) {}

        virtual bool IsActive() { return BuffTrigger::IsActive() && !botAI->HasAura("prayer of spirit", GetTarget()); }
    };


    class InnerFireTrigger : public BuffTrigger
    {
    public:
        InnerFireTrigger(PlayerbotAI* botAI) : BuffTrigger(ai, "inner fire", 2) {}
        virtual bool IsActive();
    };

    BUFF_TRIGGER(VampiricEmbraceTrigger, "vampiric embrace", "vampiric embrace")

    class PowerWordPainOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        PowerWordPainOnAttackerTrigger(PlayerbotAI* botAI) : DebuffOnAttackerTrigger(ai, "shadow word: pain") {}
    };

    DEBUFF_TRIGGER(PowerWordPainTrigger, "shadow word: pain", "shadow word: pain")
    DEBUFF_TRIGGER(DevouringPlagueTrigger, "devouring plague", "devouring plague")
    DEBUFF_TRIGGER(VampiricTouchTrigger, "vampiric touch", "vampiric touch")

    class DispelMagicTrigger : public NeedCureTrigger
    {
    public:
        DispelMagicTrigger(PlayerbotAI* botAI) : NeedCureTrigger(ai, "dispel magic", DISPEL_MAGIC) {}
    };

    class DispelMagicPartyMemberTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        DispelMagicPartyMemberTrigger(PlayerbotAI* botAI) : PartyMemberNeedCureTrigger(ai, "dispel magic", DISPEL_MAGIC) {}
    };

    class CureDiseaseTrigger : public NeedCureTrigger
    {
    public:
        CureDiseaseTrigger(PlayerbotAI* botAI) : NeedCureTrigger(ai, "cure disease", DISPEL_DISEASE) {}
    };

    class PartyMemberCureDiseaseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberCureDiseaseTrigger(PlayerbotAI* botAI) : PartyMemberNeedCureTrigger(ai, "cure disease", DISPEL_DISEASE) {}
    };

    class ShadowformTrigger : public BuffTrigger {
    public:
        ShadowformTrigger(PlayerbotAI* botAI) : BuffTrigger(ai, "shadowform") {}
        virtual bool IsActive() { return !botAI->HasAura("shadowform", bot); }
    };

    class PowerInfusionTrigger : public BuffTrigger
    {
    public:
        PowerInfusionTrigger(PlayerbotAI* botAI) : BuffTrigger(ai, "power infusion") {}
    };

    class InnerFocusTrigger : public BuffTrigger
    {
    public:
        InnerFocusTrigger(PlayerbotAI* botAI) : BuffTrigger(ai, "inner focus") {}
    };

    class ShadowProtectionOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        ShadowProtectionOnPartyTrigger(PlayerbotAI* botAI) : BuffOnPartyTrigger(ai, "shadow protection", 2) {}
    };

    class ShadowProtectionTrigger : public BuffTrigger
    {
    public:
        ShadowProtectionTrigger(PlayerbotAI* botAI) : BuffTrigger(ai, "shadow protection", 2) {}
    };

    class ShackleUndeadTrigger : public HasCcTargetTrigger
    {
    public:
        ShackleUndeadTrigger(PlayerbotAI* botAI) : HasCcTargetTrigger(ai, "shackle undead") {}
    };
}
