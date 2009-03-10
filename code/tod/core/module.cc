#include "tod/core/module.h"

#include "tod/core/kernel.h"
#include "tod/core/type.h"
#include "tod/core/object.h"

using namespace tod;

//-----------------------------------------------------------------------------
Module::Module
(const char_t* name,
 InitializeModuleFunc init_func, FinalizeModuleFunc fin_func):
name_(name), initializeModuleFunc_(init_func), finalizeModuleFunc_(fin_func)
{
    // empty
}


//-----------------------------------------------------------------------------
Module::~Module()
{
    // empty
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
Object* Module::create(const String& type_name)
{
    Types::iterator find_iter = types_.find(type_name);
    if (types_.end() == find_iter)
        return 0;
    return find_iter->second->create(); 
}


//-----------------------------------------------------------------------------
void Module::addType(Kernel* kernel, const char_t* type_name, Type* type)
{
    types_.insert(Types::value_type(type_name, type));
    kernel->addType(type_name, this);
    if (!type->hasBindedMethod())
        type->bindMethod();
    if (!type->hasBindedProperty())
        type->bindProperty();
}
