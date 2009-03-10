#ifndef TOD_CORE_UTILITY_UNITTEST_TESTCALLER_H
#define TOD_CORE_UTILITY_UNITTEST_TESTCALLER_H
/**
    @ingroup TodCoreUnitTest
    @class tod::TestCaller
    @brief 
*/

#include "tod/core/testcase.h"
#include "tod/core/testcallerbase.h"

namespace tod
{
    template <typename T>
    class TestCaller : public TestCallerBase
    {
    public:
        typedef typename TestCase<T> MyTestCase;
        typedef typename MyTestCase::TestMethod MyTestMethod;

    public:
        TestCaller(
            MyTestCase* test_case,
            MyTestMethod test_method,
            const char_t* name);
        virtual~TestCaller();

        override void call();
        override const String& getName() const;

    private:
        String name_;
        MyTestCase* testCase_;
        MyTestMethod testMethod_;
    };

#include "tod/core/testcaller.inl"

#define TODUNIT_BEGINE_TESTSUITE(name) typedef name MyTestCase;\
    typedef tod::TestCaller<name> MyTestCaller;\
    void addTest(MyTestCaller* test) { testCallers_.push_back(test); }\
    override const tod::char_t* toString() const { return #name; }\
    name() {

#define TODUNIT_TEST(name) addTest(\
    new MyTestCaller(this, &MyTestCase::name, #name));

#define TODUNIT_END_TESTSUITE() }

}

#endif // TOD_CORE_UTILITY_UNITTEST_TESTCALLER_H
