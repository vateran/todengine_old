#include "tod/core/scriptserver.h"

using namespace tod;

IMPLEMENT_CLASS(ScriptServer, Node);

//-----------------------------------------------------------------------------
bool ScriptServer::run(const char_t* str, Parameter* parameter)
{
    return false;
}


//-----------------------------------------------------------------------------
bool ScriptServer::run(const Uri& uri)
{
    return false;
}
