#include "tod/core/scriptserver.h"

using namespace tod;

IMPLEMENT_CLASS(ScriptServer, Node);

//-----------------------------------------------------------------------------
bool ScriptServer::run(const String& str)
{
    return false;
}

//-----------------------------------------------------------------------------
bool ScriptServer::run(const String& str, Parameter* parameter)
{
    return false;
}


//-----------------------------------------------------------------------------
bool ScriptServer::run(const Uri& uri)
{
    return false;
}
