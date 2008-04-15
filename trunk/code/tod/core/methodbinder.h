#ifndef TOD_CORE_OBJECT_METHODBINDER_H
#define TOD_CORE_OBJECT_METHODBINDER_H
/**
    @ingroup TodCoreObject
    @class tod::core::MethodBinder
    @brief 
*/

#include "tod/core/method.h"

namespace tod
{
namespace core
{
    template <typename T>
    class MethodBinder : public Method
    {
    public:
        typedef void (*BaseBindFunc)(Object*, Parameter*);
        typedef void (*BindFunc)(T*, Parameter*);

    public:
        override void invoke(Object* self);

        void setBindFunc(BindFunc func);
        BindFunc getBindFunc();

    private:
        union
        {
            BaseBindFunc baseBindFunc_;
            BindFunc bindFunc_;
        };
    };

#include "tod/core/methodbinder.inl"

#define BIND_METHOD(name, bind_func) \
    if (!TYPE.hasBindedMethod()) {\
        static MethodBinder<type> s_##name##_method;\
        s_##name##_method.setPrototype(STRING(#name));\
        s_##name##_method.setBindFunc(\
            static_cast<MethodBinder<type>::BindFunc>(bind_func));\
        TYPE.addMethod(&s_##name##_method); }
}
}

#endif // TOD_CORE_OBJECT_METHODBINDER_H
