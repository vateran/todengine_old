#ifndef TOD_CORE_OBJECT_METHOD_H
#define TOD_CORE_OBJECT_METHOD_H
/**
    @ingroup TodCoreObject
    @class tod::core::Method
    @brief 
*/

#include "external/boost/tokenizer.hpp"
#include "tod/core/primitivetype.h"
#include "tod/core/string.h"
#include "tod/core/name.h"
#include "tod/core/parameter.h"

namespace tod
{
namespace core
{
    class Object;
    class ReturnValue;
    class Method
    {
    public:
        Method();
        virtual~Method();

        virtual void invoke(Object* self)=0;

        const Name& getName();
        Parameter* getParameter();

        void setPrototype(const char_t* proto);
        const String& getPrototype() const;

    private:
        void build_paramter(const String& s, Variables* v);

    private:
        String prototype_;
        Name name_;
        Parameter parameter_;
    };

#include "tod/core/method.inl"

}
}

#endif // TOD_CORE_OBJECT_METHOD_H
