#include "tod/core/path.h"

using namespace tod;

//-----------------------------------------------------------------------------
Path::Path():
tokenizer_(String::begin(), String::begin(), s_seperator)
{
    // empty
}


//-----------------------------------------------------------------------------
Path::Path(const char_t* path):
String(path), tokenizer_(String::begin(), String::end(), s_seperator)
{
    // empty
}


//-----------------------------------------------------------------------------
Path::Path(const widechar_t* path):
String(path), tokenizer_(String::begin(), String::end(), s_seperator)
{
    // empty
}


//-----------------------------------------------------------------------------
Path::Path(const Path& path):
String(path), tokenizer_(String::begin(), String::end(), s_seperator)
{
    // empty
}


//-----------------------------------------------------------------------------
Path::Path(const String& path):
String(path), tokenizer_(String::begin(), String::end(), s_seperator)
{
    // empty
}


//-----------------------------------------------------------------------------
boost::char_separator<char_t> Path::s_seperator("/");
