#include "tod/core/rtti.h"

using namespace tod::core;
using namespace tod::core::type;

//-----------------------------------------------------------------------------
Rtti::Rtti(const type::name_t* name, const Rtti* base):
name(name), base(base), metaObject(0)
{
    // empty
}


//-----------------------------------------------------------------------------
const Name& Rtti::Name() const
{
    return name;
}

//-----------------------------------------------------------------------------
bool Rtti::isKindOf(const type::name_t* name) const
{
    const Rtti* s = this;
    while (s)
    {
        if (s->name == name)
            return true;
        s = s->base;
    }
    return false;
}

//-----------------------------------------------------------------------------
bool Rtti::isKindOf(const Rtti& rtti) const
{
    const Rtti* s = this;
    while (s)
    {
        if (s == &rtti)
            return true;
        s = s->base;
    }
    return false;
}

//-----------------------------------------------------------------------------
bool Rtti::equal(const Rtti& rtti) const
{
    return this == &rtti;
}
