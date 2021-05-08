#pragma once

namespace ai
{
	class CastEviscerateAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastEviscerateAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "eviscerate") {} 
	};

	class CastSliceAndDiceAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastSliceAndDiceAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "slice and dice") {} 
	};

	class CastExposeArmorAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastExposeArmorAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "expose armor") {} 
	};

	class CastRuptureAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastRuptureAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "rupture") {} 
	};
	
	class CastKidneyShotAction : public CastMeleeSpellAction 
	{ 
	public: 
		CastKidneyShotAction(PlayerbotAI* botAI) : CastMeleeSpellAction(ai, "kidney shot") {} 
	};
	
}