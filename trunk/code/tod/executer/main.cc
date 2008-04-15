#include <windows.h>
#include "tod/core/module.h"
#include "tod/core/kernel.h"
#include "tod/core/resourcemanager.h"

#pragma comment(linker, "\"/manifestdependency:type='WIN32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='X86' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace tod;
using namespace tod::core;

INCLUDE_MODULE(Engine);
INCLUDE_MODULE(D3D9Graphics);

class __declspec(dllimport) Test
{
public:
    void test();
};

//-----------------------------------------------------------------------------
int APIENTRY WinMain
(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance,
 __in_opt LPSTR  lpCmdLine, __in int nShowCmd)
{
    //_CrtSetDbgFlag (_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF );
    //_CrtSetBreakAlloc(428);

    USING_MODULE(Engine);
    USING_MODULE(D3D9Graphics);

    ResourceManager::instance()->initialize(STRING("data"));

    return 0;
}
