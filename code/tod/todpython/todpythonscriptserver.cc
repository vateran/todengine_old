#include "tod/todpython/todpython_extension.h"
#include "tod/todpython/todpythonscriptserver.h"

#include "tod/core/kernel.h"
#include "tod/core/module.h"
#include "tod/core/resourcemanager.h"
#include "tod/core/nodeeventpublisher.h"

using namespace tod;

IMPLEMENT_CLASS(TodPythonScriptServer, ScriptServer);

INCLUDE_MODULE(Engine);
INCLUDE_MODULE(D3D9Graphics);
INCLUDE_MODULE(TodPython);
INCLUDE_MODULE(TodLua);

//-----------------------------------------------------------------------------
static PyMethodDef TodPythonMethods[] =
{   
    { "res",  TodPython_res, METH_VARARGS, "get ResourceManager" },
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
static void at_Exit()
{
    // if s_standAlone_ == true then this function called at exit Python
    // SingletonServer::clear() must be called by current process(Python).
    SingletonServer::instance()->clear();
}


//-----------------------------------------------------------------------------
void TodPythonScriptServer::initialize()
{
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

    // initialize DynamicModules
    USING_MODULE(Engine);
    USING_MODULE(D3D9Graphics);
    USING_MODULE(TodPython);
    USING_MODULE(TodLua);

    if (0 == Kernel::instance()->lookup("/sys/server/script/python"))
    {
        TodPythonScriptServer::setSingletonPath("/sys/server/script/python");
        TodPythonScriptServer::s_standAlone_ = true;
        Py_AtExit(at_Exit);
    }
    else
    {
        TodPythonScriptServer::setSingletonPath("/sys/server/script/python");
        TodPythonScriptServer::s_standAlone_ = false;
    }
}


//-----------------------------------------------------------------------------
void TodPythonScriptServer::NodeEventSubscriberImpl::onAttachTo
(Node* parent, Node* child)
{
}

//-----------------------------------------------------------------------------
void TodPythonScriptServer::NodeEventSubscriberImpl::onDetachFrom
(Node* parent, Node* child)
{
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
bool TodPythonScriptServer::run(const String& str, String* result)
{
    if (PyRun_SimpleString(str) == -1)
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool TodPythonScriptServer::call(const String& str, Parameter* parameter)
{
    return false;
}


//-----------------------------------------------------------------------------
bool TodPythonScriptServer::runFile(const Uri& uri, String* result)
{
    return false;
}


//-----------------------------------------------------------------------------
PyObject* g_module = 0;
TodNodes g_todobjects;
bool TodPythonScriptServer::s_standAlone_ = false;
TodPythonScriptServer::NodeEventSubscriberImpl
TodPythonScriptServer::nodeEventSubscriber_;


//-----------------------------------------------------------------------------
void initialize_TodPython(Module* module)
{
    REGISTER_TYPE(module, TodPythonScriptServer);
}


//-----------------------------------------------------------------------------
void finalize_TodPython(Module* module)
{
    if (TodPythonScriptServer::s_standAlone_)
        Py_Finalize();
}

//-----------------------------------------------------------------------------
DECLARE_MODULE(TodPython);

