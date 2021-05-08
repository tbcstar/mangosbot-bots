#pragma once

class PlayerbotAI;

namespace ai
{
    class AiObjectContext;
    class ChatHelper;

    class AiObject : public PlayerbotAIAware
	{
	public:
        AiObject(PlayerbotAI* botAI);

    protected:
        Player* bot;
        Player* GetMaster();
        AiObjectContext* context;
        ChatHelper* chat;
	};

    class AiNamedObject : public AiObject
    {
    public:
        AiNamedObject(PlayerbotAI* botAI, string name) : AiObject(botAI), name(name) {}

    public:
        virtual string getName() { return name; }

    protected:
        string name;
    };
}
