#include "tod/core/module.h"

#include "tod/core/type.h"
#include "tod/core/object.h"

using namespace tod::core;

//-----------------------------------------------------------------------------
Module::Module
(const name_t* name,
 InitializeModuleFunc init_func, FinalizeModuleFunc fin_func):
name_(name), initializeModuleFunc_(init_func), finalizeModuleFunc_(fin_func)
{
}


//-----------------------------------------------------------------------------
Module::~Module()
{
    finalize();
}

//-----------------------------------------------------------------------------
void Module::initialize()
{
    if (initializeModuleFunc_)
        initializeModuleFunc_(this);
}


//-----------------------------------------------------------------------------
void Module::finalize()
{
    if (finalizeModuleFunc_)
        finalizeModuleFunc_(this);
    types_.clear();
}


//-----------------------------------------------------------------------------
Object* Module::create(const Name& type_name)
{
    Types::iterator find_iter = types_.find(type_name);
    if (types_.end() == find_iter)
        return 0;
    return find_iter->second->create(); 
}


//-----------------------------------------------------------------------------
void Module::addType(const name_t* type_name, Type* type)
{
    types_.insert(Types::value_type(type_name, type));
    if (!type->hasBindedMethod())
        type->bindMethod();
    if (!type->hasBindedProperty())
        type->bindProperty();
}
