#ifndef TOD_CORE_KERNEL_BUILTINMODULE_H
#define TOD_CORE_KERNEL_BUILTINMODULE_H
/**
    @ingroup TodCoreKernel
    @class tod::BuiltinModule
    @brief 
*/

#include "tod/core/module.h"

namespace tod
{
    class Type;
    class Object;
    class BuiltinModule : public Module
    {
    public:
        BuiltinModule(Kernel* kernel, const char_t* name);
        virtual~BuiltinModule();
    };
}

#endif // TOD_CORE_KERNEL_BUILTINMODULE_H
