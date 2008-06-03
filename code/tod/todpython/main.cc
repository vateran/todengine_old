#include <Windows.h>
#include <python.h>
#include "tod/todpython/todpythonscriptserver.h"

using namespace tod;

//-----------------------------------------------------------------------------
PyMODINIT_FUNC inittodpython(void)
{
    TodPythonScriptServer::initialize();
}
