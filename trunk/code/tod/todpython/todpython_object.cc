#include "tod/todpython/todpython_extension.h"

#include "tod/core/typeid.h"

using namespace tod;

//-----------------------------------------------------------------------------
PyObject* TodObject_new(PyTypeObject* type, PyObject* args, PyObject* keys)
{
    TodObject* o = reinterpret_cast<TodObject*>(type->tp_alloc(type, 0));
    return reinterpret_cast<PyObject*>(o);
}


//-----------------------------------------------------------------------------
void TodObject_dealloc(PyObject* self)
{
    TodObject* o = reinterpret_cast<TodObject*>(self);
    delete o->object_;
    self->ob_type->tp_free(self);
}


//-----------------------------------------------------------------------------
PyObject* TodObject_getattro(TodObject* self, PyObject* name)
{
    self->attrName_ = name;
    Py_INCREF(self);
    Py_INCREF(name);
    return (PyObject*)(self);
}


//-----------------------------------------------------------------------------
PyObject* TodObject_call(PyObject* self, PyObject* args, PyObject* keys)
{
    TodObject* o = reinterpret_cast<TodObject*>(self);
    if (0 == o->object_)
        return PyErr_Format(PyExc_Exception, "invalid TodObject");
    return invoke_method(o->object_, o->attrName_, STRING(""), args, keys);
}


//-----------------------------------------------------------------------------
int TodObject_setattro(TodObject* self, PyObject* name, PyObject* value)
{
    if (self->object_)
    {
        set_property(self->object_, STRING(""), name, value);
    }
    return 0;
}



//-----------------------------------------------------------------------------
PyTypeObject TodObjectType =
{
    PyObject_HEAD_INIT(0)
    0,                                      // ob_size
    "TodObject",                            // tp_name
    sizeof(TodObject),                      // tp_basicssize
    0,                                      // tp_itemsize
    TodObject_dealloc,                      // tp_dealloc
    0,                                      // tp_print
    (getattrfunc)0,                         // tp_getattr
    (setattrfunc)0,                         // tp_setattr
    0,                                      // tp_compare
    0,                                      // tp_repr
    0,                                      // tp_as_number
    0,                                      // tp_as_mapping
    0,                                      // tp_as_sequence
    0,                                      // tp_as_hash
    (ternaryfunc)TodObject_call,            // tp_call
    0,                                      // tp_str
    (getattrofunc)TodObject_getattro,       // tp_getattro
    (setattrofunc)TodObject_setattro,       // tp_setattro
    0,                                      // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                     // tp_flags
    "TodPython Object",                     // tp_doc
    0,                                      // tp_traverse
    0,                                      // tp_clear
    0,                                      // tp_richcompare
    0,                                      // tp_weaklistoffset
    0,                                      // tp_iter
    0,                                      // tp_iternext
    0,                                      // tp_methods,
    0,                                      // tp_members
    0,                                      // tp_getset
    0,                                      // tp_base
    0,                                      // tp_dict
    0,                                      // tp_descr_get
    0,                                      // tp_descr_set
    0,                                      // tp_dictoffset
    0,                                      // tp_init
    0,                                      // tp_alloc
    TodObject_new,                          // tp_new
};
