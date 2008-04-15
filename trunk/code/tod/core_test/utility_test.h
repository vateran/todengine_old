#ifndef TOD_CORETEST_UTILITYTESTCASE_H
#define TOD_CORETEST_UTILITYTESTCASE_H

#include "tod/core/unittest.h"

class UtilityTestCase : public tod::core::unittest::TestCase<UtilityTestCase>
{
public:
    TODUNIT_BEGINE_TESTSUITE(UtilityTestCase)
        TODUNIT_TEST(test_String);
        TODUNIT_TEST(test_Enumeration);
    TODUNIT_END_TESTSUITE()

    void test_String();
    void test_Enumeration();
};

#endif // TOD_CORETEST_UTILITYTESTCASE_H
