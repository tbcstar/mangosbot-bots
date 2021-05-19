/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AddLootAction.h"
#include "AttackAction.h"
#include "ChangeStrategyAction.h"
#include "CheckMailAction.h"
#include "CheckValuesAction.h"
#include "ChooseTargetActions.h"
#include "ChooseRpgTargetAction.h"
#include "DelayAction.h"
#include "EmoteAction.h"
#include "GenericActions.h"
#include "GiveItemAction.h"
#include "GreetAction.h"
#include "FollowActions.h"
#include "LootAction.h"
#include "MovementActions.h"
#include "MoveToRpgTargetAction.h"
#include "NonCombatActions.h"
#include "OutfitAction.h"
#include "PositionAction.h"
#include "RandomBotUpdateAction.h"
#include "RemoveAuraAction.h"
#include "RevealGatheringItemAction.h"
#include "RpgAction.h"
#include "RtiAction.h"
#include "SayAction.h"
#include "StayActions.h"
#include "SuggestWhatToDoAction.h"

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
            creators["move out of collision"] = &ActionContext::move_out_of_collision;
            creators["attack"] = &ActionContext::melee;
            creators["melee"] = &ActionContext::melee;
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
            creators["follow"] = &ActionContext::follow;
            creators["runaway"] = &ActionContext::runaway;
            creators["stay"] = &ActionContext::stay;
            creators["sit"] = &ActionContext::sit;
            creators["attack anything"] = &ActionContext::attack_anything;
            creators["attack least hp target"] = &ActionContext::attack_least_hp_target;
            creators["attack enemy player"] = &ActionContext::enemy_player_target;
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
        static Action* move_out_of_collision() { return new MoveOutOfCollisionAction(); }
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
        static Action* ReachSpell() { return new ReachSpellAction(); }
        static Action* ReachMelee() { return new ReachMeleeAction(); }
        static Action* reach_party_member_to_heal() { return new ReachPartyMemberToHealAction(); }
        static Action* flee() { return new FleeAction(); }
        static Action* flee_with_pet() { return new FleeWithPetAction(); }
        static Action* gift_of_the_naaru() { return new CastGiftOfTheNaaruAction(); }
        static Action* lifeblood() { return new CastLifeBloodAction(); }
        static Action* arcane_torrent() { return new CastArcaneTorrentAction(); }
        static Action* end_pull() { return new ChangeCombatStrategyAction("-pull"); }

        static Action* emote() { return new EmoteAction(); }
        static Action* talk() { return new TalkAction(); }
        static Action* suggest_what_to_do() { return new SuggestWhatToDoAction(); }
        static Action* suggest_trade() { return new SuggestTradeAction(); }
        static Action* attack_anything() { return new AttackAnythingAction(); }
        static Action* attack_least_hp_target() { return new AttackLeastHpTargetAction(); }
        static Action* enemy_player_target() { return new AttackEnemyPlayerAction(); }
        static Action* stay() { return new StayAction(); }
        static Action* sit() { return new SitAction(); }
        static Action* runaway() { return new RunAwayAction(); }
        static Action* follow() { return new FollowAction(); }
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
};
