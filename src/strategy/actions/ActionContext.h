#pragma once

#include "GenericActions.h"
#include "NonCombatActions.h"
#include "EmoteAction.h"
#include "AddLootAction.h"
#include "LootAction.h"
#include "AddLootAction.h"
#include "StayActions.h"
#include "FollowActions.h"
#include "ChangeStrategyAction.h"
#include "ChooseTargetActions.h"
#include "SuggestWhatToDoAction.h"
#include "PositionAction.h"
#include "AttackAction.h"
#include "CheckMailAction.h"
#include "CheckValuesAction.h"
#include "ChooseRpgTargetAction.h"
#include "DelayAction.h"
#include "GiveItemAction.h"
#include "GreetAction.h"
#include "MovementActions.h"
#include "MoveToRpgTargetAction.h"
#include "OutfitAction.h"
#include "RevealGatheringItemAction.h"
#include "SayAction.h"
#include "OutfitAction.h"
#include "RandomBotUpdateAction.h"
#include "RemoveAuraAction.h"
#include "RpgAction.h"
#include "RtiAction.h"

namespace ai
{
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
        static Action* give_water(PlayerbotAI* botAI) { return new GiveWaterAction(botAI); }
        static Action* give_food(PlayerbotAI* botAI) { return new GiveFoodAction(botAI); }
        static Action* ra(PlayerbotAI* botAI) { return new RemoveAuraAction(botAI); }
        static Action* mark_rti(PlayerbotAI* botAI) { return new MarkRtiAction(botAI); }
        static Action* set_return_position(PlayerbotAI* botAI) { return new SetReturnPositionAction(botAI); }
        static Action* rpg(PlayerbotAI* botAI) { return new RpgAction(botAI); }
        static Action* choose_rpg_target(PlayerbotAI* botAI) { return new ChooseRpgTargetAction(botAI); }
        static Action* move_to_rpg_target(PlayerbotAI* botAI) { return new MoveToRpgTargetAction(botAI); }
        static Action* move_out_of_collision(PlayerbotAI* botAI) { return new MoveOutOfCollisionAction(botAI); }
        static Action* check_values(PlayerbotAI* botAI) { return new CheckValuesAction(botAI); }
        static Action* greet(PlayerbotAI* botAI) { return new GreetAction(botAI); }
        static Action* check_mail(PlayerbotAI* botAI) { return new CheckMailAction(botAI); }
        static Action* drop_target(PlayerbotAI* botAI) { return new DropTargetAction(botAI); }
        static Action* attack_duel_opponent(PlayerbotAI* botAI) { return new AttackDuelOpponentAction(botAI); }
        static Action* guard(PlayerbotAI* botAI) { return new GuardAction(botAI); }
        static Action* open_loot(PlayerbotAI* botAI) { return new OpenLootAction(botAI); }
        static Action* move_to_loot(PlayerbotAI* botAI) { return new MoveToLootAction(botAI); }
        static Action* _return(PlayerbotAI* botAI) { return new ReturnAction(botAI); }
        static Action* shoot(PlayerbotAI* botAI) { return new CastShootAction(botAI); }
        static Action* melee(PlayerbotAI* botAI) { return new MeleeAction(botAI); }
        static Action* ReachSpell(PlayerbotAI* botAI) { return new ReachSpellAction(botAI); }
        static Action* ReachMelee(PlayerbotAI* botAI) { return new ReachMeleeAction(botAI); }
        static Action* reach_party_member_to_heal(PlayerbotAI* botAI) { return new ReachPartyMemberToHealAction(botAI); }
        static Action* flee(PlayerbotAI* botAI) { return new FleeAction(botAI); }
        static Action* flee_with_pet(PlayerbotAI* botAI) { return new FleeWithPetAction(botAI); }
        static Action* gift_of_the_naaru(PlayerbotAI* botAI) { return new CastGiftOfTheNaaruAction(botAI); }
        static Action* lifeblood(PlayerbotAI* botAI) { return new CastLifeBloodAction(botAI); }
        static Action* arcane_torrent(PlayerbotAI* botAI) { return new CastArcaneTorrentAction(botAI); }
        static Action* end_pull(PlayerbotAI* botAI) { return new ChangeCombatStrategyAction(ai, "-pull"); }

        static Action* emote(PlayerbotAI* botAI) { return new EmoteAction(botAI); }
        static Action* talk(PlayerbotAI* botAI) { return new TalkAction(botAI); }
        static Action* suggest_what_to_do(PlayerbotAI* botAI) { return new SuggestWhatToDoAction(botAI); }
        static Action* suggest_trade(PlayerbotAI* botAI) { return new SuggestTradeAction(botAI); }
        static Action* attack_anything(PlayerbotAI* botAI) { return new AttackAnythingAction(botAI); }
        static Action* attack_least_hp_target(PlayerbotAI* botAI) { return new AttackLeastHpTargetAction(botAI); }
        static Action* enemy_player_target(PlayerbotAI* botAI) { return new AttackEnemyPlayerAction(botAI); }
        static Action* stay(PlayerbotAI* botAI) { return new StayAction(botAI); }
        static Action* sit(PlayerbotAI* botAI) { return new SitAction(botAI); }
        static Action* runaway(PlayerbotAI* botAI) { return new RunAwayAction(botAI); }
        static Action* follow(PlayerbotAI* botAI) { return new FollowAction(botAI); }
        static Action* add_gathering_loot(PlayerbotAI* botAI) { return new AddGatheringLootAction(botAI); }
        static Action* add_loot(PlayerbotAI* botAI) { return new AddLootAction(botAI); }
        static Action* add_all_loot(PlayerbotAI* botAI) { return new AddAllLootAction(botAI); }
        static Action* loot(PlayerbotAI* botAI) { return new LootAction(botAI); }
        static Action* release_loot(PlayerbotAI* botAI) { return new ReleaseLootAction(botAI); }
        static Action* dps_assist(PlayerbotAI* botAI) { return new DpsAssistAction(botAI); }
        static Action* dps_aoe(PlayerbotAI* botAI) { return new DpsAoeAction(botAI); }
        static Action* attack_rti_target(PlayerbotAI* botAI) { return new AttackRtiTargetAction(botAI); }
        static Action* tank_assist(PlayerbotAI* botAI) { return new TankAssistAction(botAI); }
        static Action* drink(PlayerbotAI* botAI) { return new DrinkAction(botAI); }
        static Action* food(PlayerbotAI* botAI) { return new EatAction(botAI); }
        static Action* mana_potion(PlayerbotAI* botAI) { return new UseManaPotion(botAI); }
        static Action* healing_potion(PlayerbotAI* botAI) { return new UseHealingPotion(botAI); }
        static Action* healthstone(PlayerbotAI* botAI) { return new UseItemAction(ai, "healthstone"); }
        static Action* move_out_of_enemy_contact(PlayerbotAI* botAI) { return new MoveOutOfEnemyContactAction(botAI); }
        static Action* set_facing(PlayerbotAI* botAI) { return new SetFacingTargetAction(botAI); }
        static Action* set_behind(PlayerbotAI* botAI) { return new SetBehindTargetAction(botAI); }
        static Action* say(PlayerbotAI* botAI) { return new SayAction(botAI); }
        static Action* reveal_gathering_item(PlayerbotAI* botAI) { return new RevealGatheringItemAction(botAI); }
        static Action* outfit(PlayerbotAI* botAI) { return new OutfitAction(botAI); }
        static Action* random_bot_update(PlayerbotAI* botAI) { return new RandomBotUpdateAction(botAI); }
        static Action* delay(PlayerbotAI* botAI) { return new DelayAction(botAI); }
    };

};
