#include "tod/todpython/todpython_extension.h"
#include "tod/todpython/todpythonscriptserver.h"

#include "tod/core/kernel.h"
#include "tod/core/module.h"
#include "tod/core/resourcemanager.h"

using namespace tod;

IMPLEMENT_CLASS(TodPythonScriptServer, ScriptServer);
INCLUDE_MODULE(Engine);
INCLUDE_MODULE(D3D9Graphics);
INCLUDE_MODULE(TodPython);

//-----------------------------------------------------------------------------
static PyMethodDef TodPythonMethods[] =
{   
    { "resroot",  TodPython_resroot, METH_VARARGS, "set resource root" },
    { "newobj",  TodPython_newobject, METH_VARARGS, "create new nonamed TodObject" },
    { "new",  TodPython_new, METH_VARARGS, "create new TodNode" },
    { "get",  TodPython_get, METH_VARARGS, "get TobObject from NOH" },
    { "delete",  TodPython_delete, METH_VARARGS, "delete TodNode" },
    { "ls",  TodPython_ls, METH_VARARGS, "list current work node" },
    { "pushcwn",  TodPython_pushCwn, METH_VARARGS, "push current work node" },
    { "popcwn",  TodPython_popCwn, METH_VARARGS, "pop current work node" },
    { "todprint",  TodPython_todprint, METH_VARARGS, "debug print" },
    { "exit",  TodPython_exit, METH_VARARGS, "exit application" },
    { "serialize",  TodPython_serialize, METH_VARARGS,
        "serialize objects to resource" },
    { "deserialize",  TodPython_deserialize, METH_VARARGS, 
        "deserialize objects from resource" },
    { "getModuleList",  TodPython_getModuleList, METH_VARARGS, 
       "get module list" },
    { "getTypeList",  TodPython_getTypeList, METH_VARARGS, 
      "get type list specified module name" },
    { NULL, NULL, 0, NULL }        /* Sentinel */
};


//-----------------------------------------------------------------------------
void TodPythonScriptServer::initialize()
{
    USING_MODULE(Engine);
    USING_MODULE(D3D9Graphics);
    USING_MODULE(TodPython);

    // initialize TodPython module
    Py_SetProgramName("TodPython");
    //PySys_SetArgv();
    g_module = Py_InitModule("todpython", TodPythonMethods);    

    // initialize exception handler
    PyObject* error_obj = PyErr_NewException("todpython.error", 0, 0);
    Py_INCREF(error_obj);
    PyModule_AddObject(g_module, "error", error_obj);

    // initialize TodObject
    PyType_Ready(&TodObjectType);
    Py_INCREF(&TodObjectType);
    PyModule_AddObject(g_module, "TodObject", (PyObject*)(&TodObjectType));

    // initialize TodNode
    PyType_Ready(&TodNodeType);
    Py_INCREF(&TodNodeType);
    PyModule_AddObject(g_module, "TodNode", (PyObject*)(&TodNodeType));

    if (0 == Kernel::instance()->lookup(STRING("/sys/server/script/python")))
    {
        Kernel::instance()->create(STRING("TodPythonScriptServer"),
            STRING("/sys/server/script/python"));
        TodPythonScriptServer::s_standAlone_ = true;
    }
    else
    {
        TodPythonScriptServer::s_standAlone_ = false;
    }
}


//-----------------------------------------------------------------------------
TodPythonScriptServer::TodPythonScriptServer()
{   
    // Test to see if we are running inside an existing Python interpreter
    if (!Py_IsInitialized())
    {
        Py_Initialize();
        initialize();
    }
}


//-----------------------------------------------------------------------------
TodPythonScriptServer::~TodPythonScriptServer()
{
    
}


//-----------------------------------------------------------------------------
bool TodPythonScriptServer::run(const String& str)
{
    if (PyRun_SimpleString(str.toAnsiString().c_str()) == -1)
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool TodPythonScriptServer::run(const String& str, Parameter* parameter)
{
    return false;
}


//-----------------------------------------------------------------------------
bool TodPythonScriptServer::run(const Uri& uri)
{
    return false;
}


//-----------------------------------------------------------------------------
PyObject* g_module = 0;
TodNodes g_todobjects;
bool TodPythonScriptServer::s_standAlone_ = false;


//-----------------------------------------------------------------------------
void initialize_TodPython(Module* module)
{
    REGISTER_TYPE(module, TodPythonScriptServer);
}


//-----------------------------------------------------------------------------
void finalize_TodPython(Module* module)
{
    Py_DECREF(g_module);
    //if (s_standAlone_)
    {
        Py_Finalize();
    }
}

//-----------------------------------------------------------------------------
DECLARE_MODULE(TodPython);
