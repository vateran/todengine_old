#ifndef TOD_CORE_BASE_DEFINE_H
#define TOD_CORE_BASE_DEFINE_H

#include "tod/core/platform.h"

#ifdef __WIN32__

#pragma warning(disable:4311)
#pragma warning(disable:4267)
#pragma warning(disable:4819)
#pragma warning(disable:4995)

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <MMSystem.h>
#include <commctrl.h>
#include <crtdbg.h>
#include <direct.h>
#include <strsafe.h>

#define tod_sleep(t) Sleep(t);
#define tod_printf printf
#define tod_snprintf StringCchPrintfA
#define tod_strlen strlen
#define tod_mkdir _mkdir
#define tod_strcmp strcmp
#define tod_strncmp strncmp
#define tod_stricmp _stricmp
#define tod_atoi atoi
#define tod_atof atof
#define tod_atoi64 _atoi64
#define tod_vscprintf _vscprintf
#define tod_vsprintf vsprintf_s
#define tod_vsnprintf(buf, bufsize, f, a) vsnprintf_s(buf, bufsize, _TRUNCATE, f, a);
#define tod_getcwd _getcwd
#define tod_chdir _chdir

#else

#define tod_sleep(t)
#define tod_printf printf
#define tod_snprintf snprintf
#define tod_strlen strlen
#define tod_mkdir mkdir
#define tod_strcmp strcmp
#define tod_strncmp strncmp
#define tod_stricmp stricmp
#define tod_atoi atoi
#define tod_atof atof
#define tod_atoi64(s) strtoll(s, 0, 10)
#define tod_vscprintf(f, a) vsnprintf(0, 0, f, a)
#define tod_vsprintf vsprintf
#define tod_vsnprintf vsnprintf
#define tod_getcwd getcwd
#define tod_chdir chdir

#endif  // __WIN32__

#define IN
#define OUT
#define INOUT

#define ___FILE___ __FILE__
#define ___FUNCSIG___ __FUNCSIG__
#define ___FUNCTION___ __FUNCTION__
#define ___LINE___  __LINE__
#define ___DATE___  __DATE__
#define ___TIME___  __TIME__

#define tod_MAKEFOURCC(ch0, ch1, ch2, ch3)\
    ((uint32_t)(uint8_t)(ch0) |\
    ((uint32_t)(uint8_t)(ch1) << 8) |\
    ((uint32_t)(uint8_t)(ch2) << 16) |\
    ((uint32_t)(uint8_t)(ch3) << 24 ))

#define SAFE_DELETE(p) do { if (p) delete p; p = 0; } while (0);
#define SAFE_RELEASE(p) do { if (p) p->Release(); p = 0; } while (0);
#define tod_SAFE_RELEASE(p) do { if (p) p->release(); p = 0; } while (0);

#define override virtual
#define sealed

//-----------------------------------------------------------------------------
template <typename DERIVED, typename BASE>
DERIVED DOWN_CAST(BASE* p)
{
    return dynamic_cast<DERIVED>(p);
}

#endif // TOD_CORE_BASE_DEFINE_H
