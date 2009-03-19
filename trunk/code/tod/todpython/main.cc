#include <python.h>
#include "tod/core/define.h"
#include "tod/todpython/todpythonscriptserver.h"

using namespace tod;

//-----------------------------------------------------------------------------
PyMODINIT_FUNC inittodpython(void)
{
    TodPythonScriptServer::initialize();
}
