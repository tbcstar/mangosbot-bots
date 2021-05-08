#include "botpch.h"
#include "../../playerbot.h"
#include "ShamanActions.h"
#include "ShamanAiObjectContext.h"
#include "ShamanNonCombatStrategy.h"
#include "HealShamanStrategy.h"
#include "MeleeShamanStrategy.h"
#include "ShamanTriggers.h"
#include "../NamedObjectContext.h"
#include "TotemsShamanStrategy.h"
#include "CasterShamanStrategy.h"

using namespace ai;



namespace ai
{
    namespace shaman
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &shaman::StrategyFactoryInternal::nc;
                creators["totems"] = &shaman::StrategyFactoryInternal::totems;
                creators["melee aoe"] = &shaman::StrategyFactoryInternal::melee_aoe;
                creators["caster aoe"] = &shaman::StrategyFactoryInternal::caster_aoe;
                creators["cure"] = &shaman::StrategyFactoryInternal::cure;
            }

        private:
            static Strategy* nc(PlayerbotAI* botAI) { return new ShamanNonCombatStrategy(botAI); }
            static Strategy* totems(PlayerbotAI* botAI) { return new TotemsShamanStrategy(botAI); }
            static Strategy* melee_aoe(PlayerbotAI* botAI) { return new MeleeAoeShamanStrategy(botAI); }
            static Strategy* caster_aoe(PlayerbotAI* botAI) { return new CasterAoeShamanStrategy(botAI); }
            static Strategy* cure(PlayerbotAI* botAI) { return new ShamanCureStrategy(botAI); }
        };

        class BuffStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            BuffStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["bmana"] = &shaman::BuffStrategyFactoryInternal::bmana;
                creators["bdps"] = &shaman::BuffStrategyFactoryInternal::bdps;
            }

        private:
            static Strategy* bmana(PlayerbotAI* botAI) { return new ShamanBuffManaStrategy(botAI); }
            static Strategy* bdps(PlayerbotAI* botAI) { return new ShamanBuffDpsStrategy(botAI); }
        };

        class CombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            CombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["heal"] = &shaman::CombatStrategyFactoryInternal::heal;
                creators["melee"] = &shaman::CombatStrategyFactoryInternal::dps;
                creators["dps"] = &shaman::CombatStrategyFactoryInternal::dps;
                creators["caster"] = &shaman::CombatStrategyFactoryInternal::caster;
            }

        private:
            static Strategy* heal(PlayerbotAI* botAI) { return new HealShamanStrategy(botAI); }
            static Strategy* dps(PlayerbotAI* botAI) { return new MeleeShamanStrategy(botAI); }
            static Strategy* caster(PlayerbotAI* botAI) { return new CasterShamanStrategy(botAI); }
        };
    };
};

namespace ai
{
    namespace shaman
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["grace of air totem"] = &TriggerFactoryInternal::grace_of_air_totem;
                creators["windfury totem"] = &TriggerFactoryInternal::windfury_totem;
                creators["mana spring totem"] = &TriggerFactoryInternal::mana_spring_totem;
                creators["flametongue totem"] = &TriggerFactoryInternal::flametongue_totem;
                creators["strength of earth totem"] = &TriggerFactoryInternal::strength_of_earth_totem;
                creators["magma totem"] = &TriggerFactoryInternal::magma_totem;
                creators["searing totem"] = &TriggerFactoryInternal::searing_totem;
                creators["wind shear"] = &TriggerFactoryInternal::wind_shear;
                creators["purge"] = &TriggerFactoryInternal::purge;
                creators["shaman weapon"] = &TriggerFactoryInternal::shaman_weapon;
                creators["water shield"] = &TriggerFactoryInternal::water_shield;
                creators["lightning shield"] = &TriggerFactoryInternal::lightning_shield;
                creators["water breathing"] = &TriggerFactoryInternal::water_breathing;
                creators["water walking"] = &TriggerFactoryInternal::water_walking;
                creators["water breathing on party"] = &TriggerFactoryInternal::water_breathing_on_party;
                creators["water walking on party"] = &TriggerFactoryInternal::water_walking_on_party;
                creators["cleanse spirit poison"] = &TriggerFactoryInternal::cleanse_poison;
                creators["cleanse spirit curse"] = &TriggerFactoryInternal::cleanse_curse;
                creators["cleanse spirit disease"] = &TriggerFactoryInternal::cleanse_disease;
                creators["party member cleanse spirit poison"] = &TriggerFactoryInternal::party_member_cleanse_poison;
                creators["party member cleanse spirit curse"] = &TriggerFactoryInternal::party_member_cleanse_curse;
                creators["party member cleanse spirit disease"] = &TriggerFactoryInternal::party_member_cleanse_disease;
                creators["shock"] = &TriggerFactoryInternal::shock;
                creators["frost shock snare"] = &TriggerFactoryInternal::frost_shock_snare;
                creators["heroism"] = &TriggerFactoryInternal::heroism;
                creators["bloodlust"] = &TriggerFactoryInternal::bloodlust;
                creators["maelstrom weapon"] = &TriggerFactoryInternal::maelstrom_weapon;
                creators["wind shear on enemy healer"] = &TriggerFactoryInternal::wind_shear_on_enemy_healer;
                creators["cure poison"] = &TriggerFactoryInternal::cure_poison;
                creators["party member cure poison"] = &TriggerFactoryInternal::party_member_cure_poison;
                creators["cure disease"] = &TriggerFactoryInternal::cure_disease;
                creators["party member cure disease"] = &TriggerFactoryInternal::party_member_cure_disease;
            }

        private:
            static Trigger* maelstrom_weapon(PlayerbotAI* botAI) { return new MaelstromWeaponTrigger(botAI); }
            static Trigger* heroism(PlayerbotAI* botAI) { return new HeroismTrigger(botAI); }
            static Trigger* bloodlust(PlayerbotAI* botAI) { return new BloodlustTrigger(botAI); }
            static Trigger* party_member_cleanse_disease(PlayerbotAI* botAI) { return new PartyMemberCleanseSpiritDiseaseTrigger(botAI); }
            static Trigger* party_member_cleanse_curse(PlayerbotAI* botAI) { return new PartyMemberCleanseSpiritCurseTrigger(botAI); }
            static Trigger* party_member_cleanse_poison(PlayerbotAI* botAI) { return new PartyMemberCleanseSpiritPoisonTrigger(botAI); }
            static Trigger* cleanse_disease(PlayerbotAI* botAI) { return new CleanseSpiritDiseaseTrigger(botAI); }
            static Trigger* cleanse_curse(PlayerbotAI* botAI) { return new CleanseSpiritCurseTrigger(botAI); }
            static Trigger* cleanse_poison(PlayerbotAI* botAI) { return new CleanseSpiritPoisonTrigger(botAI); }
            static Trigger* water_breathing(PlayerbotAI* botAI) { return new WaterBreathingTrigger(botAI); }
            static Trigger* water_walking(PlayerbotAI* botAI) { return new WaterWalkingTrigger(botAI); }
            static Trigger* water_breathing_on_party(PlayerbotAI* botAI) { return new WaterBreathingOnPartyTrigger(botAI); }
            static Trigger* water_walking_on_party(PlayerbotAI* botAI) { return new WaterWalkingOnPartyTrigger(botAI); }
            static Trigger* windfury_totem(PlayerbotAI* botAI) { return new WindfuryTotemTrigger(botAI); }
            static Trigger* grace_of_air_totem(PlayerbotAI* botAI) { return new GraceOfAirTotemTrigger(botAI); }
            static Trigger* mana_spring_totem(PlayerbotAI* botAI) { return new ManaSpringTotemTrigger(botAI); }
            static Trigger* flametongue_totem(PlayerbotAI* botAI) { return new FlametongueTotemTrigger(botAI); }
            static Trigger* strength_of_earth_totem(PlayerbotAI* botAI) { return new StrengthOfEarthTotemTrigger(botAI); }
            static Trigger* magma_totem(PlayerbotAI* botAI) { return new MagmaTotemTrigger(botAI); }
            static Trigger* searing_totem(PlayerbotAI* botAI) { return new SearingTotemTrigger(botAI); }
            static Trigger* wind_shear(PlayerbotAI* botAI) { return new WindShearInterruptSpellTrigger(botAI); }
            static Trigger* purge(PlayerbotAI* botAI) { return new PurgeTrigger(botAI); }
            static Trigger* shaman_weapon(PlayerbotAI* botAI) { return new ShamanWeaponTrigger(botAI); }
            static Trigger* water_shield(PlayerbotAI* botAI) { return new WaterShieldTrigger(botAI); }
            static Trigger* lightning_shield(PlayerbotAI* botAI) { return new LightningShieldTrigger(botAI); }
            static Trigger* shock(PlayerbotAI* botAI) { return new ShockTrigger(botAI); }
            static Trigger* frost_shock_snare(PlayerbotAI* botAI) { return new FrostShockSnareTrigger(botAI); }
            static Trigger* wind_shear_on_enemy_healer(PlayerbotAI* botAI) { return new WindShearInterruptEnemyHealerSpellTrigger(botAI); }
            static Trigger* cure_poison(PlayerbotAI* botAI) { return new CurePoisonTrigger(botAI); }
            static Trigger* party_member_cure_poison(PlayerbotAI* botAI) { return new PartyMemberCurePoisonTrigger(botAI); }
            static Trigger* cure_disease(PlayerbotAI* botAI) { return new CureDiseaseTrigger(botAI); }
            static Trigger* party_member_cure_disease(PlayerbotAI* botAI) { return new PartyMemberCureDiseaseTrigger(botAI); }
        };
    };
};


namespace ai
{
    namespace shaman
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["water shield"] = &AiObjectContextInternal::water_shield;
                creators["lightning shield"] = &AiObjectContextInternal::lightning_shield;
                creators["strength of earth totem"] = &AiObjectContextInternal::strength_of_earth_totem;
                creators["flametongue totem"] = &AiObjectContextInternal::flametongue_totem;
                creators["searing totem"] = &AiObjectContextInternal::searing_totem;
                creators["magma totem"] = &AiObjectContextInternal::magma_totem;
                creators["windfury totem"] = &AiObjectContextInternal::windfury_totem;
                creators["grace of air totem"] = &AiObjectContextInternal::grace_of_air_totem;
                creators["mana spring totem"] = &AiObjectContextInternal::mana_spring_totem;
                creators["mana tide totem"] = &AiObjectContextInternal::mana_tide_totem;
                creators["healing stream totem"] = &AiObjectContextInternal::healing_stream_totem;
                creators["wind shear"] = &AiObjectContextInternal::wind_shear;
                creators["wind shear on enemy healer"] = &AiObjectContextInternal::wind_shear_on_enemy_healer;
                creators["rockbiter weapon"] = &AiObjectContextInternal::rockbiter_weapon;
                creators["flametongue weapon"] = &AiObjectContextInternal::flametongue_weapon;
                creators["frostbrand weapon"] = &AiObjectContextInternal::frostbrand_weapon;
                creators["windfury weapon"] = &AiObjectContextInternal::windfury_weapon;
                creators["earthliving weapon"] = &AiObjectContextInternal::earthliving_weapon;
                creators["purge"] = &AiObjectContextInternal::purge;
                creators["healing wave"] = &AiObjectContextInternal::healing_wave;
                creators["lesser healing wave"] = &AiObjectContextInternal::lesser_healing_wave;
                creators["healing wave on party"] = &AiObjectContextInternal::healing_wave_on_party;
                creators["lesser healing wave on party"] = &AiObjectContextInternal::lesser_healing_wave_on_party;
                creators["earth shield"] = &AiObjectContextInternal::earth_shield;
                creators["earth shield on party"] = &AiObjectContextInternal::earth_shield_on_party;
                creators["chain heal"] = &AiObjectContextInternal::chain_heal;
                creators["riptide"] = &AiObjectContextInternal::riptide;
                creators["riptide on party"] = &AiObjectContextInternal::riptide_on_party;
                creators["stormstrike"] = &AiObjectContextInternal::stormstrike;
                creators["lava lash"] = &AiObjectContextInternal::lava_lash;
                creators["fire nova"] = &AiObjectContextInternal::fire_nova;
                creators["ancestral spirit"] = &AiObjectContextInternal::ancestral_spirit;
                creators["water walking"] = &AiObjectContextInternal::water_walking;
                creators["water breathing"] = &AiObjectContextInternal::water_breathing;
                creators["water walking on party"] = &AiObjectContextInternal::water_walking_on_party;
                creators["water breathing on party"] = &AiObjectContextInternal::water_breathing_on_party;
                creators["cleanse spirit"] = &AiObjectContextInternal::cleanse_spirit;
                creators["cleanse spirit poison on party"] = &AiObjectContextInternal::cleanse_spirit_poison_on_party;
                creators["cleanse spirit disease on party"] = &AiObjectContextInternal::cleanse_spirit_disease_on_party;
                creators["cleanse spirit curse on party"] = &AiObjectContextInternal::cleanse_spirit_curse_on_party;
                creators["flame shock"] = &AiObjectContextInternal::flame_shock;
                creators["earth shock"] = &AiObjectContextInternal::earth_shock;
                creators["frost shock"] = &AiObjectContextInternal::frost_shock;
                creators["chain lightning"] = &AiObjectContextInternal::chain_lightning;
                creators["lightning bolt"] = &AiObjectContextInternal::lightning_bolt;
                creators["thunderstorm"] = &AiObjectContextInternal::thunderstorm;
                creators["heroism"] = &AiObjectContextInternal::heroism;
                creators["bloodlust"] = &AiObjectContextInternal::bloodlust;
                creators["cure disease"] = &AiObjectContextInternal::cure_disease;
                creators["cure disease on party"] = &AiObjectContextInternal::cure_disease_on_party;
                creators["cure poison"] = &AiObjectContextInternal::cure_poison;
                creators["cure poison on party"] = &AiObjectContextInternal::cure_poison_on_party;
            }

        private:
            static Action* heroism(PlayerbotAI* botAI) { return new CastHeroismAction(botAI); }
            static Action* bloodlust(PlayerbotAI* botAI) { return new CastBloodlustAction(botAI); }
            static Action* thunderstorm(PlayerbotAI* botAI) { return new CastThunderstormAction(botAI); }
            static Action* lightning_bolt(PlayerbotAI* botAI) { return new CastLightningBoltAction(botAI); }
            static Action* chain_lightning(PlayerbotAI* botAI) { return new CastChainLightningAction(botAI); }
            static Action* frost_shock(PlayerbotAI* botAI) { return new CastFrostShockAction(botAI); }
            static Action* earth_shock(PlayerbotAI* botAI) { return new CastEarthShockAction(botAI); }
            static Action* flame_shock(PlayerbotAI* botAI) { return new CastFlameShockAction(botAI); }
            static Action* cleanse_spirit_poison_on_party(PlayerbotAI* botAI) { return new CastCleanseSpiritPoisonOnPartyAction(botAI); }
            static Action* cleanse_spirit_disease_on_party(PlayerbotAI* botAI) { return new CastCleanseSpiritDiseaseOnPartyAction(botAI); }
            static Action* cleanse_spirit_curse_on_party(PlayerbotAI* botAI) { return new CastCleanseSpiritCurseOnPartyAction(botAI); }
            static Action* cleanse_spirit(PlayerbotAI* botAI) { return new CastCleanseSpiritAction(botAI); }
            static Action* water_walking(PlayerbotAI* botAI) { return new CastWaterWalkingAction(botAI); }
            static Action* water_breathing(PlayerbotAI* botAI) { return new CastWaterBreathingAction(botAI); }
            static Action* water_walking_on_party(PlayerbotAI* botAI) { return new CastWaterWalkingOnPartyAction(botAI); }
            static Action* water_breathing_on_party(PlayerbotAI* botAI) { return new CastWaterBreathingOnPartyAction(botAI); }
            static Action* water_shield(PlayerbotAI* botAI) { return new CastWaterShieldAction(botAI); }
            static Action* lightning_shield(PlayerbotAI* botAI) { return new CastLightningShieldAction(botAI); }
            static Action* strength_of_earth_totem(PlayerbotAI* botAI) { return new CastStrengthOfEarthTotemAction(botAI); }
            static Action* flametongue_totem(PlayerbotAI* botAI) { return new CastFlametongueTotemAction(botAI); }
            static Action* magma_totem(PlayerbotAI* botAI) { return new CastMagmaTotemAction(botAI); }
            static Action* searing_totem(PlayerbotAI* botAI) { return new CastSearingTotemAction(botAI); }
            static Action* fire_nova(PlayerbotAI* botAI) { return new CastFireNovaAction(botAI); }
            static Action* windfury_totem(PlayerbotAI* botAI) { return new CastWindfuryTotemAction(botAI); }
            static Action* grace_of_air_totem(PlayerbotAI* botAI) { return new CastGraceOfAirTotemAction(botAI); }
            static Action* mana_spring_totem(PlayerbotAI* botAI) { return new CastManaSpringTotemAction(botAI); }
            static Action* mana_tide_totem(PlayerbotAI* botAI) { return new CastManaTideTotemAction(botAI); }
            static Action* healing_stream_totem(PlayerbotAI* botAI) { return new CastHealingStreamTotemAction(botAI); }
            static Action* wind_shear(PlayerbotAI* botAI) { return new CastWindShearAction(botAI); }
            static Action* rockbiter_weapon(PlayerbotAI* botAI) { return new CastRockbiterWeaponAction(botAI); }
            static Action* flametongue_weapon(PlayerbotAI* botAI) { return new CastFlametongueWeaponAction(botAI); }
            static Action* frostbrand_weapon(PlayerbotAI* botAI) { return new CastFrostbrandWeaponAction(botAI); }
            static Action* windfury_weapon(PlayerbotAI* botAI) { return new CastWindfuryWeaponAction(botAI); }
            static Action* earthliving_weapon(PlayerbotAI* botAI) { return new CastEarthlivingWeaponAction(botAI); }
            static Action* purge(PlayerbotAI* botAI) { return new CastPurgeAction(botAI); }
            static Action* healing_wave(PlayerbotAI* botAI) { return new CastHealingWaveAction(botAI); }
            static Action* lesser_healing_wave(PlayerbotAI* botAI) { return new CastLesserHealingWaveAction(botAI); }
            static Action* healing_wave_on_party(PlayerbotAI* botAI) { return new CastHealingWaveOnPartyAction(botAI); }
            static Action* lesser_healing_wave_on_party(PlayerbotAI* botAI) { return new CastLesserHealingWaveOnPartyAction(botAI); }
            static Action* earth_shield(PlayerbotAI* botAI) { return new CastEarthShieldAction(botAI); }
            static Action* earth_shield_on_party(PlayerbotAI* botAI) { return new CastEarthShieldOnPartyAction(botAI); }
            static Action* chain_heal(PlayerbotAI* botAI) { return new CastChainHealAction(botAI); }
            static Action* riptide(PlayerbotAI* botAI) { return new CastRiptideAction(botAI); }
            static Action* riptide_on_party(PlayerbotAI* botAI) { return new CastRiptideOnPartyAction(botAI); }
            static Action* stormstrike(PlayerbotAI* botAI) { return new CastStormstrikeAction(botAI); }
            static Action* lava_lash(PlayerbotAI* botAI) { return new CastLavaLashAction(botAI); }
            static Action* ancestral_spirit(PlayerbotAI* botAI) { return new CastAncestralSpiritAction(botAI); }
            static Action* wind_shear_on_enemy_healer(PlayerbotAI* botAI) { return new CastWindShearOnEnemyHealerAction(botAI); }
            static Action* cure_poison(PlayerbotAI* botAI) { return new CastCurePoisonAction(botAI); }
            static Action* cure_poison_on_party(PlayerbotAI* botAI) { return new CastCurePoisonOnPartyAction(botAI); }
            static Action* cure_disease(PlayerbotAI* botAI) { return new CastCureDiseaseAction(botAI); }
            static Action* cure_disease_on_party(PlayerbotAI* botAI) { return new CastCureDiseaseOnPartyAction(botAI); }
        };
    };
};



ShamanAiObjectContext::ShamanAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new ai::shaman::StrategyFactoryInternal());
    strategyContexts.Add(new ai::shaman::CombatStrategyFactoryInternal());
    strategyContexts.Add(new ai::shaman::BuffStrategyFactoryInternal());
    actionContexts.Add(new ai::shaman::AiObjectContextInternal());
    triggerContexts.Add(new ai::shaman::TriggerFactoryInternal());
}
