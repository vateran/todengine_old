#include "tod/core/string.h"

#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>

using namespace tod;

//-----------------------------------------------------------------------------
String::String(const char* s, ...)
{
    va_list args;
    va_start(args, s);
    format(s, args);
}


//-----------------------------------------------------------------------------
String::String(const char_t* s, ...)
{
    va_list args;
    va_start(args, s);
    format(s, args);
}


//-----------------------------------------------------------------------------
void String::format(const char* s, ...)
{
    va_list args;
    va_start(args, s);
    format(s, args);
}


//-----------------------------------------------------------------------------
void String::format(const char* s, va_list args)
{
#if defined(UNICODE)
    int len = _vscprintf(s, args) + 1;
    std::vector<char> temp;
    temp.resize(len);    
    vsprintf_s(&temp[0], len, s, args);
    if (len > 0)
    {
        --len;
        temp.resize(len);
    }
    resize(len);
    MultiByteToWideChar(CP_ACP, 0, &temp[0], len, &(*this)[0], len);
#else

#endif
}


//-----------------------------------------------------------------------------
void String::format(const char_t* s, ...)
{
    va_list args;
    va_start(args, s);
    format(s, args);
}


//-----------------------------------------------------------------------------
void String::format(const char_t* s, va_list args)
{
    int len = tod_vscprintf(s, args) + 1;
    resize(len);
    tod_vsprintf(&(*this)[0], len, s, args);
    if (len > 0)
        resize(len - 1);
}


//-----------------------------------------------------------------------------
int String::toInt() const
{
    return tod_atoi(c_str());
}


//-----------------------------------------------------------------------------
float String::toFloat() const
{
    return static_cast<float>(tod_atof(c_str()));
}


//-----------------------------------------------------------------------------
double String::toDouble() const
{
    return tod_atof(c_str());
}


//-----------------------------------------------------------------------------
std::string String::toAnsiString() const
{
#if defined(UNICODE)
    std::string s;
    int len = static_cast<int>(size()); 
    s.resize(len);
    WideCharToMultiByte(CP_ACP, 0, &(*this)[0], len, &s[0], len, 0, false);
    return s;
#else

#endif
}
