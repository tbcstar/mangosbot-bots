#include "botpch.h"
#include "../../playerbot.h"
#include "HunterActions.h"
#include "HunterTriggers.h"
#include "HunterAiObjectContext.h"
#include "DpsHunterStrategy.h"
#include "GenericHunterNonCombatStrategy.h"
#include "HunterBuffStrategies.h"
#include "../NamedObjectContext.h"

using namespace ai;


namespace ai
{
    namespace hunter
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["dps"] = &hunter::StrategyFactoryInternal::dps;
                creators["nc"] = &hunter::StrategyFactoryInternal::nc;
                creators["aoe"] = &hunter::StrategyFactoryInternal::aoe;
                creators["dps debuff"] = &hunter::StrategyFactoryInternal::dps_debuff;
                creators["boost"] = &hunter::StrategyFactoryInternal::boost;
                creators["pet"] = &hunter::StrategyFactoryInternal::pet;
                creators["cc"] = &hunter::StrategyFactoryInternal::cc;
            }

        private:
            static Strategy* aoe(PlayerbotAI* botAI) { return new DpsAoeHunterStrategy(botAI); }
            static Strategy* dps(PlayerbotAI* botAI) { return new DpsHunterStrategy(botAI); }
            static Strategy* nc(PlayerbotAI* botAI) { return new GenericHunterNonCombatStrategy(botAI); }
            static Strategy* dps_debuff(PlayerbotAI* botAI) { return new DpsHunterDebuffStrategy(botAI); }
            static Strategy* boost(PlayerbotAI* botAI) { return new HunterBoostStrategy(botAI); }
            static Strategy* pet(PlayerbotAI* botAI) { return new HunterPetStrategy(botAI); }
            static Strategy* cc(PlayerbotAI* botAI) { return new HunterCcStrategy(botAI); }
        };

        class BuffStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            BuffStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["bspeed"] = &hunter::BuffStrategyFactoryInternal::bspeed;
                creators["bdps"] = &hunter::BuffStrategyFactoryInternal::bdps;
                creators["bmana"] = &hunter::BuffStrategyFactoryInternal::bmana;
                creators["rnature"] = &hunter::BuffStrategyFactoryInternal::rnature;
            }

        private:
            static Strategy* bspeed(PlayerbotAI* botAI) { return new HunterBuffSpeedStrategy(botAI); }
            static Strategy* bdps(PlayerbotAI* botAI) { return new HunterBuffDpsStrategy(botAI); }
            static Strategy* bmana(PlayerbotAI* botAI) { return new HunterBuffManaStrategy(botAI); }
            static Strategy* rnature(PlayerbotAI* botAI) { return new HunterNatureResistanceStrategy(botAI); }
        };
    };
};


namespace ai
{
    namespace hunter
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["aspect of the viper"] = &TriggerFactoryInternal::aspect_of_the_viper;
                creators["black arrow"] = &TriggerFactoryInternal::black_arrow;
                creators["no stings"] = &TriggerFactoryInternal::NoStings;
                creators["hunters pet dead"] = &TriggerFactoryInternal::hunters_pet_dead;
                creators["hunters pet low health"] = &TriggerFactoryInternal::hunters_pet_low_health;
                creators["hunter's mark"] = &TriggerFactoryInternal::hunters_mark;
                creators["freezing trap"] = &TriggerFactoryInternal::freezing_trap;
                creators["aspect of the pack"] = &TriggerFactoryInternal::aspect_of_the_pack;
                creators["rapid fire"] = &TriggerFactoryInternal::rapid_fire;
                creators["aspect of the hawk"] = &TriggerFactoryInternal::aspect_of_the_hawk;
                creators["aspect of the wild"] = &TriggerFactoryInternal::aspect_of_the_wild;
                creators["aspect of the viper"] = &TriggerFactoryInternal::aspect_of_the_viper;
                creators["trueshot aura"] = &TriggerFactoryInternal::trueshot_aura;
                creators["serpent sting on attacker"] = &TriggerFactoryInternal::serpent_sting_on_attacker;
                creators["pet not happy"] = &TriggerFactoryInternal::pet_not_happy;
                creators["concussive shot on snare target"] = &TriggerFactoryInternal::concussive_shot_on_snare_target;
                creators["scare beast"] = &TriggerFactoryInternal::scare_beast;
            }

        private:
            static Trigger* scare_beast(PlayerbotAI* botAI) { return new ScareBeastTrigger(botAI); }
            static Trigger* concussive_shot_on_snare_target(PlayerbotAI* botAI) { return new ConsussiveShotSnareTrigger(botAI); }
            static Trigger* pet_not_happy(PlayerbotAI* botAI) { return new HunterPetNotHappy(botAI); }
            static Trigger* serpent_sting_on_attacker(PlayerbotAI* botAI) { return new SerpentStingOnAttackerTrigger(botAI); }
            static Trigger* trueshot_aura(PlayerbotAI* botAI) { return new TrueshotAuraTrigger(botAI); }
            static Trigger* aspect_of_the_viper(PlayerbotAI* botAI) { return new HunterAspectOfTheViperTrigger(botAI); }
            static Trigger* black_arrow(PlayerbotAI* botAI) { return new BlackArrowTrigger(botAI); }
            static Trigger* NoStings(PlayerbotAI* botAI) { return new HunterNoStingsActiveTrigger(botAI); }
            static Trigger* hunters_pet_dead(PlayerbotAI* botAI) { return new HuntersPetDeadTrigger(botAI); }
            static Trigger* hunters_pet_low_health(PlayerbotAI* botAI) { return new HuntersPetLowHealthTrigger(botAI); }
            static Trigger* hunters_mark(PlayerbotAI* botAI) { return new HuntersMarkTrigger(botAI); }
            static Trigger* freezing_trap(PlayerbotAI* botAI) { return new FreezingTrapTrigger(botAI); }
            static Trigger* aspect_of_the_pack(PlayerbotAI* botAI) { return new HunterAspectOfThePackTrigger(botAI); }
            static Trigger* rapid_fire(PlayerbotAI* botAI) { return new RapidFireTrigger(botAI); }
            static Trigger* aspect_of_the_hawk(PlayerbotAI* botAI) { return new HunterAspectOfTheHawkTrigger(botAI); }
            static Trigger* aspect_of_the_wild(PlayerbotAI* botAI) { return new HunterAspectOfTheWildTrigger(botAI); }
        };
    };
};



namespace ai
{
    namespace hunter
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["auto shot"] = &AiObjectContextInternal::auto_shot;
                creators["aimed shot"] = &AiObjectContextInternal::aimed_shot;
                creators["chimera shot"] = &AiObjectContextInternal::chimera_shot;
                creators["explosive shot"] = &AiObjectContextInternal::explosive_shot;
                creators["arcane shot"] = &AiObjectContextInternal::arcane_shot;
                creators["concussive shot"] = &AiObjectContextInternal::concussive_shot;
                creators["distracting shot"] = &AiObjectContextInternal::distracting_shot;
                creators["multi-shot"] = &AiObjectContextInternal::multi_shot;
                creators["volley"] = &AiObjectContextInternal::volley;
                creators["serpent sting"] = &AiObjectContextInternal::serpent_sting;
                creators["serpent sting on attacker"] = &AiObjectContextInternal::serpent_sting_on_attacker;
                creators["wyvern sting"] = &AiObjectContextInternal::wyvern_sting;
                creators["viper sting"] = &AiObjectContextInternal::viper_sting;
                creators["scorpid sting"] = &AiObjectContextInternal::scorpid_sting;
                creators["hunter's mark"] = &AiObjectContextInternal::hunters_mark;
                creators["mend pet"] = &AiObjectContextInternal::mend_pet;
                creators["revive pet"] = &AiObjectContextInternal::revive_pet;
                creators["call pet"] = &AiObjectContextInternal::call_pet;
                creators["black arrow"] = &AiObjectContextInternal::black_arrow;
                creators["freezing trap"] = &AiObjectContextInternal::freezing_trap;
                creators["rapid fire"] = &AiObjectContextInternal::rapid_fire;
                creators["boost"] = &AiObjectContextInternal::rapid_fire;
                creators["readiness"] = &AiObjectContextInternal::readiness;
                creators["aspect of the hawk"] = &AiObjectContextInternal::aspect_of_the_hawk;
                creators["aspect of the wild"] = &AiObjectContextInternal::aspect_of_the_wild;
                creators["aspect of the viper"] = &AiObjectContextInternal::aspect_of_the_viper;
                creators["aspect of the pack"] = &AiObjectContextInternal::aspect_of_the_pack;
                creators["aspect of the cheetah"] = &AiObjectContextInternal::aspect_of_the_cheetah;
                creators["trueshot aura"] = &AiObjectContextInternal::trueshot_aura;
                creators["feign death"] = &AiObjectContextInternal::feign_death;
                creators["wing clip"] = &AiObjectContextInternal::wing_clip;
                creators["feed pet"] = &AiObjectContextInternal::feed_pet;
                creators["bestial wrath"] = &AiObjectContextInternal::bestial_wrath;
                creators["scare beast"] = &AiObjectContextInternal::scare_beast;
                creators["scare beast on cc"] = &AiObjectContextInternal::scare_beast_on_cc;
            }

        private:
            static Action* scare_beast(PlayerbotAI* botAI) { return new CastScareBeastAction(botAI); }
            static Action* scare_beast_on_cc(PlayerbotAI* botAI) { return new CastScareBeastCcAction(botAI); }
            static Action* bestial_wrath(PlayerbotAI* botAI) { return new CastBestialWrathAction(botAI); }
            static Action* feed_pet(PlayerbotAI* botAI) { return new FeedPetAction(botAI); }
            static Action* feign_death(PlayerbotAI* botAI) { return new CastFeignDeathAction(botAI); }
            static Action* trueshot_aura(PlayerbotAI* botAI) { return new CastTrueshotAuraAction(botAI); }
            static Action* auto_shot(PlayerbotAI* botAI) { return new CastAutoShotAction(botAI); }
            static Action* aimed_shot(PlayerbotAI* botAI) { return new CastAimedShotAction(botAI); }
            static Action* chimera_shot(PlayerbotAI* botAI) { return new CastChimeraShotAction(botAI); }
            static Action* explosive_shot(PlayerbotAI* botAI) { return new CastExplosiveShotAction(botAI); }
            static Action* arcane_shot(PlayerbotAI* botAI) { return new CastArcaneShotAction(botAI); }
            static Action* concussive_shot(PlayerbotAI* botAI) { return new CastConcussiveShotAction(botAI); }
            static Action* distracting_shot(PlayerbotAI* botAI) { return new CastDistractingShotAction(botAI); }
            static Action* multi_shot(PlayerbotAI* botAI) { return new CastMultiShotAction(botAI); }
            static Action* volley(PlayerbotAI* botAI) { return new CastVolleyAction(botAI); }
            static Action* serpent_sting(PlayerbotAI* botAI) { return new CastSerpentStingAction(botAI); }
            static Action* serpent_sting_on_attacker(PlayerbotAI* botAI) { return new CastSerpentStingOnAttackerAction(botAI); }
            static Action* wyvern_sting(PlayerbotAI* botAI) { return new CastWyvernStingAction(botAI); }
            static Action* viper_sting(PlayerbotAI* botAI) { return new CastViperStingAction(botAI); }
            static Action* scorpid_sting(PlayerbotAI* botAI) { return new CastScorpidStingAction(botAI); }
            static Action* hunters_mark(PlayerbotAI* botAI) { return new CastHuntersMarkAction(botAI); }
            static Action* mend_pet(PlayerbotAI* botAI) { return new CastMendPetAction(botAI); }
            static Action* revive_pet(PlayerbotAI* botAI) { return new CastRevivePetAction(botAI); }
            static Action* call_pet(PlayerbotAI* botAI) { return new CastCallPetAction(botAI); }
            static Action* black_arrow(PlayerbotAI* botAI) { return new CastBlackArrow(botAI); }
            static Action* freezing_trap(PlayerbotAI* botAI) { return new CastFreezingTrap(botAI); }
            static Action* rapid_fire(PlayerbotAI* botAI) { return new CastRapidFireAction(botAI); }
            static Action* readiness(PlayerbotAI* botAI) { return new CastReadinessAction(botAI); }
            static Action* aspect_of_the_hawk(PlayerbotAI* botAI) { return new CastAspectOfTheHawkAction(botAI); }
            static Action* aspect_of_the_wild(PlayerbotAI* botAI) { return new CastAspectOfTheWildAction(botAI); }
            static Action* aspect_of_the_viper(PlayerbotAI* botAI) { return new CastAspectOfTheViperAction(botAI); }
            static Action* aspect_of_the_pack(PlayerbotAI* botAI) { return new CastAspectOfThePackAction(botAI); }
            static Action* aspect_of_the_cheetah(PlayerbotAI* botAI) { return new CastAspectOfTheCheetahAction(botAI); }
            static Action* wing_clip(PlayerbotAI* botAI) { return new CastWingClipAction(botAI); }
        };
    };
};

HunterAiObjectContext::HunterAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new ai::hunter::StrategyFactoryInternal());
    strategyContexts.Add(new ai::hunter::BuffStrategyFactoryInternal());
    actionContexts.Add(new ai::hunter::AiObjectContextInternal());
    triggerContexts.Add(new ai::hunter::TriggerFactoryInternal());
}
