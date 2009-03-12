#include "tod/core/string.h"

#include <stdio.h>
#include <stdarg.h>

using namespace tod;

//-----------------------------------------------------------------------------
String::String(const std::wstring& s)
{
    resize(s.length());
    encoding((char*)s.c_str(), s.length() * 2, &data_[0], s.length());
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
    va_list args;
    va_start(args, s);
    format(s, args);
}


//-----------------------------------------------------------------------------
void String::format(const widechar_t* s, va_list args)
{
    std::wstring temp;
    int len;

#ifdef __WIN32__
    len = _vscwprintf(s, args) + 1;
    temp.resize(len);
    vswprintf_s(&temp[0], len, s, args);
#else
#endif

    if (len > 0)
        temp.resize(len - 1);
    len = temp.length();

    resize(len);
    encoding((char*)temp.c_str(), len * 2, &data_[0], len);
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
String::operator int ()
{
    return tod_atoi(c_str());
}


//-----------------------------------------------------------------------------
String::operator unsigned int ()
{
    return tod_atoi(c_str());
}


//-----------------------------------------------------------------------------
String::operator const unsigned int () const
{
    return tod_atoi(c_str());
}

//-----------------------------------------------------------------------------
String::operator const int () const
{
    return tod_atoi(c_str());
}


//-----------------------------------------------------------------------------
String::operator int64_t ()
{
    return tod_atoi64(c_str());
}


//-----------------------------------------------------------------------------
String::operator const int64_t () const
{
    return tod_atoi64(c_str());
}


//-----------------------------------------------------------------------------
String::operator uint64_t ()
{
    return tod_atoi64(c_str());
}


//-----------------------------------------------------------------------------
String::operator const uint64_t () const
{
    return tod_atoi64(c_str());
}


//-----------------------------------------------------------------------------
String::operator float ()
{
    return static_cast<float>(tod_atof(c_str()));
}


//-----------------------------------------------------------------------------
String::operator const float () const
{
    return static_cast<float>(tod_atof(c_str()));
}


//-----------------------------------------------------------------------------
String::operator double ()
{
    return tod_atof(c_str());
}


//-----------------------------------------------------------------------------
String::operator const double () const
{
    return tod_atof(c_str());
}


//-----------------------------------------------------------------------------
String::operator const widechar_t* () const
{
    return (widechar_t*)data_.c_str();
}


//-----------------------------------------------------------------------------
void String::initializeEncoding()
{
    encodingHandle_ = iconv_open("", "WCHAR_T");
}


//-----------------------------------------------------------------------------
void String::finalizeEncoding()
{
    iconv_close(encodingHandle_);
}


//-----------------------------------------------------------------------------
void String::encoding
(const char* src, size_t src_len, char* dest, size_t dest_len)
{
    iconv(encodingHandle_, &src, &src_len, &dest, &dest_len);
}


//-----------------------------------------------------------------------------
iconv_t String::encodingHandle_ = 0;
