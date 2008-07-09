#include "tod/core/scriptserver.h"

#include "tod/core/methodbinder.h"

using namespace tod;

//-----------------------------------------------------------------------------
static void ScriptServer_b_run_s(ScriptServer* self, Parameter* param)
{
    param->out()->get<bool>(0) =
        self->run(param->in()->get<String>(0).get());
}

//-----------------------------------------------------------------------------
void ScriptServer::bindMethod()
{
    BIND_METHOD(b_run_s, ScriptServer_b_run_s);
}
