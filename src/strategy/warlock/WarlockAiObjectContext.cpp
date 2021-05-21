#include "botpch.h"
#include "../../playerbot.h"
#include "WarlockActions.h"
#include "WarlockAiObjectContext.h"
#include "DpsWarlockStrategy.h"
#include "GenericWarlockNonCombatStrategy.h"
#include "TankWarlockStrategy.h"
#include "../generic/PullStrategy.h"
#include "WarlockTriggers.h"
#include "../NamedObjectContext.h"
#include "../actions/UseItemAction.h"

using namespace botAI;

namespace botAI
{
    namespace warlock
    {
        using namespace botAI;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &warlock::StrategyFactoryInternal::nc;
                creators["pull"] = &warlock::StrategyFactoryInternal::pull;
                creators["aoe"] = &warlock::StrategyFactoryInternal::aoe;
                creators["dps debuff"] = &warlock::StrategyFactoryInternal::dps_debuff;
                creators["boost"] = &warlock::StrategyFactoryInternal::boost;
                creators["cc"] = &warlock::StrategyFactoryInternal::cc;
                creators["pet"] = &warlock::StrategyFactoryInternal::pet;
            }

        private:
            static Strategy* pet(PlayerbotAI* botAI) { return new WarlockPetStrategy(botAI); }
            static Strategy* nc(PlayerbotAI* botAI) { return new GenericWarlockNonCombatStrategy(botAI); }
            static Strategy* aoe(PlayerbotAI* botAI) { return new DpsAoeWarlockStrategy(botAI); }
            static Strategy* dps_debuff(PlayerbotAI* botAI) { return new DpsWarlockDebuffStrategy(botAI); }
            static Strategy* pull(PlayerbotAI* botAI) { return new PullStrategy(botAI, "shoot"); }
            static Strategy* boost(PlayerbotAI* botAI) { return new WarlockBoostStrategy(botAI); }
            static Strategy* cc(PlayerbotAI* botAI) { return new WarlockCcStrategy(botAI); }
        };

        class CombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            CombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["dps"] = &warlock::CombatStrategyFactoryInternal::dps;
                creators["tank"] = &warlock::CombatStrategyFactoryInternal::tank;
            }

        private:
            static Strategy* tank(PlayerbotAI* botAI) { return new TankWarlockStrategy(botAI); }
            static Strategy* dps(PlayerbotAI* botAI) { return new DpsWarlockStrategy(botAI); }
        };
    };
};

namespace botAI
{
    namespace warlock
    {
        using namespace botAI;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["shadow trance"] = &TriggerFactoryInternal::shadow_trance;
                creators["demon armor"] = &TriggerFactoryInternal::demon_armor;
                creators["no healthstone"] = &TriggerFactoryInternal::HasHealthstone;
                creators["no firestone"] = &TriggerFactoryInternal::HasFirestone;
                creators["no spellstone"] = &TriggerFactoryInternal::HasSpellstone;
                creators["corruption"] = &TriggerFactoryInternal::corruption;
                creators["corruption on attacker"] = &TriggerFactoryInternal::corruption_on_attacker;
                creators["curse of agony"] = &TriggerFactoryInternal::curse_of_agony;
                creators["curse of agony on attacker"] = &TriggerFactoryInternal::curse_of_agony_on_attacker;
                creators["banish"] = &TriggerFactoryInternal::banish;
                creators["spellstone"] = &TriggerFactoryInternal::spellstone;
                creators["backlash"] = &TriggerFactoryInternal::backlash;
                creators["fear"] = &TriggerFactoryInternal::fear;
                creators["immolate"] = &TriggerFactoryInternal::immolate;
                creators["amplify curse"] = &TriggerFactoryInternal::amplify_curse;
                creators["siphon life"] = &TriggerFactoryInternal::siphon_life;
                creators["siphon life on attacker"] = &TriggerFactoryInternal::siphon_life_on_attacker;


            }

        private:
            static Trigger* amplify_curse(PlayerbotAI* botAI) { return new AmplifyCurseTrigger(botAI); }
            static Trigger* shadow_trance(PlayerbotAI* botAI) { return new ShadowTranceTrigger(botAI); }
            static Trigger* demon_armor(PlayerbotAI* botAI) { return new DemonArmorTrigger(botAI); }
            static Trigger* HasHealthstone(PlayerbotAI* botAI) { return new HasHealthstoneTrigger(botAI); }
            static Trigger* HasFirestone(PlayerbotAI* botAI) { return new HasFirestoneTrigger(botAI); }
            static Trigger* HasSpellstone(PlayerbotAI* botAI) { return new HasSpellstoneTrigger(botAI); }
            static Trigger* corruption(PlayerbotAI* botAI) { return new CorruptionTrigger(botAI); }
            static Trigger* corruption_on_attacker(PlayerbotAI* botAI) { return new CorruptionOnAttackerTrigger(botAI); }
            static Trigger* siphon_life(PlayerbotAI* botAI) { return new SiphonLifeTrigger(botAI); }
            static Trigger* siphon_life_on_attacker(PlayerbotAI* botAI) { return new SiphonLifeOnAttackerTrigger(botAI); }
            static Trigger* curse_of_agony(PlayerbotAI* botAI) { return new CurseOfAgonyTrigger(botAI); }
            static Trigger* curse_of_agony_on_attacker(PlayerbotAI* botAI) { return new CastCurseOfAgonyOnAttackerTrigger(botAI); }
            static Trigger* banish(PlayerbotAI* botAI) { return new BanishTrigger(botAI); }
            static Trigger* spellstone(PlayerbotAI* botAI) { return new SpellstoneTrigger(botAI); }
            static Trigger* backlash(PlayerbotAI* botAI) { return new BacklashTrigger(botAI); }
            static Trigger* fear(PlayerbotAI* botAI) { return new FearTrigger(botAI); }
            static Trigger* immolate(PlayerbotAI* botAI) { return new ImmolateTrigger(botAI); }

        };
    };
};

namespace botAI
{
    namespace warlock
    {
        using namespace botAI;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["summon imp"] = &AiObjectContextInternal::summon_imp;
                creators["fel armor"] = &AiObjectContextInternal::fel_armor;
                creators["demon armor"] = &AiObjectContextInternal::demon_armor;
                creators["demon skin"] = &AiObjectContextInternal::demon_skin;
                creators["create healthstone"] = &AiObjectContextInternal::create_healthstone;
                creators["create firestone"] = &AiObjectContextInternal::create_firestone;
                creators["create spellstone"] = &AiObjectContextInternal::create_spellstone;
                creators["spellstone"] = &AiObjectContextInternal::spellstone;
                creators["summon voidwalker"] = &AiObjectContextInternal::summon_voidwalker;
                creators["summon felguard"] = &AiObjectContextInternal::summon_felguard;
                creators["immolate"] = &AiObjectContextInternal::immolate;
                creators["corruption"] = &AiObjectContextInternal::corruption;
                creators["corruption on attacker"] = &AiObjectContextInternal::corruption_on_attacker;
                creators["siphon life"] = &AiObjectContextInternal::siphon_life;
                creators["siphon life on attacker"] = &AiObjectContextInternal::siphon_life_on_attacker;
                creators["curse of agony"] = &AiObjectContextInternal::curse_of_agony;
                creators["curse of agony on attacker"] = &AiObjectContextInternal::curse_of_agony_on_attacker;
                creators["shadow bolt"] = &AiObjectContextInternal::shadow_bolt;
                creators["drain soul"] = &AiObjectContextInternal::drain_soul;
                creators["drain mana"] = &AiObjectContextInternal::drain_mana;
                creators["drain life"] = &AiObjectContextInternal::drain_life;
                creators["banish"] = &AiObjectContextInternal::banish;
                creators["banish on cc"] = &AiObjectContextInternal::banish_on_cc;
                creators["seed of corruption"] = &AiObjectContextInternal::seed_of_corruption;
                creators["rain of fire"] = &AiObjectContextInternal::rain_of_fire;
                creators["shadowfury"] = &AiObjectContextInternal::shadowfury;
                creators["life tap"] = &AiObjectContextInternal::life_tap;
                creators["fear"] = &AiObjectContextInternal::fear;
                creators["fear on cc"] = &AiObjectContextInternal::fear_on_cc;
                creators["incinirate"] = &AiObjectContextInternal::incinirate;
                creators["conflagrate"] = &AiObjectContextInternal::conflagrate;
                creators["amplify curse"] = &AiObjectContextInternal::amplify_curse;
            }

        private:
            static Action* amplify_curse(PlayerbotAI* botAI) { return new CastAmplifyCurseAction(botAI); }
            static Action* conflagrate(PlayerbotAI* botAI) { return new CastConflagrateAction(botAI); }
            static Action* incinirate(PlayerbotAI* botAI) { return new CastIncinirateAction(botAI); }
            static Action* fear_on_cc(PlayerbotAI* botAI) { return new CastFearOnCcAction(botAI); }
            static Action* fear(PlayerbotAI* botAI) { return new CastFearAction(botAI); }
            static Action* immolate(PlayerbotAI* botAI) { return new CastImmolateAction(botAI); }
            static Action* summon_imp(PlayerbotAI* botAI) { return new CastSummonImpAction(botAI); }
            static Action* fel_armor(PlayerbotAI* botAI) { return new CastFelArmorAction(botAI); }
            static Action* demon_armor(PlayerbotAI* botAI) { return new CastDemonArmorAction(botAI); }
            static Action* demon_skin(PlayerbotAI* botAI) { return new CastDemonSkinAction(botAI); }
            static Action* create_healthstone(PlayerbotAI* botAI) { return new CastCreateHealthstoneAction(botAI); }
            static Action* create_firestone(PlayerbotAI* botAI) { return new CastCreateFirestoneAction(botAI); }
            static Action* create_spellstone(PlayerbotAI* botAI) { return new CastCreateSpellstoneAction(botAI); }
            static Action* spellstone(PlayerbotAI* botAI) { return new UseSpellItemAction(botAI, "spellstone", true); }
            static Action* summon_voidwalker(PlayerbotAI* botAI) { return new CastSummonVoidwalkerAction(botAI); }
            static Action* summon_felguard(PlayerbotAI* botAI) { return new CastSummonFelguardAction(botAI); }
            static Action* corruption(PlayerbotAI* botAI) { return new CastCorruptionAction(botAI); }
            static Action* corruption_on_attacker(PlayerbotAI* botAI) { return new CastCorruptionOnAttackerAction(botAI); }
            static Action* siphon_life(PlayerbotAI* botAI) { return new CastSiphonLifeAction(botAI); }
            static Action* siphon_life_on_attacker(PlayerbotAI* botAI) { return new CastSiphonLifeOnAttackerAction(botAI); }
            static Action* curse_of_agony(PlayerbotAI* botAI) { return new CastCurseOfAgonyAction(botAI); }
            static Action* curse_of_agony_on_attacker(PlayerbotAI* botAI) { return new CastCurseOfAgonyOnAttackerAction(botAI); }
            static Action* shadow_bolt(PlayerbotAI* botAI) { return new CastShadowBoltAction(botAI); }
            static Action* drain_soul(PlayerbotAI* botAI) { return new CastDrainSoulAction(botAI); }
            static Action* drain_mana(PlayerbotAI* botAI) { return new CastDrainManaAction(botAI); }
            static Action* drain_life(PlayerbotAI* botAI) { return new CastDrainLifeAction(botAI); }
            static Action* banish(PlayerbotAI* botAI) { return new CastBanishAction(botAI); }
            static Action* banish_on_cc(PlayerbotAI* botAI) { return new CastBanishAction(botAI); }
            static Action* seed_of_corruption(PlayerbotAI* botAI) { return new CastSeedOfCorruptionAction(botAI); }
            static Action* rain_of_fire(PlayerbotAI* botAI) { return new CastRainOfFireAction(botAI); }
            static Action* shadowfury(PlayerbotAI* botAI) { return new CastShadowfuryAction(botAI); }
            static Action* life_tap(PlayerbotAI* botAI) { return new CastLifeTapAction(botAI); }

        };
    };
};



WarlockAiObjectContext::WarlockAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new botAI::warlock::StrategyFactoryInternal());
    strategyContexts.Add(new botAI::warlock::CombatStrategyFactoryInternal());
    actionContexts.Add(new botAI::warlock::AiObjectContextInternal());
    triggerContexts.Add(new botAI::warlock::TriggerFactoryInternal());
}
