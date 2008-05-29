#ifndef TOD_CORE_KERNEL_MODULE_H
#define TOD_CORE_KERNEL_MODULE_H
/**
    @ingroup TodCoreKernel
    @class tod::core::Module
    @brief 
*/

#include <map>
#include "tod/core/primitivetype.h"
#include "tod/core/name.h"

namespace tod
{
namespace core
{
    class Type;
    class Object;
    class Module
    {
    public:
        typedef std::map<Name, const Type*> Types;
        typedef void (*InitializeModuleFunc)(Module*);
        typedef void (*FinalizeModuleFunc)(Module*);

    public:
        Module(
            const name_t* name,
            InitializeModuleFunc init_func,
            FinalizeModuleFunc fin_func);
        virtual~Module();

        virtual void initialize();
        virtual void finalize();
        
        Object* create(const Name& type_name);

        void addType(const name_t* type_name, Type* type);

        const Name& getName() const;

        Types::iterator firstType();
        Types::iterator lastType();
        Types::const_iterator firstType() const;
        Types::const_iterator lastType() const;

    private:
        /// Module's name
        Name name_;
        /// Types
        Types types_;
        /// Initialize Module Function Pointer
        InitializeModuleFunc initializeModuleFunc_;
        /// Finalize Module Function Pointer
        FinalizeModuleFunc finalizeModuleFunc_;
    };

#include "tod/core/module.inl"

/// Register Type macro
#define REGISTER_TYPE(m, cls) m->addType(STRING(#cls), &cls::TYPE);
/// Declare Module macro
#define DECLARE_MODULE(name) \
    extern "C" void Use##name##Module()\
    {\
        static Module s_##name##_module(\
        STRING(#name), initialize_##name, finalize_##name);\
        tod::core::Kernel::instance()->addModule(&s_##name##_module);\
    }
/// Include Moudle macro
#define INCLUDE_MODULE(name) extern "C" void Use##name##Module();
/// Using Moudle macro
#define USING_MODULE(name) Use##name##Module();

}
}

#endif // TOD_CORE_KERNEL_MODULE_H
