#ifndef TOD_CORE_BASE_TYPEID_H
#define TOD_CORE_BASE_TYPEID_H
/**
    @ingroup TodCoreBase
    @class tod::TypeId
    @brief 
*/

#include "tod/core/primitivetype.h"

namespace tod
{
    template <typename T>
    class TypeId
    {
    public:
        typedef TypeId<T> type;

    public:
        static type_id id()
        {
            return reinterpret_cast<int>(typeid(T).raw_name());
        }
        static bool check(type_id _id)
        {
            return id() == _id;
        }
        static bool check(const type& rhs)
        {
            return check(rhs.id());
        }
    };
}

#endif // TOD_CORE_BASE_TYPEID_H
