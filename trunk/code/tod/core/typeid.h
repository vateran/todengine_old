#ifndef TOD_CORE_BASE_TYPEID_H
#define TOD_CORE_BASE_TYPEID_H
/**
    @ingroup TodCoreBase
    @class tod::core::TypeId
    @brief 
*/

#include "tod/core/primitivetype.h"

namespace tod
{
namespace core
{
    template <typename T>
    class TypeId
    {
    public:
        typedef TypeId<T> type;

    public:
        static type_id id()
        {
            int b = typeid(T).before(typeid(T));
            const char* a = typeid(T).raw_name();
            return typeid(T).name();
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
}

#endif // TOD_CORE_BASE_TYPEID_H
