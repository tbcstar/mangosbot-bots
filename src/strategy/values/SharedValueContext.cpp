/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "SharedValueContext.h"

template<class T>
Value<T>* SharedValueContext::getGlobalValue(std::string const& name = "")
{
    NamedObjectContextList<UntypedValue> valueContexts;
    valueContexts.Add(this);
    PlayerbotAI* botAI = new PlayerbotAI();
    UntypedValue* value = valueContexts.GetObject(name, botAI);
    delete botAI;
    return dynamic_cast<Value<T>*>(value);
}

template<class T>
Value<T>* SharedValueContext::getGlobalValue(std::string const& name, std::string const& param)
{
    return getGlobalValue<T>((string(name) + "::" + param));
}

template<class T>
Value<T>* SharedValueContext::getGlobalValue(std::string const& name, uint32 param)
{
    std::ostringstream out; out << param;
    return getGlobalValue<T>(name, out.str());
}
