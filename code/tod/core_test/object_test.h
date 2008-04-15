#ifndef TOD_CORETEST_OBJECTTESTCASE_H
#define TOD_CORETEST_OBJECTTESTCASE_H

#include "tod/core/unittest.h"

class ObjectTestCase : public tod::core::unittest::TestCase<ObjectTestCase>
{
public:
    TODUNIT_BEGINE_TESTSUITE(ObjectTestCase)
        TODUNIT_TEST(test_Object)
        TODUNIT_TEST(test_CreateObjectByConcreteType)
        TODUNIT_TEST(test_PrimitiveTypeProperty)
        TODUNIT_TEST(test_CustomPrimitiveTypeProperty)
        TODUNIT_TEST(test_StructTypeProperty)
        TODUNIT_TEST(test_EnumTypeProperty)
        TODUNIT_TEST(test_ListTypeProperty)
        TODUNIT_TEST(test_DictionaryTypeProperty);
        TODUNIT_TEST(test_ReflectionMethod);
        TODUNIT_TEST(test_Node);
        TODUNIT_TEST(test_AbstractNode);
        TODUNIT_TEST(test_LinkNode);
    TODUNIT_END_TESTSUITE()

    void test_Object();
    void test_CreateObjectByConcreteType();
    void test_PrimitiveTypeProperty();
    void test_CustomPrimitiveTypeProperty();
    void test_StructTypeProperty();
    void test_EnumTypeProperty();
    void test_ListTypeProperty();
    void test_DictionaryTypeProperty();
    void test_ReflectionMethod();
    void test_Node();
    void test_AbstractNode();
    void test_LinkNode();
};

#endif // TOD_CORETEST_OBJECTTESTCASE_H
