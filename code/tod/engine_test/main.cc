#include <Windows.h>
#include <crtdbg.h>
#include "tod/core/unittest.h"
#include "tod/core/module.h"
#include "tod/core/resourcemanager.h"
#include "tod/engine_test/graphics_test.h"
#include "tod/engine_test/time_test.h"

using namespace tod;

INCLUDE_MODULE(Engine);
INCLUDE_MODULE(D3D9Graphics);

//-----------------------------------------------------------------------------
int APIENTRY WinMain
(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance,
 __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
    _CrtSetDbgFlag (_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF );
    _CrtSetBreakAlloc(156);

    USING_MODULE(Engine);
    USING_MODULE(D3D9Graphics);

    ResourceManager::instance()->initialize("data");

    tod::TestSuite test_suite;
    test_suite.addTestCase<TimeTestCase>();
    test_suite.addTestCase<GraphicsTestCase>();
    test_suite.run();
 
    return 0;
}
