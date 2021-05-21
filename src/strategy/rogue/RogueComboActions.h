#pragma once

namespace botAI
{
	class CastComboAction : public CastMeleeSpellAction
	{
	public:
	    CastComboAction(PlayerbotAI* botAI, std::string const& name) : CastMeleeSpellAction(botAI, name) { }

	    virtual bool isUseful()
	    {
	        return CastMeleeSpellAction::isUseful() && AI_VALUE2(uint8, "combo", "self target") < 5;
	    }
	};

	class CastSinisterStrikeAction : public CastComboAction
	{
	public:
		CastSinisterStrikeAction(PlayerbotAI* botAI) : CastComboAction(botAI, "sinister strike") { }
	};

    class CastMutilateAction : public CastComboAction
    {
    public:
        CastMutilateAction(PlayerbotAI* botAI) : CastComboAction(botAI, "mutilate") { }
    };

    class CastRiposteAction : public CastComboAction
    {
    public:
        CastRiposteAction(PlayerbotAI* botAI) : CastComboAction(botAI, "riposte") { }
    };

	class CastGougeAction : public CastComboAction
	{
	public:
		CastGougeAction(PlayerbotAI* botAI) : CastComboAction(botAI, "gouge") { }
	};

    class CastBackstabAction : public CastComboAction
    {
    public:
        CastBackstabAction(PlayerbotAI* botAI) : CastComboAction(botAI, "backstab") { }
    };
}
