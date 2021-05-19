/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Chat.h"
#include "Common.h"
#include "PlayerbotAIBase.h"
#include "WorldPacket.h"
#include <stack>

class AiObjectContext;
class ChatHelper;
class CompositeChatFilter;
class Creature;
class Engine;
class ExternalEventHelper;
class Gameobject;
class Item;
class ObjectGuid;
class Player;
class PlayerbotMgr;
class PlayerbotSecurity;
class Spell;
class SpellInfo;
class Unit;

enum PlayerbotSecurityLevel : uint32;
enum StrategyType : uint32;

enum BotState
{
    BOT_STATE_COMBAT        = 0,
    BOT_STATE_NON_COMBAT    = 1,
    BOT_STATE_DEAD          = 2,

    BOT_STATE_MAX
};

bool IsAlliance(uint8 race);

class PlayerbotChatHandler: protected ChatHandler
{
    public:
        explicit PlayerbotChatHandler(Player* pMasterPlayer);
        void sysmessage(std::string str) { SendSysMessage(str.c_str()); }
        uint32 extractQuestId(std::string str);
        uint32 extractSpellId(std::string str)
        {
            char* source = (char*)str.c_str();
            return extractSpellIdFromLink(source);
        }
};

class MinValueCalculator
{
	public:
        MinValueCalculator(float def = 0.0f) : param(nullptr), minValue(def) { }

		void probe(float value, void* p)
        {
			if (!param || minValue >= value)
            {
				minValue = value;
				param = p;
			}
		}

		void* param;
		float minValue;
};

class PacketHandlingHelper
{
    public:
        void AddHandler(uint16 opcode, string handler);
        void Handle(ExternalEventHelper &helper);
        void AddPacket(WorldPacket const& packet);

    private:
        std::map<uint16, std::string> handlers;
        std::stack<WorldPacket> queue;
};

class ChatCommandHolder
{
    public:
        ChatCommandHolder(std::string command, Player* owner = nullptr, uint32 type = CHAT_MSG_WHISPER, time_t time = 0) : command(command), owner(owner), type(type), time(time) { }
        ChatCommandHolder(ChatCommandHolder const& other) : command(other.command), owner(other.owner), type(other.type), time(other.time) { }

        std::string GetCommand() { return command; }
        Player* GetOwner() { return owner; }
        uint32 GetType() { return type; }
        time_t GetTime() { return time; }

    private:
        std::string command;
        Player* owner;
        uint32 type;
        time_t time;
};

class PlayerbotAI : public PlayerbotAIBase
{
    public:
	    PlayerbotAI();
	    PlayerbotAI(Player* bot);
	    virtual ~PlayerbotAI();

	    virtual void UpdateAIInternal(uint32 elapsed);
        std::string HandleRemoteCommand(std::string command);
        void HandleCommand(uint32 type, string const& text, Player* fromPlayer);
	    void HandleBotOutgoingPacket(WorldPacket const& packet);
        void HandleMasterIncomingPacket(WorldPacket const& packet);
        void HandleMasterOutgoingPacket(WorldPacket const& packet);
	    void HandleTeleportAck();
        void ChangeEngine(BotState type);
        void DoNextAction();
        void DoSpecificAction(std::string name);
        void ChangeStrategy(std::string name, BotState type);
        void ClearStrategies(BotState type);
        std::vector<string> GetStrategies(BotState type);
        bool ContainsStrategy(StrategyType type);
        bool HasStrategy(std::string name, BotState type);
        void ResetStrategies(bool load = true);
        void ReInitCurrentEngine();
        void Reset();
        bool IsTank(Player* player);
        bool IsHeal(Player* player);
        bool IsRanged(Player* player);
        Creature* GetCreature(ObjectGuid guid);
        Unit* GetUnit(ObjectGuid guid);
        GameObject* GetGameObject(ObjectGuid guid);
        bool TellMaster(std::ostringstream& stream, PlayerbotSecurityLevel securityLevel = PLAYERBOT_SECURITY_ALLOW_ALL);
        bool TellMaster(std::string text, PlayerbotSecurityLevel securityLevel = PLAYERBOT_SECURITY_ALLOW_ALL);
        bool TellMasterNoFacing(std::string text, PlayerbotSecurityLevel securityLevel = PLAYERBOT_SECURITY_ALLOW_ALL);
        bool TellError(std::string text, PlayerbotSecurityLevel securityLevel = PLAYERBOT_SECURITY_ALLOW_ALL);
        void SpellInterrupted(uint32 spellid);
        int32 CalculateGlobalCooldown(uint32 spellid);
        void InterruptSpell();
        void RemoveAura(std::string name);
        void RemoveShapeshift();
        void WaitForSpellCast(Spell* spell);
        bool PlaySound(uint32 emote);
        void Ping(float x, float y);

        virtual bool CanCastSpell(std::string name, Unit* target, Item* itemTarget = nullptr);
        virtual bool CastSpell(std::string name, Unit* target, Item* itemTarget = nullptr);
        virtual bool HasAura(std::string spellName, Unit* player, bool maxStack = false);
        virtual bool HasAnyAuraOf(Unit* player, ...);

        virtual bool IsInterruptableSpellCasting(Unit* player, std::string spell);
        virtual bool HasAuraToDispel(Unit* player, uint32 dispelType);
        bool CanCastSpell(uint32 spellid, Unit* target, bool checkHasSpell = true, Item* itemTarget = nullptr);

        bool HasAura(uint32 spellId, Unit const* player);
        bool CastSpell(uint32 spellId, Unit* target, Item* itemTarget = nullptr);
        bool canDispel(SpellInfo const* spellInfo, uint32 dispelType);

        uint32 GetEquipGearScore(Player* player, bool withBags, bool withBank);
        bool HasSkill(SkillType skill);
        bool IsAllowedCommand(std::string text);
        float GetRange(std::string type);

        Player* GetBot() { return bot; }
        Player* GetMaster() { return master; }
        void SetMaster(Player* master) { master = master; }
        AiObjectContext* GetAiObjectContext() { return aiObjectContext; }
        ChatHelper* GetChatHelper() { return &chatHelper; }
        bool IsOpposing(Player* player);
        static bool IsOpposing(uint8 race1, uint8 race2);
        PlayerbotSecurity* GetSecurity() { return &security; }

    private:
        void _fillGearScoreData(Player* player, Item* item, std::vector<uint32>* gearScore, uint32& twoHandScore);
        bool IsTellAllowed(PlayerbotSecurityLevel securityLevel = PLAYERBOT_SECURITY_ALLOW_ALL);

    protected:
	    Player* bot;
	    Player* master;
	    uint32 accountId;
        AiObjectContext* aiObjectContext;
        Engine* currentEngine;
        Engine* engines[BOT_STATE_MAX];
        BotState currentState;
        ChatHelper chatHelper;
        std::queue<ChatCommandHolder> chatCommands;
        PacketHandlingHelper botOutgoingPacketHandlers;
        PacketHandlingHelper masterIncomingPacketHandlers;
        PacketHandlingHelper masterOutgoingPacketHandlers;
        CompositeChatFilter chatFilter;
        PlayerbotSecurity security;
        std::map<std::string, time_t> whispers;
        std::pair<ChatMsg, time_t> currentChat;
        static std::set<std::string> unsecuredCommands;
};

