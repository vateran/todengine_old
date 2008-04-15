#ifndef TOD_ENGINETEST_TIMETESTCASE_H
#define TOD_ENGINETEST_TIMETESTCASE_H

#include "tod/core/unittest.h"

class TimeTestCase : public tod::core::unittest::TestCase<TimeTestCase>
{
public:
    TODUNIT_BEGINE_TESTSUITE(TimeTestCase)
        TODUNIT_TEST(test_TimeServer);
        TODUNIT_TEST(test_StopWatch);
    TODUNIT_END_TESTSUITE()

    void test_TimeServer();
    void test_StopWatch();
};

#endif // TOD_ENGINETEST_TIMETESTCASE_H
