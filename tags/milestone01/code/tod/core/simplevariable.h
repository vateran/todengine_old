#ifndef TOD_CORE_OBJECT_SIMPLEVARIABLE_H
#define TOD_CORE_OBJECT_SIMPLEVARIABLE_H
/**
    @ingroup TodCoreObject
    @class tod::SimpleVariable
    @brief
*/

#include "tod/core/define.h"
#include "tod/core/variable.h"
#include "tod/core/typeid.h"

namespace tod
{
    template <typename T>
    class SimpleVariable : public Variable
    {
    public:
        typedef SimpleVariable<T> type;

    public:
        override Variable* clone();
        override type_id getType() const;

        T& get();
        const T& get() const;

        type& operator = (const T& v);
        operator T ();

    public:
        T data_;
    };

#include "tod/core/simplevariable.inl"

}

#endif // TOD_CORE_OBJECT_SIMPLEVARIABLE_H
