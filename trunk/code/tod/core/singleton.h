#ifndef TOD_CORE_UTILITY_SINGLETON_H
#define TOD_CORE_UTILITY_SINGLETON_H
/**
    @ingroup TodCoreUtility
    @class tod::core::Singleton
    @brief 
*/

#include "tod/core/singletonserver.h"

namespace tod
{
namespace core
{
    class SingletonBase
    {
    public:
        SingletonBase() {}
        virtual~SingletonBase() {}
    };

    template <typename T>
    class Singleton : public SingletonBase
    {
    public:
        Singleton();
        virtual~Singleton();

        static T* instance();
        static bool isInitialized();

    private:
        static T* s_instance;
    };

#include "tod/core/singleton.inl"

}
}

#endif // TOD_CORE_UTILITY_SINGLETON_H
