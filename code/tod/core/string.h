#ifndef TOD_CORE_TYPE_STRING_H
#define TOD_CORE_TYPE_STRING_H
/**
    @ingroup TodCoreType
    @class tod::String
    @brief
*/

#include <string>
#include "tod/core/define.h"
#include "tod/core/primitivetype.h"

namespace tod
{
    class String : public std::string
    {
    public:
        String() {}
        String(const std::string& s):std::string(s) {}
        String(const std::wstring& s);
        String(const char* s, ...);
        String(const wchar_t* s, ...);
        String(const String& s, size_type offset, size_type count):
            std::string(s, offset, count) {}
        
        void format(const char* s, ...);
        void format(const char* s, va_list args);

        void format(const wchar_t* s, ...);
        void format(const wchar_t* s, va_list args);
        
        std::string toAnsiString() const;

        /**
            Utilities
        */
        //@{
        int toInt() const;
        float toFloat() const;
        double toDouble() const;
        String extractPath() const;
        void replace(const String& src_str, const String& dst_str);
        //@}
    };
}

#endif // TOD_CORE_TYPE_STRING_H
