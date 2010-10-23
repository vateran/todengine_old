#include "tod/todlua/todluascriptserver.h"

#include "tod/core/methodbinder.h"

using namespace tod;

//-----------------------------------------------------------------------------
static void TodLuaScriptServer_v_newThread_s
(TodLuaScriptServer* self, Parameter* param)
{
    self->newThread(param->in()->get<String>(0).get());
}


//-----------------------------------------------------------------------------
void TodLuaScriptServer::bindMethod()
{
    BIND_METHOD(v_newThread_s, TodLuaScriptServer_v_newThread_s);
}
