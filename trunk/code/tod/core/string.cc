#include "tod/core/string.h"

#include <stdio.h>
#include <stdarg.h>

using namespace tod;

//-----------------------------------------------------------------------------
String::String(const std::wstring& s)
{
/*#ifdef __WIN32__
    int len = static_cast<int>(s.size()); 
    resize(len);
    WideCharToMultiByte(CP_ACP, 0, &s[0], len, &(data_)[0], len, 0, false);
#else

#endif*/
}


//-----------------------------------------------------------------------------
String::String(const char* s, ...)
{
    va_list args;
    va_start(args, s);
    format(s, args);
}


//-----------------------------------------------------------------------------
String::String(const wchar_t* s, ...)
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
    int len = _vscprintf(s, args) + 1;
    resize(len);
    vsprintf_s(&data_[0], len, s, args);
    if (len > 0)
        resize(len - 1);
}


//-----------------------------------------------------------------------------
void String::format(const wchar_t* s, ...)
{
    /*int len = _vscprintf(s, args) + 1;
    std::vector<char> temp;
    temp.resize(len);    
    vsprintf_s(&temp[0], len, s, args);
    if (len > 0)
    {
        --len;
        temp.resize(len);
    }
    resize(len);
    if (len > 0)
        WideCharToMultiByte(CP_ACP, 0, s, len, &data_[0], len, 0, false);*/
}


//-----------------------------------------------------------------------------
void String::format(const wchar_t* s, va_list args)
{
    /*int len = tod_vscprintf(s, args) + 1;
    resize(len);
    tod_vsprintf(&data_[0], len, s, args);
    if (len > 0)
        resize(len - 1);*/
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
String String::extractPath() const
{
    String result;
    size_t p = this->rfind("/", this->size());
    if (-1 == p)
        result = *this;
    else
        result = this->substr(0, p);
    return result;
}


//-----------------------------------------------------------------------------
void String::replace(const String& src_str, const String& dst_str)
{
    size_t b = this->find(src_str);
    size_t s = 0;
    while (b != -1)
    {
        String head(this->substr(s, b));
        String tail(this->substr(b + src_str.size(), -1));
        *this = head + dst_str + tail;

        b = this->find(src_str);
    }
}


//-----------------------------------------------------------------------------
String::operator char_t* ()
{
    return const_cast<char*>(data_.c_str());
}


//-----------------------------------------------------------------------------
String::operator const char_t* () const
{
    return data_.c_str();
}


//-----------------------------------------------------------------------------
String::operator widechar_t* ()
{
    return (widechar_t*)data_.c_str();
}


//-----------------------------------------------------------------------------
String::operator const widechar_t* () const
{
    return (widechar_t*)data_.c_str();
}
