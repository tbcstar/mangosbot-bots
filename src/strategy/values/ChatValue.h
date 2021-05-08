#pragma once
#include "../Value.h"

namespace ai
{
    class ChatValue : public ManualSetValue<ChatMsg>
	{
	public:
        ChatValue(PlayerbotAI* botAI) : ManualSetValue<ChatMsg>(ai, CHAT_MSG_WHISPER) {}
    };
}
