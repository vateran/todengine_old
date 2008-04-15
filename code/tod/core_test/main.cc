#include "tod/core_test/resource_test.h"
#include "tod/core_test/object_test.h"
#include "tod/core_test/utility_test.h"
#include "tod/core_test/kernel_test.h"
#include "tod/core/singletonserver.h"

using namespace tod;
using namespace tod::core;

//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    _CrtSetDbgFlag (_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF );
    //_CrtSetBreakAlloc(428);

    tod::core::unittest::TestSuite test_suite;

    test_suite.addTestCase<ObjectTestCase>();
    test_suite.addTestCase<ResourceTestCase>();
    test_suite.addTestCase<UtilityTestCase>();
    test_suite.addTestCase<KernelTestCase>();
    test_suite.run();

    return 0;
}
