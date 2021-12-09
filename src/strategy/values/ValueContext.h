/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ActiveSpellValue.h"
#include "AlwaysLootListValue.h"
#include "AoeHealValues.h"
#include "AoeValues.h"
#include "AttackerCountValues.h"
#include "AttackersValue.h"
#include "AttackerWithoutAuraTargetValue.h"
#include "AvailableLootValue.h"
#include "CcTargetValue.h"
#include "ChatValue.h"
#include "CollisionValue.h"
#include "CraftValue.h"
#include "CurrentCcTargetValue.h"
#include "CurrentTargetValue.h"
#include "DpsTargetValue.h"
#include "DuelTargetValue.h"
#include "DistanceValue.h"
#include "EnemyHealerTargetValue.h"
#include "EnemyPlayerValue.h"
#include "Formations.h"
#include "GrindTargetValue.h"
#include "HasAvailableLootValue.h"
#include "HasTotemValue.h"
#include "InvalidTargetValue.h"
#include "ItemUsageValue.h"
#include "IsBehindValue.h"
#include "IsFacingValue.h"
#include "IsMovingValue.h"
#include "ItemCountValue.h"
#include "ItemForSpellValue.h"
#include "LastMovementValue.h"
#include "LastSaidValue.h"
#include "LastSpellCastValue.h"
#include "LastSpellCastTimeValue.h"
#include "LeastHpTargetValue.h"
#include "LfgValues.h"
#include "LineTargetValue.h"
#include "LogLevelValue.h"
#include "LootStrategyValue.h"
#include "ManaSaveLevelValue.h"
#include "MasterTargetValue.h"
#include "NearestAdsValue.h"
#include "NearestCorpsesValue.h"
#include "NearestFriendlyPlayersValue.h"
#include "NearestGameObjects.h"
#include "NearestNonBotPlayersValue.h"
#include "NearestNpcsValue.h"
#include "NewPlayerNearbyValue.h"
#include "OutfitListValue.h"
#include "QuestValues.h"
#include "PartyMemberWithoutAuraValue.h"
#include "PartyMemberWithoutItemValue.h"
#include "PartyMemberToDispel.h"
#include "PartyMemberToHeal.h"
#include "PartyMemberToResurrect.h"
#include "PetTargetValue.h"
#include "PositionValue.h"
#include "PossibleRpgTargetsValue.h"
#include "PossibleTargetsValue.h"
#include "PvpValues.h"
#include "RandomBotUpdateValue.h"
#include "RangeValues.h"
#include "RtiTargetValue.h"
#include "RtiValue.h"
#include "SelfTargetValue.h"
#include "SkipSpellsListValue.h"
#include "SnareTargetValue.h"
#include "SpellCastUsefulValue.h"
#include "SpellIdValue.h"
#include "Stances.h"
#include "StatsValues.h"
#include "TankTargetValue.h"
#include "ThreatValues.h"

class PlayerbotAI;

class ValueContext : public NamedObjectContext<UntypedValue>
{
    public:
        ValueContext()
        {
            creators["active spell"] = &ValueContext::active_spell;
            creators["craft"] = &ValueContext::craft;
            creators["collision"] = &ValueContext::collision;
            creators["skip spells list"] = &ValueContext::skip_spells_list_value;
            creators["nearest game objects"] = &ValueContext::nearest_game_objects;
            creators["nearest game objects no los"] = &ValueContext::nearest_game_objects_no_los;
            creators["closest game objects"] = &ValueContext::closest_game_objects;
            creators["nearest npcs"] = &ValueContext::nearest_npcs;
            creators["nearest friendly players"] = &ValueContext::nearest_friendly_players;
            creators["closest friendly players"] = &ValueContext::closest_friendly_players;
            creators["nearest enemy players"] = &ValueContext::nearest_enemy_players;
            creators["possible targets"] = &ValueContext::possible_targets;
            creators["possible targets no los"] = &ValueContext::possible_targets_no_los;
            creators["possible adds"] = &ValueContext::possible_adds;
            creators["all targets"] = &ValueContext::all_targets;
            creators["possible rpg targets"] = &ValueContext::possible_rpg_targets;
            creators["nearest adds"] = &ValueContext::nearest_adds;
            creators["nearest corpses"] = &ValueContext::nearest_corpses;
            creators["log level"] = &ValueContext::log_level;
            creators["party member without aura"] = &ValueContext::party_member_without_aura;
            creators["attacker without aura"] = &ValueContext::attacker_without_aura;
            creators["party member to heal"] = &ValueContext::party_member_to_heal;
            creators["party member to resurrect"] = &ValueContext::party_member_to_resurrect;
            creators["current target"] = &ValueContext::current_target;
            creators["self target"] = &ValueContext::self_target;
            creators["master target"] = &ValueContext::master;
            creators["line target"] = &ValueContext::line_target;
            creators["tank target"] = &ValueContext::tank_target;
            creators["dps target"] = &ValueContext::dps_target;
            creators["dps aoe target"] = &ValueContext::dps_aoe_target;
            creators["least hp target"] = &ValueContext::least_hp_target;
            creators["enemy player target"] = &ValueContext::enemy_player_target;
            creators["cc target"] = &ValueContext::cc_target;
            creators["current cc target"] = &ValueContext::current_cc_target;
            creators["pet target"] = &ValueContext::pet_target;
            creators["old target"] = &ValueContext::old_target;
            creators["grind target"] = &ValueContext::grind_target;
            creators["rti target"] = &ValueContext::rti_target;
            creators["rti cc target"] = &ValueContext::rti_cc_target;
            creators["duel target"] = &ValueContext::duel_target;
            creators["party member to dispel"] = &ValueContext::party_member_to_dispel;
            creators["health"] = &ValueContext::health;
            creators["rage"] = &ValueContext::rage;
            creators["energy"] = &ValueContext::energy;
            creators["mana"] = &ValueContext::mana;
            creators["combo"] = &ValueContext::combo;
            creators["dead"] = &ValueContext::dead;
            creators["pet dead"] = &ValueContext::pet_dead;
            creators["pet happy"] = &ValueContext::pet_happy;
            creators["has mana"] = &ValueContext::has_mana;
            creators["attacker count"] = &ValueContext::attacker_count;
            creators["my attacker count"] = &ValueContext::my_attacker_count;
            creators["has aggro"] = &ValueContext::has_aggro;
            creators["mounted"] = &ValueContext::mounted;

            creators["can loot"] = &ValueContext::can_loot;
            creators["loot target"] = &ValueContext::loot_target;
            creators["available loot"] = &ValueContext::available_loot;
            creators["has available loot"] = &ValueContext::has_available_loot;
            creators["always loot list"] = &ValueContext::always_loot_list;
            creators["loot strategy"] = &ValueContext::loot_strategy;
            creators["last movement"] = &ValueContext::last_movement;
            creators["stay time"] = &ValueContext::stay_time;
            creators["last taxi"] = &ValueContext::last_movement;
            creators["last area trigger"] = &ValueContext::last_movement;
            creators["distance"] = &ValueContext::distance;
            creators["moving"] = &ValueContext::moving;
            creators["swimming"] = &ValueContext::swimming;
            creators["behind"] = &ValueContext::behind;
            creators["facing"] = &ValueContext::facing;

            creators["item count"] = &ValueContext::item_count;
            creators["inventory items"] = &ValueContext::inventory_item;

            creators["spell id"] = &ValueContext::spell_id;
            creators["item for spell"] = &ValueContext::item_for_spell;
            creators["spell cast useful"] = &ValueContext::spell_cast_useful;
            creators["last spell cast"] = &ValueContext::last_spell_cast;
            creators["last spell cast time"] = &ValueContext::last_spell_cast_time;
            creators["chat"] = &ValueContext::chat;
            creators["has totem"] = &ValueContext::has_totem;

            creators["aoe heal"] = &ValueContext::aoe_heal;

            creators["rti cc"] = &ValueContext::rti_cc;
            creators["rti"] = &ValueContext::rti;
            creators["position"] = &ValueContext::position;
            creators["threat"] = &ValueContext::threat;

            creators["balance"] = &ValueContext::balance;
            creators["attackers"] = &ValueContext::attackers;
            creators["invalid target"] = &ValueContext::invalid_target;
            creators["mana save level"] = &ValueContext::mana_save_level;
            creators["combat"] = &ValueContext::combat;
            creators["lfg proposal"] = &ValueContext::lfg_proposal;
            creators["bag space"] = &ValueContext::bag_space;
            creators["durability"] = &ValueContext::durability;
            creators["repair cost"] = &ValueContext::repair_cost;
            creators["enemy healer target"] = &ValueContext::enemy_healer_target;
            creators["snare target"] = &ValueContext::snare_target;
            creators["formation"] = &ValueContext::formation;
            creators["stance"] = &ValueContext::stance;
            creators["item usage"] = &ValueContext::item_usage;
            creators["speed"] = &ValueContext::speed;
            creators["last said"] = &ValueContext::last_said;
            creators["last emote"] = &ValueContext::last_emote;

            creators["aoe count"] = &ValueContext::aoe_count;
            creators["aoe position"] = &ValueContext::aoe_position;
            creators["outfit list"] = &ValueContext::outfit_list_value;

            creators["random bot update"] = &ValueContext::random_bot_update_value;
            creators["nearest non bot players"] = &ValueContext::nearest_non_bot_players;
            creators["new player nearby"] = &ValueContext::new_player_nearby;
            creators["already seen players"] = &ValueContext::already_seen_players;
            creators["rpg target"] = &ValueContext::rpg_target;
            creators["ignore rpg target"] = &ValueContext::ignore_rpg_target;
            creators["travel target"] = &ValueContext::travel_target;
            creators["talk target"] = &ValueContext::talk_target;
            creators["pull target"] = &ValueContext::pull_target;
            creators["group"] = &ValueContext::group;
            creators["range"] = &ValueContext::range;
            creators["inside target"] = &ValueContext::inside_target;
            creators["party member without item"] = &ValueContext::party_member_without_item;
            creators["party member without food"] = &ValueContext::party_member_without_food;
            creators["party member without water"] = &ValueContext::party_member_without_water;
            creators["death count"] = &ValueContext::death_count;

            creators["bg type"] = &ValueContext::bg_type;
            creators["arena type"] = &ValueContext::arena_type;
            creators["bg role"] = &ValueContext::bg_role;
            creators["bg master"] = &ValueContext::bg_master;
            creators["enemy flag carrier"] = &ValueContext::enemy_fc;
            creators["team flag carrier"] = &ValueContext::team_fc;

            creators["home bind"] = &ValueContext::home_bind;
            creators["last long move"] = &ValueContext::last_long_move;

            creators["active quest givers"] = &ValueContext::active_quest_givers;
            creators["active quest takers"] = &ValueContext::active_quest_takers;
            creators["active quest objectives"] = &ValueContext::active_quest_objectives;
            creators["free quest log slots"] = &ValueContext::free_quest_log_slots;
        }

    private:
        static UntypedValue* party_member_without_water(PlayerbotAI* botAI) { return new PartyMemberWithoutWaterValue(botAI); }
        static UntypedValue* party_member_without_food(PlayerbotAI* botAI) { return new PartyMemberWithoutFoodValue(botAI); }
        static UntypedValue* party_member_without_item(PlayerbotAI* botAI) { return new PartyMemberWithoutItemValue(botAI); }
        static UntypedValue* inside_target(PlayerbotAI* botAI) { return new InsideTargetValue(botAI); }
        static UntypedValue* range(PlayerbotAI* botAI) { return new RangeValue(botAI); }
        static UntypedValue* active_spell(PlayerbotAI* botAI) { return new ActiveSpellValue(botAI); }
        static UntypedValue* group(PlayerbotAI* botAI) { return new IsInGroupValue(botAI); }
        static UntypedValue* craft(PlayerbotAI* botAI) { return new CraftValue(botAI); }
        static UntypedValue* collision(PlayerbotAI* botAI) { return new CollisionValue(botAI); }
        static UntypedValue* already_seen_players(PlayerbotAI* botAI) { return new AlreadySeenPlayersValue(botAI); }
        static UntypedValue* new_player_nearby(PlayerbotAI* botAI) { return new NewPlayerNearbyValue(botAI); }
        static UntypedValue* item_usage(PlayerbotAI* botAI) { return new ItemUsageValue(botAI); }
        static UntypedValue* formation(PlayerbotAI* botAI) { return new FormationValue(botAI); }
        static UntypedValue* stance(PlayerbotAI* botAI) { return new StanceValue(botAI); }
        static UntypedValue* mana_save_level(PlayerbotAI* botAI) { return new ManaSaveLevelValue(botAI); }
        static UntypedValue* invalid_target(PlayerbotAI* botAI) { return new InvalidTargetValue(botAI); }
        static UntypedValue* balance(PlayerbotAI* botAI) { return new BalancePercentValue(botAI); }
        static UntypedValue* attackers(PlayerbotAI* botAI) { return new AttackersValue(botAI); }

        static UntypedValue* position(PlayerbotAI* botAI) { return new PositionValue(botAI); }
        static UntypedValue* rti(PlayerbotAI* botAI) { return new RtiValue(botAI); }
        static UntypedValue* rti_cc(PlayerbotAI* botAI) { return new RtiCcValue(botAI); }

        static UntypedValue* aoe_heal(PlayerbotAI* botAI) { return new AoeHealValue(botAI); }

        static UntypedValue* chat(PlayerbotAI* botAI) { return new ChatValue(botAI); }
        static UntypedValue* last_spell_cast(PlayerbotAI* botAI) { return new LastSpellCastValue(botAI); }
        static UntypedValue* last_spell_cast_time(PlayerbotAI* botAI) { return new LastSpellCastTimeValue(botAI); }
        static UntypedValue* spell_cast_useful(PlayerbotAI* botAI) { return new SpellCastUsefulValue(botAI); }
        static UntypedValue* item_for_spell(PlayerbotAI* botAI) { return new ItemForSpellValue(botAI); }
        static UntypedValue* spell_id(PlayerbotAI* botAI) { return new SpellIdValue(botAI); }
        static UntypedValue* inventory_item(PlayerbotAI* botAI) { return new InventoryItemValue(botAI); }
        static UntypedValue* item_count(PlayerbotAI* botAI) { return new ItemCountValue(botAI); }
        static UntypedValue* behind(PlayerbotAI* botAI) { return new IsBehindValue(botAI); }
        static UntypedValue* facing(PlayerbotAI* botAI) { return new IsFacingValue(botAI); }
        static UntypedValue* moving(PlayerbotAI* botAI) { return new IsMovingValue(botAI); }
        static UntypedValue* swimming(PlayerbotAI* botAI) { return new IsSwimmingValue(botAI); }
        static UntypedValue* distance(PlayerbotAI* botAI) { return new DistanceValue(botAI); }
        static UntypedValue* last_movement(PlayerbotAI* botAI) { return new LastMovementValue(botAI); }
        static UntypedValue* stay_time(PlayerbotAI* botAI) { return new StayTimeValue(botAI); }

        static UntypedValue* can_loot(PlayerbotAI* botAI) { return new CanLootValue(botAI); }
        static UntypedValue* available_loot(PlayerbotAI* botAI) { return new AvailableLootValue(botAI); }
        static UntypedValue* loot_target(PlayerbotAI* botAI) { return new LootTargetValue(botAI); }
        static UntypedValue* has_available_loot(PlayerbotAI* botAI) { return new HasAvailableLootValue(botAI); }
        static UntypedValue* always_loot_list(PlayerbotAI* botAI) { return new AlwaysLootListValue(botAI); }
        static UntypedValue* loot_strategy(PlayerbotAI* botAI) { return new LootStrategyValue(botAI); }

        static UntypedValue* attacker_count(PlayerbotAI* botAI) { return new AttackerCountValue(botAI); }
        static UntypedValue* my_attacker_count(PlayerbotAI* botAI) { return new MyAttackerCountValue(botAI); }
        static UntypedValue* has_aggro(PlayerbotAI* botAI) { return new HasAggroValue(botAI); }
        static UntypedValue* mounted(PlayerbotAI* botAI) { return new IsMountedValue(botAI); }
        static UntypedValue* health(PlayerbotAI* botAI) { return new HealthValue(botAI); }
        static UntypedValue* rage(PlayerbotAI* botAI) { return new RageValue(botAI); }
        static UntypedValue* energy(PlayerbotAI* botAI) { return new EnergyValue(botAI); }
        static UntypedValue* mana(PlayerbotAI* botAI) { return new ManaValue(botAI); }
        static UntypedValue* combo(PlayerbotAI* botAI) { return new ComboPointsValue(botAI); }
        static UntypedValue* dead(PlayerbotAI* botAI) { return new IsDeadValue(botAI); }
        static UntypedValue* pet_happy(PlayerbotAI* botAI) { return new PetIsHappyValue(botAI); }
        static UntypedValue* pet_dead(PlayerbotAI* botAI) { return new PetIsDeadValue(botAI); }
        static UntypedValue* has_mana(PlayerbotAI* botAI) { return new HasManaValue(botAI); }
        static UntypedValue* nearest_game_objects(PlayerbotAI* botAI) { return new NearestGameObjects(botAI); }
        static UntypedValue* nearest_game_objects_no_los(PlayerbotAI* botAI) { return new NearestGameObjects(botAI, sPlayerbotAIConfig->sightDistance, true); }
        static UntypedValue* closest_game_objects(PlayerbotAI* botAI) { return new NearestGameObjects(botAI, INTERACTION_DISTANCE); }
        static UntypedValue* log_level(PlayerbotAI* botAI) { return new LogLevelValue(botAI); }
        static UntypedValue* nearest_npcs(PlayerbotAI* botAI) { return new NearestNpcsValue(botAI); }
        static UntypedValue* nearest_friendly_players(PlayerbotAI* botAI) { return new NearestFriendlyPlayersValue(botAI); }
        static UntypedValue* closest_friendly_players(PlayerbotAI* botAI) { return new NearestFriendlyPlayersValue(botAI, INTERACTION_DISTANCE); }
        static UntypedValue* nearest_enemy_players(PlayerbotAI* botAI) { return new NearestEnemyPlayersValue(botAI); }
        static UntypedValue* nearest_corpses(PlayerbotAI* botAI) { return new NearestCorpsesValue(botAI); }
        static UntypedValue* possible_rpg_targets(PlayerbotAI* botAI) { return new PossibleRpgTargetsValue(botAI); }
        static UntypedValue* possible_targets(PlayerbotAI* botAI) { return new PossibleTargetsValue(botAI); }
        static UntypedValue* possible_targets_no_los(PlayerbotAI* botAI) { return new PossibleTargetsValue(botAI, "possible targets", 50.0f, true); }
        static UntypedValue* all_targets(PlayerbotAI* botAI) { return new AllTargetsValue(botAI); }
        static UntypedValue* nearest_adds(PlayerbotAI* botAI) { return new NearestAddsValue(botAI); }
        static UntypedValue* party_member_without_aura(PlayerbotAI* botAI) { return new PartyMemberWithoutAuraValue(botAI); }
        static UntypedValue* attacker_without_aura(PlayerbotAI* botAI) { return new AttackerWithoutAuraTargetValue(botAI); }
        static UntypedValue* party_member_to_heal(PlayerbotAI* botAI) { return new PartyMemberToHeal(botAI); }
        static UntypedValue* party_member_to_resurrect(PlayerbotAI* botAI) { return new PartyMemberToResurrect(botAI); }
        static UntypedValue* party_member_to_dispel(PlayerbotAI* botAI) { return new PartyMemberToDispel(botAI); }
        static UntypedValue* current_target(PlayerbotAI* botAI) { return new CurrentTargetValue(botAI); }
        static UntypedValue* old_target(PlayerbotAI* botAI) { return new CurrentTargetValue(botAI); }
        static UntypedValue* self_target(PlayerbotAI* botAI) { return new SelfTargetValue(botAI); }
        static UntypedValue* master(PlayerbotAI* botAI) { return new MasterTargetValue(botAI); }
        static UntypedValue* line_target(PlayerbotAI* botAI) { return new LineTargetValue(botAI); }
        static UntypedValue* tank_target(PlayerbotAI* botAI) { return new TankTargetValue(botAI); }
        static UntypedValue* dps_target(PlayerbotAI* botAI) { return new DpsTargetValue(botAI); }
        static UntypedValue* dps_aoe_target(PlayerbotAI* botAI) { return new DpsAoeTargetValue(botAI); }
        static UntypedValue* least_hp_target(PlayerbotAI* botAI) { return new LeastHpTargetValue(botAI); }
        static UntypedValue* enemy_player_target(PlayerbotAI* botAI) { return new EnemyPlayerValue(botAI); }
        static UntypedValue* cc_target(PlayerbotAI* botAI) { return new CcTargetValue(botAI); }
        static UntypedValue* current_cc_target(PlayerbotAI* botAI) { return new CurrentCcTargetValue(botAI); }
        static UntypedValue* pet_target(PlayerbotAI* botAI) { return new PetTargetValue(botAI); }
        static UntypedValue* grind_target(PlayerbotAI* botAI) { return new GrindTargetValue(botAI); }
        static UntypedValue* rti_target(PlayerbotAI* botAI) { return new RtiTargetValue(botAI); }
        static UntypedValue* rti_cc_target(PlayerbotAI* botAI) { return new RtiCcTargetValue(botAI); }
        static UntypedValue* duel_target(PlayerbotAI* botAI) { return new DuelTargetValue(botAI); }
        static UntypedValue* has_totem(PlayerbotAI* botAI) { return new HasTotemValue(botAI); }
        static UntypedValue* threat(PlayerbotAI* botAI) { return new ThreatValue(botAI); }
        static UntypedValue* combat(PlayerbotAI* botAI) { return new IsInCombatValue(botAI); }
        static UntypedValue* lfg_proposal(PlayerbotAI* botAI) { return new LfgProposalValue(botAI); }
        static UntypedValue* bag_space(PlayerbotAI* botAI) { return new BagSpaceValue(botAI); }
        static UntypedValue* durability(PlayerbotAI* botAI) { return new DurabilityValue(botAI); }
        static UntypedValue* repair_cost(PlayerbotAI* botAI) { return new RepairCostValue(botAI); }
        static UntypedValue* enemy_healer_target(PlayerbotAI* botAI) { return new EnemyHealerTargetValue(botAI); }
        static UntypedValue* snare_target(PlayerbotAI* botAI) { return new SnareTargetValue(botAI); }
        static UntypedValue* speed(PlayerbotAI* botAI) { return new SpeedValue(botAI); }
        static UntypedValue* last_said(PlayerbotAI* botAI) { return new LastSaidValue(botAI); }
        static UntypedValue* last_emote(PlayerbotAI* botAI) { return new LastEmoteValue(botAI); }
        static UntypedValue* aoe_count(PlayerbotAI* botAI) { return new AoeCountValue(botAI); }
        static UntypedValue* aoe_position(PlayerbotAI* botAI) { return new AoePositionValue(botAI); }
        static UntypedValue* outfit_list_value(PlayerbotAI* botAI) { return new OutfitListValue(botAI); }
        static UntypedValue* random_bot_update_value(PlayerbotAI* botAI) { return new RandomBotUpdateValue(botAI); }
        static UntypedValue* nearest_non_bot_players(PlayerbotAI* botAI) { return new NearestNonBotPlayersValue(botAI); }
        static UntypedValue* skip_spells_list_value(PlayerbotAI* botAI) { return new SkipSpellsListValue(botAI); }
        static UntypedValue* rpg_target(PlayerbotAI* botAI) { return new RpgTargetValue(botAI); }
        static UntypedValue* ignore_rpg_target(PlayerbotAI* botAI) { return new IgnoreRpgTargetValue(botAI); }
        static UntypedValue* travel_target(PlayerbotAI* botAI) { return new TravelTargetValue(botAI); }
        static UntypedValue* talk_target(PlayerbotAI* botAI) { return new TalkTargetValue(botAI); }
        static UntypedValue* pull_target(PlayerbotAI* botAI) { return new PullTargetValue(botAI); }

        static UntypedValue* bg_master(PlayerbotAI* botAI) { return new BgMasterValue(botAI); }
        static UntypedValue* bg_role(PlayerbotAI* botAI) { return new BgRoleValue(botAI); }
        static UntypedValue* arena_type(PlayerbotAI* botAI) { return new ArenaTypeValue(botAI); }
        static UntypedValue* bg_type(PlayerbotAI* botAI) { return new BgTypeValue(botAI); }
        static UntypedValue* team_fc(PlayerbotAI* botAI) { return new FlagCarrierValue(botAI, true, true); }
        static UntypedValue* enemy_fc(PlayerbotAI* botAI) { return new FlagCarrierValue(botAI, false, true); }

        static UntypedValue* last_long_move(PlayerbotAI* botAI) { return new LastLongMoveValue(botAI); }
        static UntypedValue* home_bind(PlayerbotAI* botAI) { return new HomeBindValue(botAI); }

        static UntypedValue* active_quest_givers(PlayerbotAI* botAI) { return new ActiveQuestGiversValue(botAI); }
        static UntypedValue* active_quest_takers(PlayerbotAI* botAI) { return new ActiveQuestTakersValue(botAI); }
        static UntypedValue* active_quest_objectives(PlayerbotAI* botAI) { return new ActiveQuestObjectivesValue(botAI); }
        static UntypedValue* free_quest_log_slots(PlayerbotAI* botAI) { return new FreeQuestLogSlotValue(botAI); }

        static UntypedValue* death_count(PlayerbotAI* botAI) { return new DeathCountValue(botAI); }
};