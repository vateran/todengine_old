#ifndef TOD_CORE_TYPE_PRIMITIVETYPE_H
#define TOD_CORE_TYPE_PRIMITIVETYPE_H

#include <vector>
#include "tod/core/platform.h"
#include "tod/core/tuple3.h"
#include "tod/core/tuple4.h"

namespace tod
{
#ifdef __WIN32__
    typedef wchar_t widechar_t;
#else
    typedef short widechar_t;
#endif

    typedef char char_t;

    typedef char buffer_t;
    typedef std::vector<char> dynamic_buffer_t;

    typedef char_t typechar_t;    
    typedef char_t path_t;

    typedef char int8_t;
    typedef short int16_t;
    typedef long int32_t;
    typedef __int64 int64_t;
    typedef float float32_t;
    typedef double float64_t;
    typedef float real_t;

    typedef unsigned char uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned long uint32_t;
    typedef unsigned __int64 uint64_t;

    typedef uint32_t index_t;
    typedef uint32_t length_t;

    typedef int type_id;
}

#endif // TOD_CORE_TYPE_PRIMITIVETYPE_H
