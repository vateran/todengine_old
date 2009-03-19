#ifndef TOD_CORE_KERNEL_MODULE_H
#define TOD_CORE_KERNEL_MODULE_H
/**
    @ingroup TodCoreKernel
    @class tod::Module
    @brief 
*/

#include <map>
#include "tod/core/primitivetype.h"
#include "tod/core/string.h"

namespace tod
{
    class Type;
    class Object;
    class Kernel;
    class Module
    {
    public:
        typedef std::map<String, const Type*> Types;
        typedef void (*InitializeModuleFunc)(Module*);
        typedef void (*FinalizeModuleFunc)(Module*);

    public:
        Module(
            const String& name,
            InitializeModuleFunc init_func,
            FinalizeModuleFunc fin_func);
        virtual~Module();

        virtual void initialize();
        virtual void finalize();
        
        Object* create(const String& type_name);

        void addType(Kernel* kernel, const String& type_name, Type* type);

        const String& getName() const;
        size_t getNumTypes() const;

        Types::iterator firstType();
        Types::iterator lastType();
        Types::const_iterator firstType() const;
        Types::const_iterator lastType() const;        

    private:
        /// Module's name
        String name_;
        /// Types
        Types types_;
        /// Initialize Module Function Pointer
        InitializeModuleFunc initializeModuleFunc_;
        /// Finalize Module Function Pointer
        FinalizeModuleFunc finalizeModuleFunc_;
    };

#include "tod/core/module.inl"

/// Register Type macro
#define REGISTER_TYPE(m, cls) m->addType(\
    tod::Kernel::instance(), #cls, &cls::TYPE);
/// Declare Module macro
#define DECLARE_MODULE(name) \
    extern "C" void Use##name##Module()\
    {\
        static Module s_##name##_module(\
        #name, initialize_##name, finalize_##name);\
        tod::Kernel::instance()->addModule(&s_##name##_module);\
    }
/// Include Moudle macro
#define INCLUDE_MODULE(name) extern "C" void Use##name##Module();
/// Using Moudle macro
#define USING_MODULE(name) Use##name##Module();

}

#endif // TOD_CORE_KERNEL_MODULE_H
