#pragma once

namespace ai
{
	class CastEviscerateAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastEviscerateAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "eviscerate") {} 
	};

	class CastSliceAndDiceAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastSliceAndDiceAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "slice and dice") {} 
	};

	class CastExposeArmorAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastExposeArmorAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "expose armor") {} 
	};

	class CastRuptureAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastRuptureAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "rupture") {} 
	};
	
	class CastKidneyShotAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastKidneyShotAction(PlayerbotAI* botAI) : CastMeleeSpellAction(botAI, "kidney shot") {} 
	};
	
}