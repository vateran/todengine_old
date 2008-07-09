#ifndef TOD_CORETEST_RESOURCETESTCASE_H
#define TOD_CORETEST_RESOURCETESTCASE_H

#include "tod/core/unittest.h"

class ResourceTestCase : public tod::TestCase<ResourceTestCase>
{
public:
    TODUNIT_BEGINE_TESTSUITE(ResourceTestCase)
        TODUNIT_TEST(test_Uri_split)
        TODUNIT_TEST(test_ResourceManager_addResource)
        TODUNIT_TEST(test_ResourceManager_removeResource)
        TODUNIT_TEST(test_ResourceManager_findResource)
    TODUNIT_END_TESTSUITE()

    void test_Uri_split();
    void test_ResourceManager_addResource();
    void test_ResourceManager_removeResource();
    void test_ResourceManager_findResource();
};

#endif // TOD_CORETEST_RESOURCETESTCASE_H
