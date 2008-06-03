#ifndef TOD_CORE_UTILITY_CWNGUARD_H
#define TOD_CORE_UTILITY_CWNGUARD_H
/**
    @ingroup TodCoreUtility
    @class tod::CwnGuard
    @brief Current Working Node Guard
*/

#include "tod/core/exception.h"
#include "tod/core/ref.h"
#include "tod/core/kernel.h"

namespace tod
{
    class CwnGuard
    {
    public:
        CwnGuard(Node* node)
        {
            Kernel::instance()->pushCwn(node);
        }
        CwnGuard(const Path& path)
        {
            Node* node = Kernel::instance()->lookup(path);
            if (0 == node)
                TOD_THROW_EXCEPTION(0, String(
                    STRING("\'%s\' not found node in NOH"), path.c_str()));
            Kernel::instance()->pushCwn(node);
        }
        ~CwnGuard()
        {
            Kernel::instance()->popCwn();
        }

    private:
    };

#include "tod/core/cwnguard.inl"

}

#endif // TOD_CORE_UTILITY_CWNGUARD_H
