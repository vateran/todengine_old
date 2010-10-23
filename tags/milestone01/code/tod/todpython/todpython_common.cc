#include "tod/todpython/todpython_extension.h"

#include "tod/core/color.h"
#include "tod/core/uri.h"
#include "tod/core/simpleproperty.h"
#include "tod/engine/format.h"

using namespace tod;
using namespace tod::engine;

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
PyObject* build_property_to_pyobject(tod::Object* obj, tod::Property* prop)
{
    if (TypeId<bool>::check(prop->getType()))
    {   
        return Py_BuildValue("b",
            reinterpret_cast<SimpleProperty<bool>*>(prop)->get(obj));
    }
    else if (TypeId<short>::check(prop->getType()))
    {   
        return Py_BuildValue("h",
            reinterpret_cast<SimpleProperty<short>*>(prop)->get(obj));
    }
    else if (TypeId<long>::check(prop->getType()))
    {   
        return Py_BuildValue("l",
            reinterpret_cast<SimpleProperty<long>*>(prop)->get(obj));
    }
    else if (TypeId<int>::check(prop->getType()))
    {   
        return Py_BuildValue("i",
            reinterpret_cast<SimpleProperty<int>*>(prop)->get(obj));
    }
    else if (TypeId<int64_t>::check(prop->getType()))
    {
        return Py_BuildValue("L",
            reinterpret_cast<SimpleProperty<int64_t>*>(prop)->get(obj));
    }
    else if (TypeId<float>::check(prop->getType()))
    {
        return Py_BuildValue("f",
            reinterpret_cast<SimpleProperty<float>*>(prop)->get(obj));
    }
    else if (TypeId<double>::check(prop->getType()))
    {
        return Py_BuildValue("d",
            reinterpret_cast<SimpleProperty<double>*>(prop)->get(obj));
    }
    else if (TypeId<const String&>::check(prop->getType()))
    {
        return Py_BuildValue("s",
            reinterpret_cast<SimpleProperty
                <const String&>*>(prop)->get(obj).c_str());
    }
    else if (TypeId<const Uri&>::check(prop->getType()))
    {
        return Py_BuildValue("s",
            reinterpret_cast<SimpleProperty
                <const Uri&>*>(prop)->get(obj).c_str());
    }
    else if (TypeId<const Vector3&>::check(prop->getType()))
    {
        const Vector3* v = &reinterpret_cast<
            SimpleProperty<const Vector3&>*>(prop)->get(obj);
        return Py_BuildValue("(d, d, d)", v->x_, v->y_, v->z_);
    }
    else if (TypeId<const Color&>::check(prop->getType()))
    {
        const Color* c = &reinterpret_cast<
            SimpleProperty<const Color&>*>(prop)->get(obj);
        return Py_BuildValue("(i, i, i, i)", c->r_, c->g_, c->b_, c->a_);
    }
    else if (TypeId<Object*>::check(prop->getType()))
    {
        Object* object = reinterpret_cast<SimpleProperty<Object*>*>(prop)->get(obj);
        if (0 == object)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        TodObject* o = reinterpret_cast<TodObject*>(
            TodObjectType.tp_new(&TodObjectType, 0, 0));
        if (0 == o)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        o->object_ = object;
        o->createdByPython_ = true;
        return reinterpret_cast<PyObject*>(o);
    }
    else if (TypeId<Node*>::check(prop->getType()))
    {
        Node* node = reinterpret_cast<SimpleProperty<Node*>*>(prop)->get(obj);
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
PyObject* build_variable_to_pyobject(Variable* variable)
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
    else if (TypeId<int64_t>::check(variable->getType()))
    {
        return Py_BuildValue("L",
            reinterpret_cast<SimpleVariable<int64_t>*>(variable)->get());
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
            reinterpret_cast<SimpleVariable<String>*>(variable)->get().c_str());
    }
    else if (TypeId<Uri>::check(variable->getType()))
    {
        return Py_BuildValue("s",
            reinterpret_cast<SimpleVariable<Uri>*>(variable)->get().c_str());
    }
    else if (TypeId<Vector3>::check(variable->getType()))
    {
        Vector3* v = &reinterpret_cast<SimpleVariable<Vector3>*>(variable)->get();
        return Py_BuildValue("(d, d, d)", v->x_, v->y_, v->z_);
    }
    else if (TypeId<Color>::check(variable->getType()))
    {
        Color* c = &reinterpret_cast<SimpleVariable<Color>*>(variable)->get();
        return Py_BuildValue("(i, i, i, i)", c->r_, c->g_, c->b_, c->a_);
    }
    else if (TypeId<Object*>::check(variable->getType()))
    {
        Object* object = reinterpret_cast<SimpleVariable<Object*>*>(variable)->get();
        if (0 == object)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        TodObject* o = reinterpret_cast<TodObject*>(
            TodObjectType.tp_new(&TodObjectType, 0, 0));
        if (0 == o)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        o->object_ = object;
        o->createdByPython_ = true;
        return reinterpret_cast<PyObject*>(o);
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
        if (TypeId<bool>::check(v->get(a)->getType()))
        {
            typedef bool type;
            if (PyBool_Check(arg))
            {
                v->get<type>(a) = PyInt_AsLong(arg)?true:false;
                continue;
            }
            else if (PyInt_Check(arg))
            {
                v->get<type>(a) = PyInt_AsLong(arg)?true:false;
                continue;
            }
            else if (PyFloat_Check(arg))
            {
                v->get<type>(a) = PyFloat_AsDouble(arg)?true:false;
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'int\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<int>::check(v->get(a)->getType()))
        {
            typedef int type;
            if (PyInt_Check(arg))
            {
                v->get<type>(a) = PyInt_AsLong(arg);
                continue;
            }
            else if (PyFloat_Check(arg))
            {
                v->get<type>(a) = static_cast<int>(PyFloat_AsDouble(arg));
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'int\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<float>::check(v->get(a)->getType()))
        {
            typedef float type;
            if (PyInt_Check(arg))
            {
                v->get<type>(a) = static_cast<type>(PyInt_AsLong(arg));
                continue;
            }
            else if (PyFloat_Check(arg))
            {
                v->get<type>(a) = static_cast<type>(PyFloat_AsDouble(arg));
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'float\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<String>::check(v->get(a)->getType()))
        {
            if (PyString_Check(arg))
            {
                v->get<String>(a) = String("%s", PyString_AsString(arg));
                continue;
            }
            else if (PyUnicode_Check(arg))
            {
                v->get<String>(a) = String((char_t*)(PyUnicode_AS_DATA(arg)));
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'String\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<Uri>::check(v->get(a)->getType()))
        {
            if (PyString_Check(arg))
            {
                v->get<Uri>(a) = String("%s", PyString_AsString(arg));
                continue;
            }
            else if (PyUnicode_Check(arg))
            {
                v->get<Uri>(a) = String((char_t*)(PyUnicode_AS_DATA(arg)));
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'Uri\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<Vector3>::check(v->get(a)->getType()))
        {
            if (PyTuple_Check(arg))
            {
                Vector3& tv = v->get<Vector3>(a).get();
                if (PyTuple_Size(arg) == 3)
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        float value = 0;
                        PyObject* o = PyTuple_GET_ITEM(arg, i);
                        if (PyInt_Check(o))
                            value = static_cast<float>(PyInt_AsLong(o));
                        else if (PyFloat_Check(o))
                            value = static_cast<float>(PyFloat_AsDouble(o));
                        tv.a_[i] = value;
                    }
                    continue;
                }
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'Vector3\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<Color>::check(v->get(a)->getType()))
        {
            if (PyTuple_Check(arg))
            {
                Color& tc = v->get<Color>(a).get();
                if (PyTuple_Size(arg) == 4)
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        int value = 0;
                        PyObject* o = PyTuple_GET_ITEM(arg, i);
                        if (PyInt_Check(o))
                            value = PyInt_AsLong(o);
                        else if (PyFloat_Check(o))
                            value = static_cast<int>(PyFloat_AsDouble(o));
                        tc.array_[i] = value;
                    }
                    continue;
                }
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'Color\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<Object*>::check(v->get(a)->getType()))
        {
            if (PyObject_TypeCheck(arg, &TodObjectType))
            {
                TodObject* o = reinterpret_cast<TodObject*>(arg);
                v->get<Object*>(a) = o->object_;
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'TodObject\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<Node*>::check(v->get(a)->getType()))
        {
            if (PyObject_TypeCheck(arg, &TodNodeType))
            {
                TodNode* o = reinterpret_cast<TodNode*>(arg);
                v->get<Node*>(a) = *o->node_;
                continue;
            }
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'TodNode\'",
                    method_name, arg->ob_type->tp_name);
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
(tod::Object* object, const Path& path, PyObject* name, PyObject* value)
{
    // find property
    char* prop_name = PyString_AsString(name);
    Property* prop = object->getType()->
        findProperty(String("%s", prop_name).c_str());
    if (0 == prop)
    {
        PyErr_Format(PyExc_AttributeError,
            "\'%s\' object has no property \'%s\'",
            path.c_str(), prop_name);
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
(Object* object, Method* method, PyObject* args, PyObject* keys)
{
    // make input parameter
    index_t num_args = static_cast<index_t>(PyTuple_Size(args));
    Parameter* param = method->getParameter();
    if (num_args != param->in()->size())
        return PyErr_Format(PyExc_TypeError,
            "%s() takes exactly %d argument (%d given)",
                method->getName().c_str(), param->in()->size(), num_args);
    if (!build_input_paramter(param->in(), args, method->getName()))
        return 0;

    // invoke method
    method->invoke(object);

    // make output parameter
    if (method->getParameter()->out()->isForceList())
    {
        PyObject* result = PyTuple_New(param->out()->size());
        for (index_t a = 0; a < param->out()->size(); ++a)
        {
            PyTuple_SET_ITEM(result, a,
                build_variable_to_pyobject(param->out()->get(a)));
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
            return build_variable_to_pyobject(param->out()->get(0));
            // parameter size > 1
        default:
            {
                PyObject* result = PyTuple_New(param->out()->size());
                for (index_t a = 0; a < param->out()->size(); ++a)
                {
                    PyTuple_SET_ITEM(result, a, 
                        build_variable_to_pyobject(param->out()->get(a)));
                }
                return result;
            }
        }
    }
}
