/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AddLootAction.h"
#include "AttackAction.h"
#include "BankAction.h"
#include "BuffAction.h"
#include "BuyAction.h"
#include "CastCustomSpellAction.h"
#include "ChangeChatAction.h"
#include "ChangeTalentsAction.h"
#include "ChangeStrategyAction.h"
#include "ChatShortcutActions.h"
#include "CustomStrategyEditAction.h"
#include "DebugAction.h"
#include "DestroyItemAction.h"
#include "DropQuestAction.h"
#include "EquipAction.h"
#include "FlagAction.h"
#include "GoAction.h"
#include "GossipHelloAction.h"
#include "GuildBankAction.h"
#include "HelpAction.h"
#include "HireAction.h"
#include "InviteToGroupAction.h"
#include "LeaveGroupAction.h"
#include "ListQuestsActions.h"
#include "ListSpellsAction.h"
#include "LogLevelAction.h"
#include "LootStrategyAction.h"
#include "MailAction.h"
#include "QueryItemUsageAction.h"
#include "QueryQuestAction.h"
#include "PositionAction.h"
#include "RangeAction.h"
#include "ReleaseSpiritAction.h"
#include "RepairAllAction.h"
#include "ResetAiAction.h"
#include "ReviveFromCorpseAction.h"
#include "RewardAction.h"
#include "RtiAction.h"
#include "SaveManaAction.h"
#include "SellAction.h"
#include "SetCraftAction.h"
#include "SendMailAction.h"
#include "SetHomeAction.h"
#include "ShareQuestAction.h"
#include "SkipSpellsListAction.h"
#include "StatsAction.h"
#include "TaxiAction.h"
#include "TeleportAction.h"
#include "TellCastFailedAction.h"
#include "TellItemCountAction.h"
#include "TellLosAction.h"
#include "TellReputationAction.h"
#include "TellTargetAction.h"
#include "TradeAction.h"
#include "TrainerAction.h"
#include "UnequipAction.h"
#include "UseItemAction.h"
#include "UseMeetingStoneAction.h"
#include "WhoAction.h"
#include "WtsAction.h"
#include "../NamedObjectContext.h"
#include "../values/Formations.h"
#include "../values/Stances.h"

class ChatActionContext : public NamedObjectContext<Action>
{
    public:
        ChatActionContext()
        {
            creators["range"] = &ChatActionContext::range;
            creators["stats"] = &ChatActionContext::stats;
            creators["quests"] = &ChatActionContext::quests;
            creators["leave"] = &ChatActionContext::leave;
            creators["reputation"] = &ChatActionContext::reputation;
            creators["log"] = &ChatActionContext::log;
            creators["los"] = &ChatActionContext::los;
            creators["drop"] = &ChatActionContext::drop;
            creators["share"] = &ChatActionContext::share;
            creators["query quest"] = &ChatActionContext::query_quest;
            creators["query item usage"] = &ChatActionContext::query_item_usage;
            creators["ll"] = &ChatActionContext::ll;
            creators["ss"] = &ChatActionContext::ss;
            creators["add all loot"] = &ChatActionContext::add_all_loot;
            creators["release"] = &ChatActionContext::release;
            creators["teleport"] = &ChatActionContext::teleport;
            creators["taxi"] = &ChatActionContext::taxi;
            creators["repair"] = &ChatActionContext::repair;
            creators["use"] = &ChatActionContext::use;
            creators["item count"] = &ChatActionContext::item_count;
            creators["equip"] = &ChatActionContext::equip;
            creators["unequip"] = &ChatActionContext::unequip;
            creators["sell"] = &ChatActionContext::sell;
            creators["buy"] = &ChatActionContext::buy;
            creators["reward"] = &ChatActionContext::reward;
            creators["trade"] = &ChatActionContext::trade;
            creators["talents"] = &ChatActionContext::talents;
            creators["spells"] = &ChatActionContext::spells;
            creators["co"] = &ChatActionContext::co;
            creators["nc"] = &ChatActionContext::nc;
            creators["dead"] = &ChatActionContext::dead;
            creators["trainer"] = &ChatActionContext::trainer;
            creators["attack my target"] = &ChatActionContext::attack_my_target;
            creators["chat"] = &ChatActionContext::chat;
            creators["home"] = &ChatActionContext::home;
            creators["destroy"] = &ChatActionContext::destroy;
            creators["reset ai"] = &ChatActionContext::reset_ai;
            creators["buff"] = &ChatActionContext::buff;
            creators["help"] = &ChatActionContext::help;
            creators["gb"] = &ChatActionContext::gb;
            creators["bank"] = &ChatActionContext::bank;
            creators["follow chat shortcut"] = &ChatActionContext::follow_chat_shortcut;
            creators["stay chat shortcut"] = &ChatActionContext::stay_chat_shortcut;
            creators["flee chat shortcut"] = &ChatActionContext::flee_chat_shortcut;
            creators["runaway chat shortcut"] = &ChatActionContext::runaway_chat_shortcut;
            creators["grind chat shortcut"] = &ChatActionContext::grind_chat_shortcut;
            creators["tank attack chat shortcut"] = &ChatActionContext::tank_attack_chat_shortcut;
            creators["gossip hello"] = &ChatActionContext::gossip_hello;
            creators["cast custom spell"] = &ChatActionContext::cast_custom_spell;
            creators["invite"] = &ChatActionContext::invite;
            creators["spell"] = &ChatActionContext::spell;
            creators["rti"] = &ChatActionContext::rti;
            creators["spirit healer"] = &ChatActionContext::spirit_healer;
            creators["position"] = &ChatActionContext::position;
            creators["tell target"] = &ChatActionContext::tell_target;
            creators["summon"] = &ChatActionContext::summon;
            creators["who"] = &ChatActionContext::who;
            creators["save mana"] = &ChatActionContext::save_mana;
            creators["max dps chat shortcut"] = &ChatActionContext::max_dps_chat_shortcut;
            creators["tell attackers"] = &ChatActionContext::tell_attackers;
            creators["formation"] = &ChatActionContext::formation;
            creators["stance"] = &ChatActionContext::stance;
            creators["sendmail"] = &ChatActionContext::sendmail;
            creators["mail"] = &ChatActionContext::mail;
            creators["go"] = &ChatActionContext::go;
            creators["debug"] = &ChatActionContext::debug;
            creators["cs"] = &ChatActionContext::cs;
            creators["wts"] = &ChatActionContext::wts;
            creators["hire"] = &ChatActionContext::hire;
            creators["craft"] = &ChatActionContext::craft;
            creators["flag"] = &ChatActionContext::flag;
        }

    private:
        static Action* range() { return new RangeAction(); }
        static Action* flag() { return new FlagAction(); }
        static Action* craft() { return new SetCraftAction(); }
        static Action* hire() { return new HireAction(); }
        static Action* wts() { return new WtsAction(); }
        static Action* cs() { return new CustomStrategyEditAction(); }
        static Action* debug() { return new DebugAction(); }
        static Action* mail() { return new MailAction(); }
        static Action* go() { return new GoAction(); }
        static Action* sendmail() { return new SendMailAction(); }
        static Action* formation() { return new SetFormationAction(); }
        static Action* stance() { return new SetStanceAction(); }
        static Action* tell_attackers() { return new TellAttackersAction(); }
        static Action* max_dps_chat_shortcut() { return new MaxDpsChatShortcutAction(); }
        static Action* save_mana() { return new SaveManaAction(); }
        static Action* who() { return new WhoAction(); }
        static Action* summon() { return new SummonAction(); }
        static Action* tell_target() { return new TellTargetAction(); }
        static Action* position() { return new PositionAction(); }
        static Action* spirit_healer() { return new SpiritHealerAction(); }
        static Action* rti() { return new RtiAction(); }
        static Action* invite() { return new InviteToGroupAction(); }
        static Action* spell() { return new TellSpellAction(); }
        static Action* cast_custom_spell() { return new CastCustomSpellAction(); }
        static Action* tank_attack_chat_shortcut() { return new TankAttackChatShortcutAction(); }
        static Action* grind_chat_shortcut() { return new GrindChatShortcutAction(); }
        static Action* flee_chat_shortcut() { return new FleeChatShortcutAction(); }
        static Action* runaway_chat_shortcut() { return new GoawayChatShortcutAction(); }
        static Action* stay_chat_shortcut() { return new StayChatShortcutAction(); }
        static Action* follow_chat_shortcut() { return new FollowChatShortcutAction(); }
        static Action* gb() { return new GuildBankAction(); }
        static Action* bank() { return new BankAction(); }
        static Action* help() { return new HelpAction(); }
        static Action* buff() { return new BuffAction(); }
        static Action* destroy() { return new DestroyItemAction(); }
        static Action* home() { return new SetHomeAction(); }
        static Action* chat() { return new ChangeChatAction(); }
        static Action* attack_my_target() { return new AttackMyTargetAction(); }
        static Action* trainer() { return new TrainerAction(); }
        static Action* co() { return new ChangeCombatStrategyAction(); }
        static Action* nc() { return new ChangeNonCombatStrategyAction(); }
        static Action* dead() { return new ChangeDeadStrategyAction(); }
        static Action* spells() { return new ListSpellsAction(); }
        static Action* talents() { return new ChangeTalentsAction(); }

        static Action* equip() { return new EquipAction(); }
        static Action* unequip() { return new UnequipAction(); }
        static Action* sell() { return new SellAction(); }
        static Action* buy() { return new BuyAction(); }
        static Action* reward() { return new RewardAction(); }
        static Action* trade() { return new TradeAction(); }

        static Action* item_count() { return new TellItemCountAction(); }
        static Action* use() { return new UseItemAction(); }
        static Action* repair() { return new RepairAllAction(); }
        static Action* taxi() { return new TaxiAction(); }
        static Action* teleport() { return new TeleportAction(); }
        static Action* release() { return new ReleaseSpiritAction(); }
        static Action* query_item_usage() { return new QueryItemUsageAction(); }
        static Action* query_quest() { return new QueryQuestAction(); }
        static Action* drop() { return new DropQuestAction(); }
        static Action* share() { return new ShareQuestAction(); }
        static Action* stats() { return new StatsAction(); }
        static Action* quests() { return new ListQuestsAction(); }
        static Action* leave() { return new LeaveGroupAction(); }
        static Action* reputation() { return new TellReputationAction(); }
        static Action* log() { return new LogLevelAction(); }
        static Action* los() { return new TellLosAction(); }
        static Action* ll() { return new LootStrategyAction(); }
        static Action* ss() { return new SkipSpellsListAction(); }
        static Action* add_all_loot() { return new AddAllLootAction(); }
        static Action* reset_ai() { return new ResetAiAction(); }
        static Action* gossip_hello() { return new GossipHelloAction(); }
};
