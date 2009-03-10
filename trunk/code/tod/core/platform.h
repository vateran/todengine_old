#ifndef TOD_CORE_BASE_PLATFORM_H
#define TOD_CORE_BASE_PLATFORM_H

#ifdef __WIN32__
#undef __WIN32__
#endif

#ifdef _WIN32
#define __WIN32__
//#pragma message("TodEngine detected WIN32 platform")

#pragma warning(disable:4311)
#pragma warning(disable:4267)
#pragma warning(disable:4819)
#pragma warning(disable:4995)

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <strsafe.h>

#endif

#endif // TOD_CORE_BASE_PLATFORM_H
