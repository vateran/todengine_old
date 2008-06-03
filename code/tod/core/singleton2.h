#ifndef TOD_CORE_UTILITY_SINGLETON2_H
#define TOD_CORE_UTILITY_SINGLETON2_H
/**
    @ingroup TodCoreUtility
    @class tod::Singleton2
    @brief 
*/

namespace tod
{
    template <typename T>
    class Singleton2
    {
    public:
        Singleton2();
        virtual~Singleton2();

        static T* instance();
        static bool isInitialized();

    private:
        static T* s_instance;
    };

#include "tod/core/singleton2.inl"

}

#endif // TOD_CORE_UTILITY_SINGLETON2_H
