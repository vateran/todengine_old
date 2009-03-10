#include "tod/todpython/todpython_extension.h"

#include "tod/core/define.h"
#include "tod/core/kernel.h"
#include "tod/core/module.h"
#include "tod/core/resourcemanager.h"
#include "tod/core/xmlserializer.h"
#include "tod/engine/triggerserver.h"

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
TodNode* new_todnode(const typechar_t* type_name, const Path& path)
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
PyObject* TodPython_res(PyObject* self, PyObject* args)
{   
    TodObject* o = reinterpret_cast<TodObject*>(
        TodObjectType.tp_new(&TodObjectType, 0, 0));
    if (0 == o)
        return 0;
    o->object_ = ResourceManager::instance();
    return reinterpret_cast<PyObject*>(o);
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
    o->createdByPython_ = true;
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
            PyString_FromString(i->second->getName()));
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
    tod::engine::TriggerServer::instance()->quit();
    Py_INCREF(Py_True);
    return Py_True;
}


//-----------------------------------------------------------------------------
PyObject* TodPython_serialize(PyObject* self, PyObject* args)
{
    TodNode* o = 0;
    char* uri = 0;
    if (!PyArg_ParseTuple(args, "sO:serialize", &uri, &o))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    XmlSerializer s;
    if (s.serialize(String(uri), o->node_))
    {
        Py_INCREF(Py_True);
        return Py_True;
    }
    else
    {
        Py_INCREF(Py_False);
        return Py_False;
    }
}


//-----------------------------------------------------------------------------
PyObject* TodPython_deserialize(PyObject* self, PyObject* args)
{
    TodNode* parent_o = 0;
    char* uri = 0;
    char* name = 0;
    if (!PyArg_ParseTuple(args, "Os|s:deserialize", &parent_o, &uri, &name))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    XmlSerializer s;
    Object* result_o = 0;
    if (name)
        result_o = s.deserialize(
            parent_o->node_, String(uri), String(name).c_str());
    else
        result_o = s.deserialize(parent_o->node_, String(uri), 0);
    if (0 == result_o)
        return PyErr_Format(PyExc_Exception, "resource not found(%s)", uri);

    TodObject* o = reinterpret_cast<TodObject*>(
        TodObjectType.tp_new(&TodObjectType, 0, 0));
    if (0 == o)
    {
        Py_INCREF(Py_None);
        return Py_None;
    }
    o->object_ = result_o;
    return reinterpret_cast<PyObject*>(o);

}


//-----------------------------------------------------------------------------
PyObject* TodPython_getModuleList(PyObject* self, PyObject* args)
{
    PyObject* result = PyTuple_New(Kernel::instance()->getNumModules());

    int i = 0;
    for (Kernel::Modules::iterator m = Kernel::instance()->firstModule();
         m != Kernel::instance()->lastModule(); ++m, ++i)
    {
        Module* module = m->second;
        PyTuple_SET_ITEM(result, i, PyString_FromString(module->getName()));
    }

    return result;
}


//-----------------------------------------------------------------------------
PyObject* TodPython_getTypeList(PyObject* self, PyObject* args)
{
    char* module_name = 0;
    if (!PyArg_ParseTuple(args, "s:getTypeList", &module_name))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    PyObject* result = 0;
    Module* module = Kernel::instance()->findModule(String(module_name).c_str());
    if (0 == module)
    {
        result = PyTuple_New(0);
        return result;
    }
    else
        result = PyTuple_New(module->getNumTypes());
    
    int i = 0;
    for (Module::Types::iterator t = module->firstType();
         t != module->lastType(); ++t, ++i)
    {
        const Type* type = t->second;
        PyTuple_SET_ITEM(result, i, PyString_FromString(type->getName()));
    }

    return result;

}
