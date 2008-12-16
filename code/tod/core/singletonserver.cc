#include "tod/core/singletonserver.h"

#include "tod/core/singleton.h"

using namespace tod;

//-----------------------------------------------------------------------------
SingletonServer::SingletonServer()
{

}


//-----------------------------------------------------------------------------
SingletonServer::~SingletonServer()
{
    clear();
}


//-----------------------------------------------------------------------------
void SingletonServer::clear()
{
    singletons_.reverse();
    for (Singletons::iterator i = singletons_.begin();
         i != singletons_.end();)
    {
        SingletonBase* s = *i;
        i = singletons_.erase(i);
        delete s;
    }
}


//-----------------------------------------------------------------------------
void SingletonServer::registerSingleton(SingletonBase* singleton)
{
    singletons_.push_back(singleton);
}


//-----------------------------------------------------------------------------
void SingletonServer::unregisterSingleton(SingletonBase* singleton)
{
    singletons_.remove(singleton);
}


//-----------------------------------------------------------------------------
SingletonServer* SingletonServer::instance()
{
    return &s_instance_;
}


//-----------------------------------------------------------------------------
SingletonServer SingletonServer::s_instance_;
