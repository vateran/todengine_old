#ifndef TOD_CORE_UTILITY_SINGLETON3_H
#define TOD_CORE_UTILITY_SINGLETON3_H
/**
    @ingroup TodCoreUtility
    @class tod::core::Singleton3
    @brief 
*/

#include "tod/core/assert.h"
#include "tod/core/path.h"
#include "tod/core/kernel.h"

namespace tod
{
namespace core
{
    template <typename T>
    class Singleton3
    {
    public:
        Singleton3();
        virtual~Singleton3();

        static void setSingletonPath(const Path& path);

        static T* instance();
        static bool isInitialized();

    private:
        static Path s_path;
        static T* s_instance;
    };

#include "tod/core/singleton3.inl"

}
}

#endif // TOD_CORE_UTILITY_SINGLETON3_H
