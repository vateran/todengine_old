#ifndef TOD_CORE_UTILITY_UNITTEST_TESTSUITE_H
#define TOD_CORE_UTILITY_UNITTEST_TESTSUITE_H
/**
    @ingroup TodCoreUnitTest
    @class tod::core::unittest::TestSuite
    @brief 
*/

#include <list>

namespace tod
{
namespace core
{
namespace unittest
{
    class TestCaseBase;
    class TestSuite
    {
    public:
        virtual~TestSuite();

        template <typename T>
        void addTestCase();
        void run();

    private:
        typedef std::list<TestCaseBase*> TestCases;

    private:
        TestCases testCases_;
    };

#include "tod/core/testsuite.inl"

}
}
}

#endif // TOD_CORE_UTILITY_UNITTEST_TESTSUITE_H
