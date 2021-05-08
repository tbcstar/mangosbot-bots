#pragma once

#include "ChatCommandTrigger.h"

namespace ai
{
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
            creators["e"] = &ChatTriggerContext::equip;
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
            creators["dead"] = &ChatTriggerContext::dead;
            creators["trainer"] = &ChatTriggerContext::trainer;
            creators["attack"] = &ChatTriggerContext::attack;
            creators["chat"] = &ChatTriggerContext::chat;
            creators["accept"] = &ChatTriggerContext::accept;
            creators["home"] = &ChatTriggerContext::home;
            creators["reset ai"] = &ChatTriggerContext::reset_ai;
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
            creators["cs"] = &ChatTriggerContext::cs;
            creators["wts"] = &ChatTriggerContext::wts;
            creators["hire"] = &ChatTriggerContext::hire;
            creators["craft"] = &ChatTriggerContext::craft;
            creators["flag"] = &ChatTriggerContext::craft;
            creators["range"] = &ChatTriggerContext::range;
            creators["ra"] = &ChatTriggerContext::ra;
        }

    private:
        static Trigger* ra(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "ra"); }
        static Trigger* range(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "range"); }
        static Trigger* flag(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "flag"); }
        static Trigger* craft(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "craft"); }
        static Trigger* hire(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "hire"); }
        static Trigger* wts(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "wts"); }
        static Trigger* cs(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "cs"); }
        static Trigger* debug(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "debug"); }
        static Trigger* go(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "go"); }
        static Trigger* outfit(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "outfit"); }
        static Trigger* mail(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "mail"); }
        static Trigger* sendmail(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "sendmail"); }
        static Trigger* formation(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "formation"); }
        static Trigger* stance(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "stance"); }
        static Trigger* attackers(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "attackers"); }
        static Trigger* max_dps(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "max dps"); }
        static Trigger* save_mana(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "save mana"); }
        static Trigger* who(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "who"); }
        static Trigger* summon(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "summon"); }
        static Trigger* position(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "position"); }
        static Trigger* runaway(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "runaway"); }
        static Trigger* warning(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "warning"); }
        static Trigger* revive(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "revive"); }
        static Trigger* rti(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "rti"); }
        static Trigger* invite(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "invite"); }
        static Trigger* cast(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "cast"); }
        static Trigger* talk(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "talk"); }
        static Trigger* flee(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "flee"); }
        static Trigger* grind(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "grind"); }
        static Trigger* tank_attack(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "tank attack"); }
        static Trigger* stay(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "stay"); }
        static Trigger* follow(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "follow"); }
        static Trigger* gb(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "gb"); }
        static Trigger* bank(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "bank"); }
        static Trigger* help(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "help"); }
        static Trigger* buff(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "buff"); }
        static Trigger* emote(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "emote"); }
        static Trigger* destroy(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "destroy"); }
        static Trigger* home(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "home"); }
        static Trigger* accept(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "accept"); }
        static Trigger* chat(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "chat"); }
        static Trigger* attack(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "attack"); }
        static Trigger* trainer(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "trainer"); }
        static Trigger* co(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "co"); }
        static Trigger* nc(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "nc"); }
        static Trigger* dead(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "dead"); }
        static Trigger* spells(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "spells"); }
        static Trigger* talents(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "talents"); }
        static Trigger* equip(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "e"); }
        static Trigger* uneqip(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "ue"); }
        static Trigger* sell(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "s"); }
        static Trigger* buy(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "b"); }
        static Trigger* reward(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "r"); }
        static Trigger* trade(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "t"); }
        static Trigger* nontrade(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "nt"); }

        static Trigger* item_count(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "c"); }
        static Trigger* use(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "use"); }
        static Trigger* repair(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "repair"); }
        static Trigger* taxi(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "taxi"); }
        static Trigger* teleport(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "teleport"); }
        static Trigger* q(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "q"); }
        static Trigger* ll(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "ll"); }
        static Trigger* ss(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "ss"); }
        static Trigger* drop(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "drop"); }
        static Trigger* share(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "share"); }
        static Trigger* quests(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "quests"); }
        static Trigger* stats(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "stats"); }
        static Trigger* leave(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "leave"); }
        static Trigger* reputation(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "reputation"); }
        static Trigger* log(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "log"); }
        static Trigger* los(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "los"); }
        static Trigger* loot_all(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "add all loot"); }
        static Trigger* release(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "release"); }
        static Trigger* reset_ai(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "reset ai"); }
        static Trigger* spell(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "spell"); }
        static Trigger* ready_check(PlayerbotAI* botAI) { return new ChatCommandTrigger(ai, "ready check"); }
    };
};
