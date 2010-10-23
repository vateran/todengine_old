#ifndef TOD_CORETEST_KERNALTESTCASE_H
#define TOD_CORETEST_KERNALTESTCASE_H

#include "tod/core/unittest.h"

class KernelTestCase : public tod::TestCase<KernelTestCase>
{
public:
    TODUNIT_BEGINE_TESTSUITE(KernelTestCase)
        TODUNIT_TEST(test_Path);
        TODUNIT_TEST(test_CreateObject)
        TODUNIT_TEST(test_Lookup)
    TODUNIT_END_TESTSUITE()

    void test_Path();
    void test_CreateObject();
    void test_Lookup();
};

#endif // TOD_CORETEST_KERNALTESTCASE_H
