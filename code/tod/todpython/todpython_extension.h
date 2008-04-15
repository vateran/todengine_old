#ifndef TOD_TODPYTHON_TODPYTHONFUNC_H
#define TOD_TODPYTHON_TODPYTHONFUNC_H

#include <python.h>
#include "tod/core/ref.h"
#include "tod/core/node.h"

//-----------------------------------------------------------------------------
extern PyObject* build_value(tod::core::Variable* variable);
extern PyObject* build_input_paramter
(tod::core::Variables* v, PyObject* args, const char* method_name);
extern int set_property
(tod::core::Object* object, const tod::core::Path& phat,
 PyObject* name, PyObject* value);
extern PyObject* invoke_method
(tod::core::Object* object, PyObject* attr_name, const tod::core::Path& path,
 PyObject* args, PyObject* keys);

//-----------------------------------------------------------------------------
struct TodObject
{
    PyObject_HEAD
    tod::core::Object* object_;
    PyObject* attrName_;

    TodObject():attrName_(0) {}
};

extern PyTypeObject TodObjectType;

extern PyObject* TodPython_newobject(PyObject* self, PyObject* args);

//-----------------------------------------------------------------------------
struct TodNode
{
    PyObject_HEAD
    tod::core::Ref<tod::core::Node> node_;
    PyObject* attrName_;

    TodNode():attrName_(0) {}
};

typedef std::map<tod::core::Path, TodNode*> TodNodes;

extern PyObject* g_module;
extern TodNodes g_todobjects;
extern PyTypeObject TodNodeType;

extern PyObject* TodPython_resroot(PyObject* self, PyObject* args);
extern PyObject* TodPython_new(PyObject* self, PyObject* args);
extern PyObject* TodPython_get(PyObject* self, PyObject* args);
extern PyObject* TodPython_delete(PyObject* self, PyObject* args);
extern PyObject* TodPython_ls(PyObject* self, PyObject* args);
extern PyObject* TodPython_pushCwn(PyObject* self, PyObject* args);
extern PyObject* TodPython_popCwn(PyObject* self, PyObject* args);
extern PyObject* TodPython_todprint(PyObject* self, PyObject* args);
extern PyObject* TodPython_exit(PyObject* self, PyObject* args);

#endif // TOD_TODPYTHON_TODPYTHONFUNC_H
