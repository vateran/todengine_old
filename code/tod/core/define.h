#ifndef TOD_CORE_BASE_DEFINE_H
#define TOD_CORE_BASE_DEFINE_H

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN

#pragma warning(disable:4311)
#pragma warning(disable:4267)
#pragma warning(disable:4819)
#pragma warning(disable:4995)

#define tod_sleep(t) Sleep(t);

#endif

#define IN
#define OUT
#define INOUT

#ifdef UNICODE
#define TOD_UNICODE
#define STRING(s) L##s
#define WIDEN(x) STRING(x)
#define tod_printf wprintf
#define tod_snprintf StringCchPrintfW
#define tod_strlen wcslen
#define tod_mkdir _wmkdir
#define tod_strcmp wcscmp
#define tod_strncmp wcsncmp
#define tod_stricmp _wcsicmp
#define tod_atoi _wtoi
#define tod_atof _wtof
#define tod_atoi64 _wtoi64
#define tod_vscprintf _vscwprintf
#define tod_vsprintf vswprintf_s

#define ___FILE___      WIDEN(__FILE__)
#define ___FUNCSIG___   WIDEN(__FUNCSIG__)
#define ___FUNCTION___  WIDEN(__FUNCTION__)
#define ___LINE___      __LINE__
#define ___DATE___      WIDEN(__DATE__)
#define ___TIME___      WIDEN(__TIME__)

#else
#define STRING(s) s
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

#define ___FILE___ __FILE__
#define ___FUNCSIG___ __FUNCSIG__
#define ___FUNCTION___ __FUNCTION__
#define ___LINE___  __LINE__
#define ___DATE___  __DATE__
#define ___TIME___  __TIME__

#endif

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

