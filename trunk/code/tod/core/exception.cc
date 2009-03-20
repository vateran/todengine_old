#include "tod/core/exception.h"

using namespace tod;

//-----------------------------------------------------------------------------
Exception::Exception
(int error_code, int line, const String& file,
 const String& function, const String& description):
errorCode_(error_code), line_(line), file_(file),
function_(function), description_(description)
{
    // empty
}


//-----------------------------------------------------------------------------
void Exception::setErrorCode(int error_code)
{
    errorCode_ = error_code;
}


//-----------------------------------------------------------------------------
void Exception::setLine(int line)
{
    line_ = line_;
}


//-----------------------------------------------------------------------------
void Exception::setFile(const String& file)
{
    file_ = file;
}


//-----------------------------------------------------------------------------
void Exception::setFunction(const String& function)
{
    function_ = function;
}


//-----------------------------------------------------------------------------
void Exception::setDescription(const String& description)
{
    description_ = description;
}


//-----------------------------------------------------------------------------
int Exception::getErrorCode() const
{
    return errorCode_;
}


//-----------------------------------------------------------------------------
int Exception::getLine() const
{
    return line_;
}


//-----------------------------------------------------------------------------
const String& Exception::getFile() const
{
    return file_;
}


//-----------------------------------------------------------------------------
const String& Exception::getFunction() const
{
    return function_;
}


//-----------------------------------------------------------------------------
const String& Exception::getDescription() const
{
    return description_;
}


//-----------------------------------------------------------------------------
String Exception::getFullDescription() const
{
    return String("%s(%d : Exception(%d):%s: %s)",
        file_.c_str(), line_, errorCode_,
        function_.c_str(), description_.c_str());
}

//-----------------------------------------------------------------------------
void ThrowExceptionHandler::handle(const Exception& e)
{
    throw e;
}

//-----------------------------------------------------------------------------
void MessageBoxExceptionHandler::handle(const Exception& e)
{
    String s("%s(%d :\n\nException(%d):%s:\n%s)",
        e.getFile().c_str(), e.getLine(), e.getErrorCode(),
        e.getFunction().c_str(), e.getDescription().c_str());

#ifdef __WIN32__
    MessageBoxA(0, s, "TodEngine Exception", MB_OK);
#else
	NSRunAlertPanel(@"TodEngine Exception", s.c_str(), @"Ok", nil, nil);
#endif
}