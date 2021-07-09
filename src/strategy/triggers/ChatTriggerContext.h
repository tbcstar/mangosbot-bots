/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "ChatCommandTrigger.h"
#include "NamedObjectContext.h"

class PlayerbotAI;

class ChatTriggerContext : public NamedObjectContext<Trigger>
{
    public:
        ChatTriggerContext()
        {
            creators["quests"] = &ChatTriggerContext::quests;
            creators["stats"] = &ChatTriggerContext::stats;
            creators["leave"] = &ChatTriggerContext::leave;
            creators["rep"] = &ChatTriggerContext::reputation;
            creators["reputation"] = &ChatTriggerContext::reputation;
            creators["log"] = &ChatTriggerContext::log;
            creators["los"] = &ChatTriggerContext::los;
            creators["drop"] = &ChatTriggerContext::drop;
            creators["share"] = &ChatTriggerContext::share;
            creators["q"] = &ChatTriggerContext::q;
            creators["ll"] = &ChatTriggerContext::ll;
            creators["ss"] = &ChatTriggerContext::ss;
            creators["loot all"] = &ChatTriggerContext::loot_all;
            creators["add all loot"] = &ChatTriggerContext::loot_all;
            creators["release"] = &ChatTriggerContext::release;
            creators["teleport"] = &ChatTriggerContext::teleport;
            creators["taxi"] = &ChatTriggerContext::taxi;
            creators["repair"] = &ChatTriggerContext::repair;
            creators["u"] = &ChatTriggerContext::use;
            creators["use"] = &ChatTriggerContext::use;
            creators["c"] = &ChatTriggerContext::item_count;
            creators["items"] = &ChatTriggerContext::item_count;
            creators["inventory"] = &ChatTriggerContext::item_count;
            creators["inv"] = &ChatTriggerContext::item_count;
            creators["e"] = &ChatTriggerContext::equip;
            creators["equip"] = &ChatTriggerContext::equip;
            creators["ue"] = &ChatTriggerContext::uneqip;
            creators["s"] = &ChatTriggerContext::sell;
            creators["b"] = &ChatTriggerContext::buy;
            creators["r"] = &ChatTriggerContext::reward;
            creators["t"] = &ChatTriggerContext::trade;
            creators["nt"] = &ChatTriggerContext::nontrade;
            creators["talents"] = &ChatTriggerContext::talents;
            creators["spells"] = &ChatTriggerContext::spells;
            creators["co"] = &ChatTriggerContext::co;
            creators["nc"] = &ChatTriggerContext::nc;
            creators["de"] = &ChatTriggerContext::dead;
            creators["trainer"] = &ChatTriggerContext::trainer;
            creators["attack"] = &ChatTriggerContext::attack;
            creators["chat"] = &ChatTriggerContext::chat;
            creators["accept"] = &ChatTriggerContext::accept;
            creators["home"] = &ChatTriggerContext::home;
            creators["reset botAI"] = &ChatTriggerContext::reset_ai;
            creators["destroy"] = &ChatTriggerContext::destroy;
            creators["emote"] = &ChatTriggerContext::emote;
            creators["buff"] = &ChatTriggerContext::buff;
            creators["help"] = &ChatTriggerContext::help;
            creators["gb"] = &ChatTriggerContext::gb;
            creators["bank"] = &ChatTriggerContext::bank;
            creators["follow"] = &ChatTriggerContext::follow;
            creators["stay"] = &ChatTriggerContext::stay;
            creators["flee"] = &ChatTriggerContext::flee;
            creators["grind"] = &ChatTriggerContext::grind;
            creators["tank attack"] = &ChatTriggerContext::tank_attack;
            creators["talk"] = &ChatTriggerContext::talk;
            creators["cast"] = &ChatTriggerContext::cast;
            creators["castnc"] = &ChatTriggerContext::castnc;
            creators["invite"] = &ChatTriggerContext::invite;
            creators["spell"] = &ChatTriggerContext::spell;
            creators["rti"] = &ChatTriggerContext::rti;
            creators["revive"] = &ChatTriggerContext::revive;
            creators["runaway"] = &ChatTriggerContext::runaway;
            creators["warning"] = &ChatTriggerContext::warning;
            creators["position"] = &ChatTriggerContext::position;
            creators["summon"] = &ChatTriggerContext::summon;
            creators["who"] = &ChatTriggerContext::who;
            creators["save mana"] = &ChatTriggerContext::save_mana;
            creators["max dps"] = &ChatTriggerContext::max_dps;
            creators["attackers"] = &ChatTriggerContext::attackers;
            creators["formation"] = &ChatTriggerContext::formation;
            creators["stance"] = &ChatTriggerContext::stance;
            creators["sendmail"] = &ChatTriggerContext::sendmail;
            creators["mail"] = &ChatTriggerContext::mail;
            creators["outfit"] = &ChatTriggerContext::outfit;
            creators["go"] = &ChatTriggerContext::go;
            creators["ready"] = &ChatTriggerContext::ready_check;
            creators["debug"] = &ChatTriggerContext::debug;
            creators["cdebug"] = &ChatTriggerContext::cdebug;
            creators["cs"] = &ChatTriggerContext::cs;
            creators["wts"] = &ChatTriggerContext::wts;
            creators["hire"] = &ChatTriggerContext::hire;
            creators["craft"] = &ChatTriggerContext::craft;
            creators["flag"] = &ChatTriggerContext::craft;
            creators["range"] = &ChatTriggerContext::range;
            creators["ra"] = &ChatTriggerContext::ra;
        }

    private:
        static Trigger* ra(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "ra"); }
        static Trigger* range(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "range"); }
        static Trigger* flag(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "flag"); }
        static Trigger* craft(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "craft"); }
        static Trigger* hire(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "hire"); }
        static Trigger* wts(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "wts"); }
        static Trigger* cs(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "cs"); }
        static Trigger* debug(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "debug"); }
        static Trigger* cdebug(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "cdebug"); }
        static Trigger* go(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "go"); }
        static Trigger* outfit(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "outfit"); }
        static Trigger* mail(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "mail"); }
        static Trigger* sendmail(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "sendmail"); }
        static Trigger* formation(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "formation"); }
        static Trigger* stance(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "stance"); }
        static Trigger* attackers(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "attackers"); }
        static Trigger* max_dps(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "max dps"); }
        static Trigger* save_mana(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "save mana"); }
        static Trigger* who(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "who"); }
        static Trigger* summon(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "summon"); }
        static Trigger* position(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "position"); }
        static Trigger* runaway(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "runaway"); }
        static Trigger* warning(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "warning"); }
        static Trigger* revive(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "revive"); }
        static Trigger* rti(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "rti"); }
        static Trigger* invite(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "invite"); }
        static Trigger* cast(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "cast"); }
        static Trigger* castnc(PlayerbotAI* ai) { return new ChatCommandTrigger(ai, "castnc"); }
        static Trigger* talk(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "talk"); }
        static Trigger* flee(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "flee"); }
        static Trigger* grind(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "grind"); }
        static Trigger* tank_attack(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "tank attack"); }
        static Trigger* stay(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "stay"); }
        static Trigger* follow(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "follow"); }
        static Trigger* gb(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "gb"); }
        static Trigger* bank(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "bank"); }
        static Trigger* help(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "help"); }
        static Trigger* buff(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "buff"); }
        static Trigger* emote(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "emote"); }
        static Trigger* destroy(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "destroy"); }
        static Trigger* home(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "home"); }
        static Trigger* accept(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "accept"); }
        static Trigger* chat(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "chat"); }
        static Trigger* attack(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "attack"); }
        static Trigger* trainer(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "trainer"); }
        static Trigger* co(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "co"); }
        static Trigger* nc(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "nc"); }
        static Trigger* dead(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "de"); }
        static Trigger* spells(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "spells"); }
        static Trigger* talents(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "talents"); }
        static Trigger* equip(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "e"); }
        static Trigger* uneqip(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "ue"); }
        static Trigger* sell(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "s"); }
        static Trigger* buy(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "b"); }
        static Trigger* reward(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "r"); }
        static Trigger* trade(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "t"); }
        static Trigger* nontrade(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "nt"); }
        static Trigger* item_count(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "c"); }
        static Trigger* use(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "use"); }
        static Trigger* repair(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "repair"); }
        static Trigger* taxi(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "taxi"); }
        static Trigger* teleport(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "teleport"); }
        static Trigger* q(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "q"); }
        static Trigger* ll(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "ll"); }
        static Trigger* ss(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "ss"); }
        static Trigger* drop(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "drop"); }
        static Trigger* share(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "share"); }
        static Trigger* quests(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "quests"); }
        static Trigger* stats(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "stats"); }
        static Trigger* leave(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "leave"); }
        static Trigger* reputation(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "reputation"); }
        static Trigger* log(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "log"); }
        static Trigger* los(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "los"); }
        static Trigger* loot_all(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "add all loot"); }
        static Trigger* release(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "release"); }
        static Trigger* reset_ai(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "reset botAI"); }
        static Trigger* spell(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "spell"); }
        static Trigger* ready_check(PlayerbotAI* botAI) { return new ChatCommandTrigger(botAI, "ready check"); }
};
