#ifndef TOD_TODPYTHON_TODPYTHONFUNC_H
#define TOD_TODPYTHON_TODPYTHONFUNC_H

#include <python.h>
#include "tod/core/ref.h"
#include "tod/core/node.h"

//-----------------------------------------------------------------------------
extern PyObject* build_property_to_pyobject
(tod::Object* obj, tod::Property* prop);
extern PyObject* build_variable_to_pyobject(tod::Variable* variable);
extern PyObject* build_input_paramter
(tod::Variables* v, PyObject* args, const char* method_name);
extern int set_property
(tod::Object* object, const tod::Path& phat,
 PyObject* name, PyObject* value);
extern PyObject* invoke_method
(tod::Object* object, tod::Method* method, PyObject* args, PyObject* keys);

//-----------------------------------------------------------------------------
struct TodObject
{
    PyObject_HEAD
    tod::Object* object_;
    tod::Method* method_;
    bool createdByPython_;
    
    TodObject():method_(0), createdByPython_(false) {}
};

extern PyTypeObject TodObjectType;

extern PyObject* TodPython_newobject(PyObject* self, PyObject* args);

//-----------------------------------------------------------------------------
struct TodNode
{
    PyObject_HEAD
    tod::Ref<tod::Node> node_;
    tod::Method* method_;

    TodNode():method_(0) {}
};

typedef std::map<tod::Path, TodNode*> TodNodes;

extern PyObject* g_module;
extern TodNodes g_todobjects;
extern PyTypeObject TodNodeType;

extern PyObject* TodPython_res(PyObject* self, PyObject* args);
extern PyObject* TodPython_new(PyObject* self, PyObject* args);
extern PyObject* TodPython_get(PyObject* self, PyObject* args);
extern PyObject* TodPython_delete(PyObject* self, PyObject* args);
extern PyObject* TodPython_ls(PyObject* self, PyObject* args);
extern PyObject* TodPython_pushCwn(PyObject* self, PyObject* args);
extern PyObject* TodPython_popCwn(PyObject* self, PyObject* args);
extern PyObject* TodPython_todprint(PyObject* self, PyObject* args);
extern PyObject* TodPython_exit(PyObject* self, PyObject* args);
extern PyObject* TodPython_serialize(PyObject* self, PyObject* args);
extern PyObject* TodPython_deserialize(PyObject* self, PyObject* args);
extern PyObject* TodPython_getModuleList(PyObject* self, PyObject* args);
extern PyObject* TodPython_getTypeList(PyObject* self, PyObject* args);

#endif // TOD_TODPYTHON_TODPYTHONFUNC_H
