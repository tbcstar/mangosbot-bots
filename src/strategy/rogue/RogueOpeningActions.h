#pragma once

namespace ai
{
	class CastSapAction : public CastMeleeSpellAction
	{ 
	public: 
		CastSapAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "sap") {} 
	};

	class CastGarroteAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastGarroteAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "garrote") {} 
	};


	class CastCheapShotAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastCheapShotAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "cheap shot") {} 
	};
	
}