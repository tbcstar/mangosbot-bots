#pragma once
#include "../Value.h"

namespace botAI
{
    class ChatValue : public ManualSetValue<ChatMsg>
	{
	public:
        ChatValue(PlayerbotAI* botAI) : ManualSetValue<ChatMsg>(botAI, CHAT_MSG_WHISPER) { }
    };
}
