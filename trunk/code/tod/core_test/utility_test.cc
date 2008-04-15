#include "tod/core_test/utility_test.h"

#include "tod/core/string.h"
#include "tod/core/enumeration.h"

using namespace tod::core;

//-----------------------------------------------------------------------------
void UtilityTestCase::test_String()
{
    String s;
    s.format(STRING("%d %.1f %s"), 3, 0.3, STRING("TEST"));
    TODUNIT_ASSERT(s == STRING("3 0.3 TEST"));
}

//-----------------------------------------------------------------------------
class TestEnum
{
public:
    enum Value
    {
        TESTENUM_1 = 1,
        TESTENUM_2 = 100,
        TESTENUM_3,
        TESTENUM_INVALID = -1,
        TESTENUM_MAX,
    };
};

typedef Enumeration<TestEnum::Value, TestEnum::TESTENUM_MAX, TestEnum::TESTENUM_INVALID> TestEnumeration;
struct TestEnumInitializer : public TestEnumeration
{
    static void initialize()
    {
        add(STRING("TestEnum::TESTENUM_1"), TestEnum::TESTENUM_1);
        add(STRING("TestEnum::TESTENUM_2"), TestEnum::TESTENUM_2);
        add(STRING("TestEnum::TESTENUM_3"), TestEnum::TESTENUM_3);
    }
};

void UtilityTestCase::test_Enumeration()
{
    TestEnumInitializer::initialize();
    TestEnumeration te;

    TODUNIT_ASSERT(sizeof(TestEnumeration) == 4);

    // assign operator
    te = TestEnum::TESTENUM_1;
    TODUNIT_ASSERT(te == TestEnum::TESTENUM_1);
    te = TestEnum::TESTENUM_2;
    TODUNIT_ASSERT(te == TestEnum::TESTENUM_2);

    // copy constructor
    TestEnumeration te2(te);
    TODUNIT_ASSERT(te2 == TestEnum::TESTENUM_2);
    TODUNIT_ASSERT(te == te2);
    TestEnumeration te3(TestEnum::TESTENUM_3);
    TODUNIT_ASSERT(te3 == TestEnum::TESTENUM_3);
    TestEnumeration te4(100);
    TODUNIT_ASSERT(te4 == TestEnum::TESTENUM_2);

    te2 = te3;
    TODUNIT_ASSERT(te2 == TestEnum::TESTENUM_3);

    // from string
    TestEnumeration te5(STRING("TestEnum::TESTENUM_1"));
    TODUNIT_ASSERT(te5 == TestEnum::TESTENUM_1);
    te5 = STRING("TestEnum::TESTENUM_2");
    TODUNIT_ASSERT(te5 == TestEnum::TESTENUM_2);
    te5 = STRING("TestEnum::TESTENUM_4");
    TODUNIT_ASSERT(te5 == TestEnum::TESTENUM_INVALID);

    // to string
    TestEnumeration te6(TestEnum::TESTENUM_1);
    TODUNIT_ASSERT(te6 == STRING("TestEnum::TESTENUM_1"));
    te6 = TestEnum::TESTENUM_2;
    TODUNIT_ASSERT(te6 == STRING("TestEnum::TESTENUM_2"));

    // enumerator
    TestEnum::Value a[] =
    {
        TestEnum::TESTENUM_1,
        TestEnum::TESTENUM_2,
        TestEnum::TESTENUM_3,
    };
    int i = 0;
    for (TestEnumeration::enumerator e = te6.beginEnum();
         e != te6.endEnum(); ++e, ++i)
         TODUNIT_ASSERT(e->first == a[i]);
}
