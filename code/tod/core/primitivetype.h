#ifndef TOD_CORE_TYPE_PRIMITIVETYPE_H
#define TOD_CORE_TYPE_PRIMITIVETYPE_H

#include <vector>
#include "tod/core/tuple3.h"
#include "tod/core/tuple4.h"

namespace tod
{
namespace core
{
#ifdef UNICODE
    typedef wchar_t char_t;
#else
    typedef char char_t;
#endif // UNICODE

    typedef char buffer_t;
    typedef std::vector<char> dynamic_buffer_t;

    typedef char_t typename_t;
    typedef char_t name_t;
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

    typedef const char* type_id;
}
}

#endif // TOD_CORE_TYPE_PRIMITIVETYPE_H
