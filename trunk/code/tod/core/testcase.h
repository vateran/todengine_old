#ifndef TOD_CORE_UTILITY_UNITTEST_TESTCASE_H
#define TOD_CORE_UTILITY_UNITTEST_TESTCASE_H
/**
    @ingroup TodCoreUnitTest
    @class tod::unittest::TestCase
    @brief 
*/

#include <list>
#include "tod/core/define.h"
#include "tod/core/string.h"
#include "tod/core/currentsnapshot.h"
#include "tod/core/testcallerbase.h"

namespace tod
{
    class TestCaseBase
    {
    public:
        struct Error
        {
            TestCallerBase* testCaller_;
            CurrentSnapShot snapShot_;
        };
        typedef std::list<Error> Errors;

    public:
        virtual~TestCaseBase() {}

        virtual void initialize() {}
        virtual void finalize() {}
        virtual void run() {}

        virtual void terminate()=0;
        virtual const char_t* toString() const=0;
        virtual int getNumTests() const=0;
        Errors& getErrors();

    protected:
        Errors errors_;
    };

    template <typename T>
    class TestCase : public TestCaseBase
    {
    public:
        typedef void (T::*TestMethod)();

    public:
        virtual~TestCase();

        void run();

        override void terminate();
        override int getNumTests() const;

    private:
        typedef std::list<TestCallerBase*> TestCallers;

    protected:
        TestCallers testCallers_;
    };

#include "tod/core/testcase.inl"

#define TODUNIT_ASSERT(e) do { if (!(e)) { \
    throw CurrentSnapShot(STRING("assert"),\
    ___DATE___, ___TIME___, ___FILE___, ___FUNCTION___,\
    ___FUNCTION___, ___LINE___, STRING(#e));\
    } } while (0);

}

#endif // TOD_CORE_UTILITY_UNITTEST_TESTCASE_H
