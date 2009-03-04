#ifndef TOD_CORE_UTILITY_SINGLETONBASE_H
#define TOD_CORE_UTILITY_SINGLETONBASE_H
/**
    @ingroup TodCoreUtility
    @class tod::SingletonBase
    @brief 
*/

#include "tod/core/singletonserver.h"

namespace tod
{
    class SingletonBase
    {
    public:
        SingletonBase():refCount_(0) {}
        virtual~SingletonBase() {}

        virtual int addRefSingleton();
        virtual int releaseSingleton();
        virtual int getRefSingleton() const;

    protected:
        int refCount_;
    };

#include "tod/core/singletonbase.inl"

}

#endif // TOD_CORE_UTILITY_SINGLETONBASE_H
