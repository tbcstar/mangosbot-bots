/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AddLootAction.h"
#include "AttackAction.h"
#include "AutoLearnSpellAction.h"
#include "BattlegroundTactics.h"
#include "BattlegroundJoinAction.h"
#include "CastCustomSpellAction.h"
#include "ChangeStrategyAction.h"
#include "ChangeTalentsAction.h"
#include "CheckMailAction.h"
#include "CheckValuesAction.h"
#include "ChooseTargetActions.h"
#include "ChooseRpgTargetAction.h"
#include "CombatActions.h"
#include "DelayAction.h"
#include "EmoteAction.h"
#include "GenericActions.h"
#include "GiveItemAction.h"
#include "GreetAction.h"
#include "ImbueAction.h"
#include "InviteToGroupAction.h"
#include "LeaveGroupAction.h"
#include "FollowActions.h"
#include "LootAction.h"
#include "MovementActions.h"
#include "MoveToRpgTargetAction.h"
#include "MoveToTravelTargetAction.h"
#include "NonCombatActions.h"
#include "OutfitAction.h"
#include "PositionAction.h"
#include "RandomBotUpdateAction.h"
#include "ReleaseSpiritAction.h"
#include "RemoveAuraAction.h"
#include "RevealGatheringItemAction.h"
#include "RpgAction.h"
#include "RtiAction.h"
#include "SayAction.h"
#include "StayActions.h"
#include "SuggestWhatToDoAction.h"
#include "TravelAction.h"
#include "XpGainAction.h"
#include "WorldBuffAction.h"

class PlayerbotAI;

class ActionContext : public NamedObjectContext<Action>
{
    public:
        ActionContext()
        {
            creators["mark rti"] = &ActionContext::mark_rti;
            creators["set return position"] = &ActionContext::set_return_position;
            creators["rpg"] = &ActionContext::rpg;
            creators["choose rpg target"] = &ActionContext::choose_rpg_target;
            creators["move to rpg target"] = &ActionContext::move_to_rpg_target;
            creators["travel"] = &ActionContext::travel;
            creators["choose travel target"] = &ActionContext::choose_travel_target;
            creators["move to travel target"] = &ActionContext::move_to_travel_target;
            creators["move out of collision"] = &ActionContext::move_out_of_collision;
            creators["move out of collision"] = &ActionContext::move_out_of_collision;
            creators["move random"] = &ActionContext::move_random;
            creators["attack"] = &ActionContext::melee;
            creators["melee"] = &ActionContext::melee;
            creators["switch to melee"] = &ActionContext::switch_to_melee;
            creators["switch to ranged"] = &ActionContext::switch_to_ranged;
            creators["reach spell"] = &ActionContext::ReachSpell;
            creators["reach melee"] = &ActionContext::ReachMelee;
            creators["reach party member to heal"] = &ActionContext::reach_party_member_to_heal;
            creators["flee"] = &ActionContext::flee;
            creators["flee with pet"] = &ActionContext::flee_with_pet;
            creators["gift of the naaru"] = &ActionContext::gift_of_the_naaru;
            creators["shoot"] = &ActionContext::shoot;
            creators["lifeblood"] = &ActionContext::lifeblood;
            creators["arcane torrent"] = &ActionContext::arcane_torrent;
            creators["end pull"] = &ActionContext::end_pull;
            creators["healthstone"] = &ActionContext::healthstone;
            creators["healing potion"] = &ActionContext::healing_potion;
            creators["mana potion"] = &ActionContext::mana_potion;
            creators["food"] = &ActionContext::food;
            creators["drink"] = &ActionContext::drink;
            creators["tank assist"] = &ActionContext::tank_assist;
            creators["dps assist"] = &ActionContext::dps_assist;
            creators["dps aoe"] = &ActionContext::dps_aoe;
            creators["attack rti target"] = &ActionContext::attack_rti_target;
            creators["loot"] = &ActionContext::loot;
            creators["add loot"] = &ActionContext::add_loot;
            creators["add gathering loot"] = &ActionContext::add_gathering_loot;
            creators["add all loot"] = &ActionContext::add_all_loot;
            creators["release loot"] = &ActionContext::release_loot;
            creators["shoot"] = &ActionContext::shoot;
            creators["follow"] = &ActionContext::follow;
            creators["flee to master"] = &ActionContext::flee_to_master;
            creators["runaway"] = &ActionContext::runaway;
            creators["stay"] = &ActionContext::stay;
            creators["sit"] = &ActionContext::sit;
            creators["attack anything"] = &ActionContext::attack_anything;
            creators["attack least hp target"] = &ActionContext::attack_least_hp_target;
            creators["attack enemy player"] = &ActionContext::attack_enemy_player;
            creators["emote"] = &ActionContext::emote;
            creators["talk"] = &ActionContext::talk;
            creators["suggest what to do"] = &ActionContext::suggest_what_to_do;
            creators["suggest trade"] = &ActionContext::suggest_trade;
            creators["return"] = &ActionContext::_return;
            creators["move to loot"] = &ActionContext::move_to_loot;
            creators["open loot"] = &ActionContext::open_loot;
            creators["guard"] = &ActionContext::guard;
            creators["move out of enemy contact"] = &ActionContext::move_out_of_enemy_contact;
            creators["set facing"] = &ActionContext::set_facing;
            creators["set behind"] = &ActionContext::set_behind;
            creators["attack duel opponent"] = &ActionContext::attack_duel_opponent;
            creators["drop target"] = &ActionContext::drop_target;
            creators["check mail"] = &ActionContext::check_mail;
            creators["say"] = &ActionContext::say;
            creators["reveal gathering item"] = &ActionContext::reveal_gathering_item;
            creators["outfit"] = &ActionContext::outfit;
            creators["random bot update"] = &ActionContext::random_bot_update;
            creators["delay"] = &ActionContext::delay;
            creators["greet"] = &ActionContext::greet;
            creators["check values"] = &ActionContext::check_values;
            creators["ra"] = &ActionContext::ra;
            creators["give food"] = &ActionContext::give_food;
            creators["give water"] = &ActionContext::give_water;
            creators["apply poison"] = &ActionContext::apply_poison;
            creators["apply stone"] = &ActionContext::apply_stone;
            creators["apply oil"] = &ActionContext::apply_oil;
            creators["try emergency"] = &ActionContext::try_emergency;
            creators["mount"] = &ActionContext::mount;
            creators["war stomp"] = &ActionContext::war_stomp;
            creators["auto talents"] = &ActionContext::auto_talents;
            creators["auto learn spell"] = &ActionContext::auto_learn_spell;
            creators["xp gain"] = &ActionContext::xp_gain;
            creators["invite nearby"] = &ActionContext::invite_nearby;
            creators["leave far away"] = &ActionContext::leave_far_away;
            creators["move to dark portal"] = &ActionContext::move_to_dark_portal;
            creators["move from dark portal"] = &ActionContext::move_from_dark_portal;
            creators["use dark portal azeroth"] = &ActionContext::use_dark_portal_azeroth;
            creators["world buff"] = &ActionContext::world_buff;
            creators["hearthstone"] = &ActionContext::hearthstone;
            creators["cast random spell"] = &ActionContext::cast_random_spell;
            creators["free bg join"] = &ActionContext::free_bg_join;
            creators["use random recipe"] = &ActionContext::use_random_recipe;
            creators["craft random item"] = &ActionContext::craft_random_item;

            // BG Tactics
            creators["bg tactics"] = &ActionContext::bg_tactics;
            creators["bg move to start"] = &ActionContext::bg_move_to_start;
            creators["bg move to objective"] = &ActionContext::bg_move_to_objective;
            creators["bg select objective"] = &ActionContext::bg_select_objective;
            creators["bg check objective"] = &ActionContext::bg_check_objective;
            creators["bg attack fc"] = &ActionContext::bg_attack_fc;
            creators["bg protect fc"] = &ActionContext::bg_protect_fc;
            creators["bg use buff"] = &ActionContext::bg_use_buff;
            creators["attack enemy flag carrier"] = &ActionContext::attack_enemy_fc;
            creators["bg check flag"] = &ActionContext::bg_check_flag;
        }

    private:
        static Action* give_water() { return new GiveWaterAction(); }
        static Action* give_food() { return new GiveFoodAction(); }
        static Action* ra() { return new RemoveAuraAction(); }
        static Action* mark_rti() { return new MarkRtiAction(); }
        static Action* set_return_position() { return new SetReturnPositionAction(); }
        static Action* rpg() { return new RpgAction(); }
        static Action* choose_rpg_target() { return new ChooseRpgTargetAction(); }
        static Action* move_to_rpg_target() { return new MoveToRpgTargetAction(); }
        static Action* travel(PlayerbotAI* botAI) { return new TravelAction(botAI); }
        static Action* choose_travel_target(PlayerbotAI* botAI) { return new ChooseTravelTargetAction(botAI); }
        static Action* move_to_travel_target(PlayerbotAI* botAI) { return new MoveToTravelTargetAction(botAI); }
        static Action* move_out_of_collision() { return new MoveOutOfCollisionAction(); }
        static Action* move_random(PlayerbotAI* botAI) { return new MoveRandomAction(botAI); }
        static Action* check_values() { return new CheckValuesAction(); }
        static Action* greet() { return new GreetAction(); }
        static Action* check_mail() { return new CheckMailAction(); }
        static Action* drop_target() { return new DropTargetAction(); }
        static Action* attack_duel_opponent() { return new AttackDuelOpponentAction(); }
        static Action* guard() { return new GuardAction(); }
        static Action* open_loot() { return new OpenLootAction(); }
        static Action* move_to_loot() { return new MoveToLootAction(); }
        static Action* _return() { return new ReturnAction(); }
        static Action* shoot() { return new CastShootAction(); }
        static Action* melee() { return new MeleeAction(); }
        static Action* switch_to_melee(PlayerbotAI* botAI) { return new SwitchToMeleeAction(botAI); }
        static Action* switch_to_ranged(PlayerbotAI* botAI) { return new SwitchToRangedAction(botAI); }
        static Action* ReachSpell() { return new ReachSpellAction(); }
        static Action* ReachMelee() { return new ReachMeleeAction(); }
        static Action* reach_party_member_to_heal() { return new ReachPartyMemberToHealAction(); }
        static Action* flee() { return new FleeAction(); }
        static Action* flee_with_pet() { return new FleeWithPetAction(); }
        static Action* gift_of_the_naaru() { return new CastGiftOfTheNaaruAction(); }
        static Action* lifeblood() { return new CastLifeBloodAction(); }
        static Action* arcane_torrent() { return new CastArcaneTorrentAction(); }
        static Action* mana_tap(PlayerbotAI* botAI) { return new CastManaTapAction(botAI); }
        static Action* end_pull() { return new ChangeCombatStrategyAction("-pull"); }

        static Action* emote() { return new EmoteAction(); }
        static Action* talk() { return new TalkAction(); }
        static Action* suggest_what_to_do() { return new SuggestWhatToDoAction(); }
        static Action* suggest_trade() { return new SuggestTradeAction(); }
        static Action* attack_anything() { return new AttackAnythingAction(); }
        static Action* attack_least_hp_target() { return new AttackLeastHpTargetAction(); }
        static Action* attack_enemy_player() { return new AttackEnemyPlayerAction(); }
        static Action* stay() { return new StayAction(); }
        static Action* sit() { return new SitAction(); }
        static Action* runaway() { return new RunAwayAction(); }
        static Action* follow() { return new FollowAction(); }
        static Action* flee_to_master(PlayerbotAI* botAI) { return new FleeToMasterAction(botAI); }
        static Action* add_gathering_loot() { return new AddGatheringLootAction(); }
        static Action* add_loot() { return new AddLootAction(); }
        static Action* add_all_loot() { return new AddAllLootAction(); }
        static Action* loot() { return new LootAction(); }
        static Action* release_loot() { return new ReleaseLootAction(); }
        static Action* dps_assist() { return new DpsAssistAction(); }
        static Action* dps_aoe() { return new DpsAoeAction(); }
        static Action* attack_rti_target() { return new AttackRtiTargetAction(); }
        static Action* tank_assist() { return new TankAssistAction(); }
        static Action* drink() { return new DrinkAction(); }
        static Action* food() { return new EatAction(); }
        static Action* mana_potion() { return new UseManaPotion(); }
        static Action* healing_potion() { return new UseHealingPotion(); }
        static Action* healthstone() { return new UseItemAction("healthstone"); }
        static Action* move_out_of_enemy_contact() { return new MoveOutOfEnemyContactAction(); }
        static Action* set_facing() { return new SetFacingTargetAction(); }
        static Action* set_behind() { return new SetBehindTargetAction(); }
        static Action* say() { return new SayAction(); }
        static Action* reveal_gathering_item() { return new RevealGatheringItemAction(); }
        static Action* outfit() { return new OutfitAction(); }
        static Action* random_bot_update() { return new RandomBotUpdateAction(); }
        static Action* delay() { return new DelayAction(); }

        static Action* apply_poison(PlayerbotAI* botAI) { return new ImbueWithPoisonAction(botAI); }
        static Action* apply_oil(PlayerbotAI* botAI) { return new ImbueWithOilAction(botAI); }
        static Action* apply_stone(PlayerbotAI* botAI) { return new ImbueWithStoneAction(botAI); }
        static Action* try_emergency(PlayerbotAI* botAI) { return new TryEmergencyAction(botAI); }
        static Action* mount(PlayerbotAI* botAI) { return new CastSpellAction(botAI, "mount"); }
        static Action* war_stomp(PlayerbotAI* botAI) { return new CastWarStompAction(botAI); }
        static Action* auto_talents(PlayerbotAI* botAI) { return new AutoSetTalentsAction(botAI); }
        static Action* auto_learn_spell(PlayerbotAI* botAI) { return new AutoLearnSpellAction(botAI); }
        static Action* xp_gain(PlayerbotAI* botAI) { return new XpGainAction(botAI); }
        static Action* invite_nearby(PlayerbotAI* botAI) { return new InviteNearbyToGroupAction(botAI); }
        static Action* leave_far_away(PlayerbotAI* botAI) { return new LeaveFarAwayAction(botAI); }
        static Action* move_to_dark_portal(PlayerbotAI* botAI) { return new MoveToDarkPortalAction(botAI); }
        static Action* use_dark_portal_azeroth(PlayerbotAI* botAI) { return new DarkPortalAzerothAction(botAI); }
        static Action* move_from_dark_portal(PlayerbotAI* botAI) { return new MoveFromDarkPortalAction(botAI); }
        static Action* world_buff(PlayerbotAI* botAI) { return new WorldBuffAction(botAI); }
        static Action* hearthstone(PlayerbotAI* botAI) { return new UseHearthStone(botAI); }
        static Action* cast_random_spell(PlayerbotAI* botAI) { return new CastRandomSpellAction(botAI); }
        static Action* free_bg_join(PlayerbotAI* botAI) { return new FreeBGJoinAction(botAI); }

        static Action* use_random_recipe(PlayerbotAI* botAI) { return new UseRandomRecipe(botAI); }
        static Action* craft_random_item(PlayerbotAI* botAI) { return new CraftRandomItemAction(botAI); }

        // BG Tactics
        static Action* bg_tactics(PlayerbotAI* botAI) { return new BGTactics(botAI); }
        static Action* bg_move_to_start(PlayerbotAI* botAI) { return new BGTactics(botAI, "move to start"); }
        static Action* bg_move_to_objective(PlayerbotAI* botAI) { return new BGTactics(botAI, "move to objective"); }
        static Action* bg_select_objective(PlayerbotAI* botAI) { return new BGTactics(botAI, "select objective"); }
        static Action* bg_check_objective(PlayerbotAI* botAI) { return new BGTactics(botAI, "check objective"); }
        static Action* bg_attack_fc(PlayerbotAI* botAI) { return new BGTactics(botAI, "attack fc"); }
        static Action* bg_protect_fc(PlayerbotAI* botAI) { return new BGTactics(botAI, "protect fc"); }
        static Action* attack_enemy_fc(PlayerbotAI* botAI) { return new AttackEnemyFlagCarrierAction(botAI); }
        static Action* bg_use_buff(PlayerbotAI* botAI) { return new BGTactics(botAI, "use buff"); }
        static Action* bg_check_flag(PlayerbotAI* botAI) { return new BGTactics(botAI, "check flag"); }
};
