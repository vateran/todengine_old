#ifndef TOD_CORE_TYPE_STRING_H
#define TOD_CORE_TYPE_STRING_H
/**
    @ingroup TodCoreType
    @class tod::core::String
    @brief
*/

#include <string>
#include "tod/core/define.h"
#include "tod/core/primitivetype.h"

namespace tod
{
namespace core
{
#ifdef UNICODE
    class String : public std::wstring
    {
    public:
        String() {}        
        String(const String& s):std::wstring(s) {}
        String(const std::wstring& s):std::wstring(s) {}
        String(const char_t* s, ...);
        String(const char* s, ...);
        String(const String& s, size_type offset, size_type count):
            std::wstring(s, offset, count) {}
        
        void format(const char* s, ...);
        void format(const char* s, va_list args);

        void format(const char_t* s, ...);
        void format(const char_t* s, va_list args);

        int toInt() const;
        float toFloat() const;
        double toDouble() const;
        std::string toAnsiString() const;
    };
#else
    class String : public std::string
    {
    public:
    };
#endif
}
}

#endif // TOD_CORE_TYPE_STRING_H
