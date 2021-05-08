#pragma once

namespace ai {
	class CastBearFormAction : public CastBuffSpellAction { 
	public: 
		CastBearFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "bear form") {} 

        virtual bool isPossible() {
			return CastBuffSpellAction::isPossible() && !botAI->HasAura("dire bear form", GetTarget());
		}
        virtual bool isUseful() {
			return CastBuffSpellAction::isUseful() && !botAI->HasAura("dire bear form", GetTarget());
		}
	};

	class CastDireBearFormAction : public CastBuffSpellAction { 
	public: 
		CastDireBearFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "dire bear form") {} 
        
        virtual NextAction** getAlternatives() {
			return NextAction::merge(NextAction::array(0, new NextAction("bear form"), NULL), CastSpellAction::getAlternatives());
		}
	};

	class CastCatFormAction : public CastBuffSpellAction { 
	public: 
		CastCatFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "cat form") {} 
	};

	class CastTreeFormAction : public CastBuffSpellAction {
	public:
		CastTreeFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "tree of life") {}
	};

	class CastMoonkinFormAction : public CastBuffSpellAction { 
	public: 
		CastMoonkinFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "moonkin form") {} 
	};

	class CastCasterFormAction : public CastBuffSpellAction { 
	public: 
		CastCasterFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(ai, "caster form") {} 

		virtual bool isUseful() {
			return botAI->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "cat form", "travel form", "aquatic form", 
				"flight form", "swift flight form", "moonkin form", "tree of life", NULL);
		}
		virtual bool isPossible() { return true; }
		
		virtual bool Execute(Event event);
	};

}
