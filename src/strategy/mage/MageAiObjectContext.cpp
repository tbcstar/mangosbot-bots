#include "botpch.h"
#include "../../playerbot.h"
#include "../Strategy.h"
#include "MageActions.h"
#include "MageAiObjectContext.h"
#include "FrostMageStrategy.h"
#include "ArcaneMageStrategy.h"
#include "GenericMageNonCombatStrategy.h"
#include "FireMageStrategy.h"
#include "../generic/PullStrategy.h"
#include "MageTriggers.h"
#include "../NamedObjectContext.h"

using namespace botAI;


namespace botAI
{
    namespace mage
    {
        using namespace botAI;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &mage::StrategyFactoryInternal::nc;
                creators["pull"] = &mage::StrategyFactoryInternal::pull;
                creators["fire aoe"] = &mage::StrategyFactoryInternal::fire_aoe;
                creators["frost aoe"] = &mage::StrategyFactoryInternal::frost_aoe;
                creators["cure"] = &mage::StrategyFactoryInternal::cure;
                creators["buff"] = &mage::StrategyFactoryInternal::buff;
                creators["boost"] = &mage::StrategyFactoryInternal::boost;
                creators["cc"] = &mage::StrategyFactoryInternal::cc;
            }

        private:
            static Strategy* nc(PlayerbotAI* botAI) { return new GenericMageNonCombatStrategy(botAI); }
            static Strategy* pull(PlayerbotAI* botAI) { return new PullStrategy(botAI, "shoot"); }
            static Strategy* fire_aoe(PlayerbotAI* botAI) { return new FireMageAoeStrategy(botAI); }
            static Strategy* frost_aoe(PlayerbotAI* botAI) { return new FrostMageAoeStrategy(botAI); }
            static Strategy* cure(PlayerbotAI* botAI) { return new MageCureStrategy(botAI); }
            static Strategy* buff(PlayerbotAI* botAI) { return new MageBuffStrategy(botAI); }
            static Strategy* boost(PlayerbotAI* botAI) { return new MageBoostStrategy(botAI); }
            static Strategy* cc(PlayerbotAI* botAI) { return new MageCcStrategy(botAI); }
        };

        class MageStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            MageStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["frost"] = &mage::MageStrategyFactoryInternal::frost;
                creators["fire"] = &mage::MageStrategyFactoryInternal::fire;
                creators["arcane"] = &mage::MageStrategyFactoryInternal::arcane;
            }

        private:
            static Strategy* frost(PlayerbotAI* botAI) { return new FrostMageStrategy(botAI); }
            static Strategy* fire(PlayerbotAI* botAI) { return new FireMageStrategy(botAI); }
            static Strategy* arcane(PlayerbotAI* botAI) { return new ArcaneMageStrategy(botAI); }
        };

        class MageBuffStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            MageBuffStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["bmana"] = &mage::MageBuffStrategyFactoryInternal::bmana;
                creators["bdps"] = &mage::MageBuffStrategyFactoryInternal::bdps;
            }

        private:
            static Strategy* bmana(PlayerbotAI* botAI) { return new MageBuffManaStrategy(botAI); }
            static Strategy* bdps(PlayerbotAI* botAI) { return new MageBuffDpsStrategy(botAI); }
        };
    };
};


namespace botAI
{
    namespace mage
    {
        using namespace botAI;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["fireball"] = &TriggerFactoryInternal::fireball;
                creators["pyroblast"] = &TriggerFactoryInternal::pyroblast;
                creators["combustion"] = &TriggerFactoryInternal::combustion;
                creators["icy veins"] = &TriggerFactoryInternal::icy_veins;
                creators["arcane intellect"] = &TriggerFactoryInternal::arcane_intellect;
                creators["arcane intellect on party"] = &TriggerFactoryInternal::arcane_intellect_on_party;
                creators["mage armor"] = &TriggerFactoryInternal::mage_armor;
                creators["remove curse"] = &TriggerFactoryInternal::remove_curse;
                creators["remove curse on party"] = &TriggerFactoryInternal::remove_curse_on_party;
                creators["counterspell"] = &TriggerFactoryInternal::counterspell;
                creators["polymorph"] = &TriggerFactoryInternal::polymorph;
                creators["spellsteal"] = &TriggerFactoryInternal::spellsteal;
                creators["hot streak"] = &TriggerFactoryInternal::hot_streak;
                creators["living bomb"] = &TriggerFactoryInternal::living_bomb;
                creators["missile barrage"] = &TriggerFactoryInternal::missile_barrage;
                creators["arcane blast"] = &TriggerFactoryInternal::arcane_blast;
                creators["counterspell on enemy healer"] = &TriggerFactoryInternal::counterspell_enemy_healer;
                creators["arcane power"] = &TriggerFactoryInternal::arcane_power;
                creators["presence of mind"] = &TriggerFactoryInternal::presence_of_mind;

            }

        private:
            static Trigger* presence_of_mind(PlayerbotAI* botAI) { return new PresenceOfMindTrigger(botAI); }
            static Trigger* arcane_power(PlayerbotAI* botAI) { return new ArcanePowerTrigger(botAI); }
            static Trigger* hot_streak(PlayerbotAI* botAI) { return new HotStreakTrigger(botAI); }
            static Trigger* fireball(PlayerbotAI* botAI) { return new FireballTrigger(botAI); }
            static Trigger* pyroblast(PlayerbotAI* botAI) { return new PyroblastTrigger(botAI); }
            static Trigger* combustion(PlayerbotAI* botAI) { return new CombustionTrigger(botAI); }
            static Trigger* icy_veins(PlayerbotAI* botAI) { return new IcyVeinsTrigger(botAI); }
            static Trigger* arcane_intellect(PlayerbotAI* botAI) { return new ArcaneIntellectTrigger(botAI); }
            static Trigger* arcane_intellect_on_party(PlayerbotAI* botAI) { return new ArcaneIntellectOnPartyTrigger(botAI); }
            static Trigger* mage_armor(PlayerbotAI* botAI) { return new MageArmorTrigger(botAI); }
            static Trigger* remove_curse(PlayerbotAI* botAI) { return new RemoveCurseTrigger(botAI); }
            static Trigger* remove_curse_on_party(PlayerbotAI* botAI) { return new PartyMemberRemoveCurseTrigger(botAI); }
            static Trigger* counterspell(PlayerbotAI* botAI) { return new CounterspellInterruptSpellTrigger(botAI); }
            static Trigger* polymorph(PlayerbotAI* botAI) { return new PolymorphTrigger(botAI); }
            static Trigger* spellsteal(PlayerbotAI* botAI) { return new SpellstealTrigger(botAI); }
            static Trigger* living_bomb(PlayerbotAI* botAI) { return new LivingBombTrigger(botAI); }
            static Trigger* missile_barrage(PlayerbotAI* botAI) { return new MissileBarrageTrigger(botAI); }
            static Trigger* arcane_blast(PlayerbotAI* botAI) { return new ArcaneBlastTrigger(botAI); }
            static Trigger* counterspell_enemy_healer(PlayerbotAI* botAI) { return new CounterspellEnemyHealerTrigger(botAI); }
        };
    };
};


namespace botAI
{
    namespace mage
    {
        using namespace botAI;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["arcane power"] = &AiObjectContextInternal::arcane_power;
                creators["presence of mind"] = &AiObjectContextInternal::presence_of_mind;
                creators["frostbolt"] = &AiObjectContextInternal::frostbolt;
                creators["blizzard"] = &AiObjectContextInternal::blizzard;
                creators["frost nova"] = &AiObjectContextInternal::frost_nova;
                creators["arcane intellect"] = &AiObjectContextInternal::arcane_intellect;
                creators["arcane intellect on party"] = &AiObjectContextInternal::arcane_intellect_on_party;
                creators["conjure water"] = &AiObjectContextInternal::conjure_water;
                creators["conjure food"] = &AiObjectContextInternal::conjure_food;
                creators["molten armor"] = &AiObjectContextInternal::molten_armor;
                creators["mage armor"] = &AiObjectContextInternal::mage_armor;
                creators["ice armor"] = &AiObjectContextInternal::ice_armor;
                creators["frost armor"] = &AiObjectContextInternal::frost_armor;
                creators["fireball"] = &AiObjectContextInternal::fireball;
                creators["pyroblast"] = &AiObjectContextInternal::pyroblast;
                creators["flamestrike"] = &AiObjectContextInternal::flamestrike;
                creators["fire blast"] = &AiObjectContextInternal::fire_blast;
                creators["scorch"] = &AiObjectContextInternal::scorch;
                creators["counterspell"] = &AiObjectContextInternal::counterspell;
                creators["remove curse"] = &AiObjectContextInternal::remove_curse;
                creators["remove curse on party"] = &AiObjectContextInternal::remove_curse_on_party;
                creators["remove lesser curse"] = &AiObjectContextInternal::remove_lesser_curse;
                creators["remove lesser curse on party"] = &AiObjectContextInternal::remove_lesser_curse_on_party;
                creators["icy veins"] = &AiObjectContextInternal::icy_veins;
                creators["combustion"] = &AiObjectContextInternal::combustion;
                creators["ice block"] = &AiObjectContextInternal::ice_block;
                creators["polymorph"] = &AiObjectContextInternal::polymorph;
                creators["spellsteal"] = &AiObjectContextInternal::spellsteal;
                creators["living bomb"] = &AiObjectContextInternal::living_bomb;
                creators["dragon's breath"] = &AiObjectContextInternal::dragons_breath;
                creators["blast wave"] = &AiObjectContextInternal::blast_wave;
                creators["invisibility"] = &AiObjectContextInternal::invisibility;
                creators["evocation"] = &AiObjectContextInternal::evocation;
                creators["arcane blast"] = &AiObjectContextInternal::arcane_blast;
                creators["arcane barrage"] = &AiObjectContextInternal::arcane_barrage;
                creators["arcane missiles"] = &AiObjectContextInternal::arcane_missiles;
                creators["counterspell on enemy healer"] = &AiObjectContextInternal::counterspell_on_enemy_healer;
            }

        private:
            static Action* presence_of_mind(PlayerbotAI* botAI) { return new CastPresenceOfMindAction(botAI); }
            static Action* arcane_power(PlayerbotAI* botAI) { return new CastArcanePowerAction(botAI); }
            static Action* arcane_missiles(PlayerbotAI* botAI) { return new CastArcaneMissilesAction(botAI); }
            static Action* arcane_barrage(PlayerbotAI* botAI) { return new CastArcaneBarrageAction(botAI); }
            static Action* arcane_blast(PlayerbotAI* botAI) { return new CastArcaneBlastAction(botAI); }
            static Action* frostbolt(PlayerbotAI* botAI) { return new CastFrostboltAction(botAI); }
            static Action* blizzard(PlayerbotAI* botAI) { return new CastBlizzardAction(botAI); }
            static Action* frost_nova(PlayerbotAI* botAI) { return new CastFrostNovaAction(botAI); }
            static Action* arcane_intellect(PlayerbotAI* botAI) { return new CastArcaneIntellectAction(botAI); }
            static Action* arcane_intellect_on_party(PlayerbotAI* botAI) { return new CastArcaneIntellectOnPartyAction(botAI); }
            static Action* conjure_water(PlayerbotAI* botAI) { return new CastConjureWaterAction(botAI); }
            static Action* conjure_food(PlayerbotAI* botAI) { return new CastConjureFoodAction(botAI); }
            static Action* molten_armor(PlayerbotAI* botAI) { return new CastMoltenArmorAction(botAI); }
            static Action* mage_armor(PlayerbotAI* botAI) { return new CastMageArmorAction(botAI); }
            static Action* ice_armor(PlayerbotAI* botAI) { return new CastIceArmorAction(botAI); }
            static Action* frost_armor(PlayerbotAI* botAI) { return new CastFrostArmorAction(botAI); }
            static Action* fireball(PlayerbotAI* botAI) { return new CastFireballAction(botAI); }
            static Action* pyroblast(PlayerbotAI* botAI) { return new CastPyroblastAction(botAI); }
            static Action* flamestrike(PlayerbotAI* botAI) { return new CastFlamestrikeAction(botAI); }
            static Action* fire_blast(PlayerbotAI* botAI) { return new CastFireBlastAction(botAI); }
            static Action* scorch(PlayerbotAI* botAI) { return new CastScorchAction(botAI); }
            static Action* counterspell(PlayerbotAI* botAI) { return new CastCounterspellAction(botAI); }
            static Action* remove_curse(PlayerbotAI* botAI) { return new CastRemoveCurseAction(botAI); }
            static Action* remove_curse_on_party(PlayerbotAI* botAI) { return new CastRemoveCurseOnPartyAction(botAI); }
            static Action* remove_lesser_curse(PlayerbotAI* botAI) { return new CastRemoveLesserCurseAction(botAI); }
            static Action* remove_lesser_curse_on_party(PlayerbotAI* botAI) { return new CastRemoveLesserCurseOnPartyAction(botAI); }
            static Action* icy_veins(PlayerbotAI* botAI) { return new CastIcyVeinsAction(botAI); }
            static Action* combustion(PlayerbotAI* botAI) { return new CastCombustionAction(botAI); }
            static Action* ice_block(PlayerbotAI* botAI) { return new CastIceBlockAction(botAI); }
            static Action* polymorph(PlayerbotAI* botAI) { return new CastPolymorphAction(botAI); }
            static Action* spellsteal(PlayerbotAI* botAI) { return new CastSpellstealAction(botAI); }
            static Action* living_bomb(PlayerbotAI* botAI) { return new CastLivingBombAction(botAI); }
            static Action* dragons_breath(PlayerbotAI* botAI) { return new CastDragonsBreathAction(botAI); }
            static Action* blast_wave(PlayerbotAI* botAI) { return new CastBlastWaveAction(botAI); }
            static Action* invisibility(PlayerbotAI* botAI) { return new CastInvisibilityAction(botAI); }
            static Action* evocation(PlayerbotAI* botAI) { return new CastEvocationAction(botAI); }
            static Action* counterspell_on_enemy_healer(PlayerbotAI* botAI) { return new CastCounterspellOnEnemyHealerAction(botAI); }
        };
    };
};



MageAiObjectContext::MageAiObjectContext(PlayerbotAI* botAI) : AiObjectContext(botAI)
{
    strategyContexts.Add(new botAI::mage::StrategyFactoryInternal());
    strategyContexts.Add(new botAI::mage::MageStrategyFactoryInternal());
    strategyContexts.Add(new botAI::mage::MageBuffStrategyFactoryInternal());
    actionContexts.Add(new botAI::mage::AiObjectContextInternal());
    triggerContexts.Add(new botAI::mage::TriggerFactoryInternal());
}
