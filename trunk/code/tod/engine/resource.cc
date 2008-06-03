#include "tod/engine/resource.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
Resource::Resource(const Uri& uri):
uri_(uri), refCount_(0)
{

}


//-----------------------------------------------------------------------------
Resource::~Resource()
{

}


//-----------------------------------------------------------------------------
int Resource::addRef()
{
    return ++refCount_;
}


//-----------------------------------------------------------------------------
int Resource::getRef() const
{
    return refCount_;
}


//-----------------------------------------------------------------------------
int Resource::release()
{
    if (0 == --refCount_)
    {
        delete this;
        return 0;
    }
    return refCount_;
}


//-----------------------------------------------------------------------------
bool Resource::invalid() const
{
    return !valid();
}


//-----------------------------------------------------------------------------
const Uri& Resource::getUri() const
{
    return uri_;
}
