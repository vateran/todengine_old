#ifndef TOD_CORE_UTILITY_UNITTEST_TESTCALLERBASE_H
#define TOD_CORE_UTILITY_UNITTEST_TESTCALLERBASE_H
/**
    @ingroup TodCoreUnitTest
    @class tod::core::unittest::TestCallerBase
    @brief 
*/

#include "tod/core/name.h"

namespace tod
{
namespace core
{
namespace unittest
{
    class TestCallerBase
    {
    public:
        virtual~TestCallerBase() {}

        virtual void call()=0;
        virtual const Name& getName() const=0;
    };
}
}
}

#endif // TOD_CORE_UTILITY_UNITTEST_TESTCALLERBASE_H
