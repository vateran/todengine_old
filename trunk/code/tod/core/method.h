#ifndef TOD_CORE_OBJECT_METHOD_H
#define TOD_CORE_OBJECT_METHOD_H
/**
    @ingroup TodCoreObject
    @class tod::Method
    @brief 
*/

#include "boost/tokenizer.hpp"
#include "tod/core/primitivetype.h"
#include "tod/core/string.h"
#include "tod/core/name.h"
#include "tod/core/parameter.h"

namespace tod
{
    class Object;
    class ReturnValue;
    class Method
    {
    public:
        Method();
        virtual~Method();

        virtual void invoke(Object* self)=0;

        const String& getName();
        Parameter* getParameter();

        void setPrototype(const String& proto);
        const String& getPrototype() const;

    private:
        void build_paramter(const String& s, Variables* v);

    private:
        String prototype_;
        String name_;
        Parameter parameter_;
    };

#include "tod/core/method.inl"

}

#endif // TOD_CORE_OBJECT_METHOD_H
