#include "tod/todpython/todpython_extension.h"

#include "tod/core/color.h"
#include "tod/core/uri.h"
#include "tod/core/simpleproperty.h"
#include "tod/engine/format.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
int todpython_toint(PyObject* value)
{
    if (PyInt_Check(value))
        return PyInt_AsLong(value);
    else if (PyFloat_Check(value))
        return static_cast<int>(PyFloat_AsDouble(value));
    return 0;
}

//-----------------------------------------------------------------------------
PyObject* build_value(Variable* variable)
{
    if (TypeId<bool>::check(variable->getType()))
    {   
        return Py_BuildValue("b",
            reinterpret_cast<SimpleVariable<bool>*>(variable)->get());
    }
    else if (TypeId<short>::check(variable->getType()))
    {   
        return Py_BuildValue("h",
            reinterpret_cast<SimpleVariable<short>*>(variable)->get());
    }
    else if (TypeId<long>::check(variable->getType()))
    {   
        return Py_BuildValue("l",
            reinterpret_cast<SimpleVariable<long>*>(variable)->get());
    }
    else if (TypeId<int>::check(variable->getType()))
    {   
        return Py_BuildValue("i",
            reinterpret_cast<SimpleVariable<int>*>(variable)->get());
    }
    else if (TypeId<__int64>::check(variable->getType()))
    {
        return Py_BuildValue("L",
            reinterpret_cast<SimpleVariable<__int64>*>(variable)->get());
    }
    else if (TypeId<float>::check(variable->getType()))
    {
        return Py_BuildValue("f",
            reinterpret_cast<SimpleVariable<float>*>(variable)->get());
    }
    else if (TypeId<double>::check(variable->getType()))
    {
        return Py_BuildValue("d",
            reinterpret_cast<SimpleVariable<double>*>(variable)->get());
    }
    else if (TypeId<String>::check(variable->getType()))
    {
        return Py_BuildValue("s",
            reinterpret_cast<SimpleVariable<String>*>(variable)->
            get().toAnsiString().c_str());
    }
    else if (TypeId<Node*>::check(variable->getType()))
    {
        Node* node = reinterpret_cast<SimpleVariable<Node*>*>(variable)->get();
        if (0 == node)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        TodNode* o = reinterpret_cast<TodNode*>(
            TodNodeType.tp_new(&TodNodeType, 0, 0));
        if (0 == o)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        o->node_ = node;
        return reinterpret_cast<PyObject*>(o);
    }
    return 0;
}


//-----------------------------------------------------------------------------
PyObject* build_input_paramter
(Variables* v, PyObject* args, const char* method_name)
{
    index_t num_args = static_cast<index_t>(PyTuple_Size(args));
    for (index_t a = 0; a < num_args; ++a)
    {
        PyObject* arg = PyTuple_GET_ITEM(args, a);
        if (TypeId<int>::check(v->get(a)->getType()))
        {
            typedef int type;
            if (PyInt_Check(arg))
            {
                v->get<type>(a) = PyInt_AsLong(arg);
            }
            else if (PyFloat_Check(arg))
            {
                v->get<type>(a) = static_cast<int>(PyFloat_AsDouble(arg));
            }
            else
            {
                return PyErr_Format(PyExc_TypeError,
                    "%s() : cannot convert parameter from \'%s\' to \'int\'",
                    method_name, arg->ob_type->tp_name);
                return 0;
            }
        }
        else if (TypeId<float>::check(v->get(a)->getType()))
        {
            typedef float type;
            if (PyInt_Check(arg))
            {
                v->get<type>(a) = static_cast<type>(PyInt_AsLong(arg));
            }
            else if (PyFloat_Check(arg))
            {
                v->get<type>(a) = static_cast<type>(PyFloat_AsDouble(arg));
            }
            else
            {
                return PyErr_Format(PyExc_TypeError,
                    "%s() : cannot convert parameter from \'%s\' to \'float\'",
                    method_name, arg->ob_type->tp_name);
                return 0;
            }
        }
        else if (TypeId<String>::check(v->get(a)->getType()))
        {
            if (PyString_Check(arg))
            {
                v->get<String>(a) = String("%s", PyString_AsString(arg));
            }
            else
            {
                return PyErr_Format(PyExc_TypeError,
                    "%s() : cannot convert parameter from \'%s\' to \'String\'",
                    method_name, arg->ob_type->tp_name);
            }
        }
        else if (TypeId<Node*>::check(v->get(a)->getType()))
        {
            if (PyObject_TypeCheck(arg, &TodNodeType))
            {
                TodNode* o = reinterpret_cast<TodNode*>(arg);
                v->get<Node*>(a) = *o->node_;
            }
            else
            {
                return PyErr_Format(PyExc_TypeError,
                    "%s() : cannot convert parameter from \'%s\' to \'TodNode\'",
                    method_name, arg->ob_type->tp_name);
            }
        }
        else
        {
            return PyErr_Format(PyExc_TypeError,
                "%s() : not supported parameter type \'%s\'",
                method_name, arg->ob_type->tp_name);
        }
    }

    return Py_True;
}


//-----------------------------------------------------------------------------
int set_property
(tod::core::Object* object, const Path& path, PyObject* name, PyObject* value)
{
    // find property
    char* prop_name = PyString_AsString(name);
    Property* prop = object->getType().
        findProperty(String("%s", prop_name).c_str());
    if (0 == prop)
    {
        PyErr_Format(PyExc_AttributeError,
            "\'%s\' object has no property \'%s\'",
            path.toAnsiString().c_str(), prop_name);
        return -1;
    }

    // set property
    if (TypeId<bool>::check(prop->getType()))
    {
        typedef SimpleProperty<bool> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        if (PyBool_Check(value))
            ap->set(object, Py_True == value ? true:false);
        else if (PyInt_Check(value))
            ap->set(object, PyInt_AsLong(value) ? true:false);
        else if (PyFloat_Check(value))
            ap->set(object, PyFloat_AsDouble(value) ? true:false);
        else if (PyString_Check(value))
        {
            char* v = PyString_AsString(value);
            if (stricmp(v, "true") == 0 ||
                stricmp(v, "t") == 0 ||
                stricmp(v, "on") == 0)
                ap->set(object, true);
            else
                ap->set(object, false);
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'int\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<int>::check(prop->getType()))
    {
        typedef SimpleProperty<int> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        if (PyInt_Check(value))
            ap->set(object, PyInt_AsLong(value));
        else if (PyFloat_Check(value))
            ap->set(object, static_cast<int>(PyFloat_AsDouble(value)));
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'int\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<float>::check(prop->getType()))
    {
        typedef SimpleProperty<float> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        if (PyFloat_Check(value))
            ap->set(object, static_cast<float>(PyFloat_AsDouble(value)));
        else if (PyInt_Check(value))
            ap->set(object, static_cast<float>(PyInt_AsLong(value)));
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'float\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<double>::check(prop->getType()))
    {
        typedef SimpleProperty<double> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        if (PyFloat_Check(value))
            ap->set(object, PyFloat_AsDouble(value));
        else if (PyInt_Check(value))
            ap->set(object, PyInt_AsLong(value));
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'double\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    if (TypeId<String>::check(prop->getType()))
    {
        if (PyString_Check(value))
        {
            typedef SimpleProperty<const String&> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(object, String("%s", PyString_AsString(value)));
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'String\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<Uri>::check(prop->getType()))
    {
        if (PyString_Check(value))
        {
            typedef SimpleProperty<const Uri&> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(object, String("%s", PyString_AsString(value)).c_str());
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'Uri\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<Name>::check(prop->getType()))
    {
        if (PyString_Check(value))
        {
            typedef SimpleProperty<const Name&> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(object, String("%s", PyString_AsString(value)).c_str());
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'Name\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<Vector3>::check(prop->getType()))
    {
        if (PyTuple_Check(value))
        {
            typedef SimpleProperty<const Vector3&> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            Vector3 v;
            for (int i = 0; i < 3; ++i)
            {
                PyObject* e = PyTuple_GET_ITEM(value, i);
                if (PyInt_Check(e))
                    v.set(i, static_cast<float>(PyInt_AsLong(e)));
                else if (PyFloat_Check(e))
                    v.set(i, static_cast<float>(PyFloat_AsDouble(e)));
            }
            ap->set(object, v);
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'Vector3\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<Color>::check(prop->getType()))
    {
        if (PyTuple_Check(value))
        {
            typedef SimpleProperty<const Color&> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            Color v(
                todpython_toint(PyTuple_GET_ITEM(value, 0)),
                todpython_toint(PyTuple_GET_ITEM(value, 1)),
                todpython_toint(PyTuple_GET_ITEM(value, 2)),
                todpython_toint(PyTuple_GET_ITEM(value, 3)));
            ap->set(object, v);
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'Color\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<Format>::check(prop->getType()))
    {
        if (PyString_Check(value))
        {
            typedef SimpleProperty<const Format&> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->fromString(object, String("%s", PyString_AsString(value)).c_str());
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'Format\'",
                value->ob_type->tp_name);
            return -1;
        }
    }

    return 0;
}


//-----------------------------------------------------------------------------
PyObject* invoke_method
(Object* object, PyObject* attr_name, const Path& path,
 PyObject* args, PyObject* keys)
{
    class Guard
    {
    public:
        Guard(PyObject* o):o_(o) {}
        ~Guard() {Py_DECREF(o_);}
        PyObject* get() {return o_;}
    protected:
        PyObject* o_;
    };
    Guard argGuard(attr_name);

    // convert method name
    char* method_name = PyString_AsString(argGuard.get());
    if (0 == method_name)
        return PyErr_Format(PyExc_Exception,
        "\'%s\' object has no method \'%s\'", method_name);

    // find method
    Method* method = object->getType().
        findMethod(String("%s", method_name).c_str());
    if (0 == method)
        return PyErr_Format(PyExc_Exception,
            "\'%s\' object has no method \'%s\'",
            path.toAnsiString().c_str(), method_name);

    // make input parameter
    index_t num_args = static_cast<index_t>(PyTuple_Size(args));
    Parameter* param = method->getParameter();
    if (num_args != param->in()->size())
        return PyErr_Format(PyExc_TypeError,
            "%s() takes exactly %d argument (%d given)",
            method_name, param->in()->size(), num_args);
    if (!build_input_paramter(param->in(), args, method_name))
        return 0;

    // invoke method
    method->invoke(object);

    // make output parameter
    if (method->getParameter()->out()->isForceList())
    {
        PyObject* result = PyTuple_New(param->out()->size());
        for (index_t a = 0; a < param->out()->size(); ++a)
        {
            PyTuple_SET_ITEM(result, a, build_value(param->out()->get(a)));
        }
        return result;
    }
    else
    {
        switch (param->out()->size())
        {
            // parameter size == 0
        case 0:
            Py_INCREF(Py_None);
            return Py_None;
            // parameter size == 1
        case 1:
            return build_value(param->out()->get(0));
            // parameter size > 1
        default:
            {
                PyObject* result = PyTuple_New(param->out()->size());
                for (index_t a = 0; a < param->out()->size(); ++a)
                {
                    PyTuple_SET_ITEM(result, a, build_value(param->out()->get(a)));
                }
                return result;
            }
        }
    }

    Py_INCREF(Py_None);
    return Py_None;
}
