#pragma once
#include "../triggers/GenericTriggers.h"

namespace botAI
{
    class ArcaneIntellectOnPartyTrigger : public BuffOnPartyTrigger {
    public:
        ArcaneIntellectOnPartyTrigger(PlayerbotAI* botAI) : BuffOnPartyTrigger(botAI, "arcane intellect", 2) { }

        virtual bool IsActive() { return BuffOnPartyTrigger::IsActive() && !botAI->HasAura("arcane brilliance", GetTarget()); }
    };

    class ArcaneIntellectTrigger : public BuffTrigger {
    public:
        ArcaneIntellectTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "arcane intellect", 2) { }

        virtual bool IsActive() { return BuffTrigger::IsActive() && !botAI->HasAura("arcane brilliance", GetTarget()); }
    };

    class MageArmorTrigger : public BuffTrigger {
    public:
        MageArmorTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "mage armor", 5) { }
        bool IsActive() override;
    };

    class LivingBombTrigger : public DebuffTrigger {
    public:
        LivingBombTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "living bomb") { }
	};

    class FireballTrigger : public DebuffTrigger {
    public:
        FireballTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "fireball") { }
	};

    class PyroblastTrigger : public DebuffTrigger {
    public:
        PyroblastTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "pyroblast") { }
    };

    class HotStreakTrigger : public HasAuraTrigger {
    public:
        HotStreakTrigger(PlayerbotAI* botAI) : HasAuraTrigger(botAI, "hot streak") { }
    };

    class MissileBarrageTrigger : public HasAuraTrigger {
    public:
        MissileBarrageTrigger(PlayerbotAI* botAI) : HasAuraTrigger(botAI, "missile barrage") { }
    };

    class ArcaneBlastTrigger : public BuffTrigger {
    public:
        ArcaneBlastTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "arcane blast") { }
    };

    class CounterspellInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        CounterspellInterruptSpellTrigger(PlayerbotAI* botAI) : InterruptSpellTrigger(botAI, "counterspell") { }
    };

    class CombustionTrigger : public BoostTrigger
    {
    public:
        CombustionTrigger(PlayerbotAI* botAI) : BoostTrigger(botAI, "combustion") { }
    };

    class IcyVeinsTrigger : public BoostTrigger
    {
    public:
        IcyVeinsTrigger(PlayerbotAI* botAI) : BoostTrigger(botAI, "icy veins") { }
    };

    class PolymorphTrigger : public HasCcTargetTrigger
    {
    public:
        PolymorphTrigger(PlayerbotAI* botAI) : HasCcTargetTrigger(botAI, "polymorph") { }
    };

    class RemoveCurseTrigger : public NeedCureTrigger
    {
    public:
        RemoveCurseTrigger(PlayerbotAI* botAI) : NeedCureTrigger(botAI, "remove curse", DISPEL_CURSE) { }
    };

    class PartyMemberRemoveCurseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberRemoveCurseTrigger(PlayerbotAI* botAI) : PartyMemberNeedCureTrigger(botAI, "remove curse", DISPEL_CURSE) { }
    };

    class SpellstealTrigger : public TargetAuraDispelTrigger
    {
    public:
        SpellstealTrigger(PlayerbotAI* botAI) : TargetAuraDispelTrigger(botAI, "spellsteal", DISPEL_MAGIC) { }
    };

    class CounterspellEnemyHealerTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        CounterspellEnemyHealerTrigger(PlayerbotAI* botAI) : InterruptEnemyHealerTrigger(botAI, "counterspell") { }
    };

    class ArcanePowerTrigger : public BuffTrigger
    {
    public:
        ArcanePowerTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "arcane power") { }
    };

    class PresenceOfMindTrigger : public BuffTrigger
    {
    public:
        PresenceOfMindTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "presence of mind") { }
    };
}
