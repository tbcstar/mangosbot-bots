#pragma once

namespace ai {
	class CastBearFormAction : public CastBuffSpellAction { 
	public: 
		CastBearFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "bear form") {} 

        virtual bool isPossible() {
			return CastBuffSpellAction::isPossible() && !botAI->HasAura("dire bear form", GetTarget());
		}
        virtual bool isUseful() {
			return CastBuffSpellAction::isUseful() && !botAI->HasAura("dire bear form", GetTarget());
		}
	};

	class CastDireBearFormAction : public CastBuffSpellAction { 
	public: 
		CastDireBearFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "dire bear form") {} 
        
        virtual NextAction** getAlternatives() {
			return NextAction::merge(NextAction::array(0, new NextAction("bear form"), nullptr), CastSpellAction::getAlternatives());
		}
	};

	class CastCatFormAction : public CastBuffSpellAction { 
	public: 
		CastCatFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "cat form") {} 
	};

	class CastTreeFormAction : public CastBuffSpellAction {
	public:
		CastTreeFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "tree of life") {}
	};

	class CastMoonkinFormAction : public CastBuffSpellAction { 
	public: 
		CastMoonkinFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "moonkin form") {} 
	};

	class CastCasterFormAction : public CastBuffSpellAction { 
	public: 
		CastCasterFormAction(PlayerbotAI* botAI) : CastBuffSpellAction(botAI, "caster form") {} 

		virtual bool isUseful() {
			return botAI->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "cat form", "travel form", "aquatic form", 
				"flight form", "swift flight form", "moonkin form", "tree of life", nullptr);
		}
		virtual bool isPossible() { return true; }
		
		bool Execute(Event event) override;
	};

}
