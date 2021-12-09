/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "Define.h"

class PlayerbotAIBase
{
    public:
	    PlayerbotAIBase();

	    bool CanUpdateAI();
	    void SetNextCheckDelay(uint32 const delay);
        void IncreaseNextCheckDelay(uint32 delay);
	    void YieldThread();
        virtual void UpdateAI(uint32 elapsed);
        virtual void UpdateAIInternal(uint32 elapsed) = 0;
        bool IsActive();

    protected:
	    uint32 nextAICheckDelay;
};