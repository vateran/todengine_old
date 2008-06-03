#include "tod/todpython/todpython_extension.h"

#include "tod/core/define.h"
#include "tod/core/kernel.h"
#include "tod/core/resourcemanager.h"

using namespace tod;

//-----------------------------------------------------------------------------
TodNode* find_todnode(const Path& path)
{
    TodNodes::iterator find_iter = g_todobjects.find(path);
    if (find_iter == g_todobjects.end())
        return 0;
    return find_iter->second;
}


//-----------------------------------------------------------------------------
TodNode* new_todnode(const typename_t* type_name, const Path& path)
{
    TodNode* exist_o = find_todnode(path);
    if (exist_o)
    {
        Py_INCREF(exist_o);
        return exist_o;
    }

    TodNode* o = reinterpret_cast<TodNode*>(
        TodNodeType.tp_new(&TodNodeType, 0, 0));
    if (0 == o)
        return 0;
    o->node_ = Kernel::instance()->create(type_name, path);
    if (o->node_.invalid())
    {
        Py_DECREF(o);
        return 0;
    }
    g_todobjects.insert(TodNodes::value_type(o->node_->getAbsolutePath(), o));
    return o;
}


//-----------------------------------------------------------------------------
PyObject* TodPython_resroot(PyObject* self, PyObject* args)
{
    char* resource_root = 0;
    if (!PyArg_ParseTuple(args, "s:resroot", &resource_root))
        return PyErr_Format(PyExc_Exception, "mismatch argument");
    ResourceManager::instance()->initialize(String("%s", resource_root).c_str());
    Py_INCREF(Py_True);
    return Py_True;
}


//-----------------------------------------------------------------------------
PyObject* TodPython_newobject(PyObject* self, PyObject* args)
{
    // parse argument
    char* type_name = 0;
    if (!PyArg_ParseTuple(args, "s:newobject", &type_name))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    TodObject* o = reinterpret_cast<TodObject*>(
        TodObjectType.tp_new(&TodObjectType, 0, 0));
    if (0 == o)
        return 0;
    o->object_ = Kernel::instance()->create(String("%s", type_name).c_str());
    if (0 == o->object_)
    {
        Py_DECREF(o);
        return 0;
    }
    return reinterpret_cast<PyObject*>(o);
}


//-----------------------------------------------------------------------------
PyObject* TodPython_new(PyObject* self, PyObject* args)
{
    // parse argument
    char* type_name = 0;
    char* path = 0;
    if (!PyArg_ParseTuple(args, "ss:new", &type_name, &path))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    // create new object on NOH and create new TodNode
    TodNode* o = new_todnode(
        String("%s", type_name).c_str(), String("%s", path));
    if (0 == o)
        return PyErr_Format(PyExc_Exception, "unable to create");
    return reinterpret_cast<PyObject*>(o);
}


//-----------------------------------------------------------------------------
PyObject* TodPython_get(PyObject* self, PyObject* args)
{
    char* path = 0;
    if (!PyArg_ParseTuple(args, "s:get", &path))
        return PyErr_Format(PyExc_Exception, "mismatch argument");
    TodNode* exist = find_todnode(String("%s", path));
    if (exist)
    {
        Py_INCREF(exist);
        return reinterpret_cast<PyObject*>(exist);
    }
    Node* node = Kernel::instance()->lookup(String("%s", path));
    if (0 == node)
        return PyErr_Format(PyExc_Exception, "not found node in NOH");
    TodNode* o = reinterpret_cast<TodNode*>(
        TodNodeType.tp_new(&TodNodeType, 0, 0));
    if (0 == o)
        return 0;
    o->node_ = node;
    g_todobjects.insert(TodNodes::value_type(node->getAbsolutePath(), o));
    return reinterpret_cast<PyObject*>(o);
}


//-----------------------------------------------------------------------------
PyObject* TodPython_delete(PyObject* self, PyObject* args)
{
    char* path = 0;
    if (!PyArg_ParseTuple(args, "s:delete", &path))
        return PyErr_Format(PyExc_Exception, "mismatch argument");
    TodNode* exist = find_todnode(String("%s", path));
    if (exist)
    {
        Py_DECREF(exist);
    }
    else
    {
        Node* node = Kernel::instance()->lookup(String("%s", path));
        if (0 == node)
            return PyErr_Format(PyExc_Exception, "not found path[%s]", path);
        node->release();
    }
    Py_INCREF(Py_None);
    return Py_None;
}


//-----------------------------------------------------------------------------
PyObject* TodPython_ls(PyObject* self, PyObject* args)
{
    Node* node = Kernel::instance()->getCwn();    
    PyObject* children_names = PyTuple_New(node->getNumChildren());
    int index = 0;
    for (Node::NodeIterator i = node->firstChildNode();
         i != node->lastChildNode(); ++i, ++index)
    {
        PyTuple_SET_ITEM(children_names, index,
            PyString_FromString(i->second->getName().toAnsiString().c_str()));
    }
    return children_names;
}


//-----------------------------------------------------------------------------
PyObject* TodPython_pushCwn(PyObject* self, PyObject* args)
{
    TodNode* o = 0;
    if (!PyArg_ParseTuple(args, "O:pushcwn", &o))
        return PyErr_Format(PyExc_Exception, "mismatch argument");
    Kernel::instance()->pushCwn(o->node_);
    Py_INCREF(Py_True);
    return Py_True;
}


//-----------------------------------------------------------------------------
PyObject* TodPython_popCwn(PyObject* self, PyObject* args)
{
    Kernel::instance()->popCwn();
    Py_INCREF(Py_True);
    return Py_True;
}


//-----------------------------------------------------------------------------
PyObject* TodPython_todprint(PyObject* self, PyObject* args)
{
    return 0;
}


//-----------------------------------------------------------------------------
PyObject* TodPython_exit(PyObject* self, PyObject* args)
{
    return 0;
}

/*PyObject* dict = PyModule_GetDict(g_module);
PyObject *key, *value;
int pos = 0;
while (PyDict_Next(dict, &pos, &key, &value))
{
PyObject* str_key = PyObject_Str(key);
PyObject* str_value = PyObject_Str(value);
printf("%s:%s\n", PyString_AsString(str_key), PyString_AsString(str_value));
}*/
