#ifndef TOD_CORE_BASE_PLATFORM_H
#define TOD_CORE_BASE_PLATFORM_H

#ifdef __WIN32__
#undef __WIN32__
#endif

#ifdef _WIN32
#define __WIN32__
//#pragma message("TodEngine detected WIN32 platform")
#endif

#endif // TOD_CORE_BASE_PLATFORM_H
