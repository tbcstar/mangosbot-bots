#pragma once

namespace ai
{
	class CastSapAction : public CastMeleeSpellAction
	{ 
	public: 
		CastSapAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "sap") {} 
	};

	class CastGarroteAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastGarroteAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "garrote") {} 
	};


	class CastCheapShotAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastCheapShotAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "cheap shot") {} 
	};
	
}