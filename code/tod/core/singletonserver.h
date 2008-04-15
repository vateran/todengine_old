#ifndef TOD_CORE_UTILITY_SINGLETONSERVER_H
#define TOD_CORE_UTILITY_SINGLETONSERVER_H
/**
    @ingroup TodCoreUtility
    @class tod::core::SingletonServer
    @brief 
*/

#include <list>

namespace tod
{
namespace core
{
    class SingletonBase;
    class SingletonServer
    {
    public:
        SingletonServer();
        ~SingletonServer();

        void clear();

        void registerSingleton(SingletonBase* singleton);
        void unregisterSingleton(SingletonBase* singleton);

    public:
        static SingletonServer* instance();
        static SingletonServer s_instance_;

    private:
        typedef std::list<SingletonBase*> Singletons;

    private:
        Singletons singletons_;
    };
}
}

#endif // TOD_CORE_UTILITY_SINGLETONSERVER_H
