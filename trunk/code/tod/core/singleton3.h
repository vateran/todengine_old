#ifndef TOD_CORE_UTILITY_SINGLETON3_H
#define TOD_CORE_UTILITY_SINGLETON3_H
/**
    @ingroup TodCoreUtility
    @class tod::Singleton3
    @brief 
*/

#include "tod/core/assert.h"
#include "tod/core/path.h"
#include "tod/core/kernel.h"
#include "tod/core/singleton.h"
#include "tod/core/singletonbase.h"

namespace tod
{
    template <typename T>
    class Singleton3 : public SingletonBase
    {
    public:
        Singleton3();
        virtual~Singleton3();

        override int addRefSingleton();
        override int releaseSingleton();
        override int getRefSingleton() const;

        static void setSingletonPath(const Path& path);

        static T* instance();
        static bool isInitialized();

    private:
        static Path s_path;
        static T* s_instance;
    };

#include "tod/core/singleton3.inl"

}

#endif // TOD_CORE_UTILITY_SINGLETON3_H
