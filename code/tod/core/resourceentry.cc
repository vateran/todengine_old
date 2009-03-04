#include "tod/core/resourceentry.h"

using namespace tod;

IMPLEMENT_CLASS(ResourceEntry, Object);

//-----------------------------------------------------------------------------
ResourceEntry::ResourceEntry():
file_(false), hidden_(false), protocol_(0)
{
}


//-----------------------------------------------------------------------------
ResourceEntry::ResourceEntry
(const String& name, const String& type, bool file, bool hidden,
 __int64 size, __int64 write_time, ResourceProtocol* rp):
name_(name), type_(type), file_(file), hidden_(false), size_(size),
writeTime_(write_time), protocol_(rp)
{
}


//-----------------------------------------------------------------------------
ResourceEntry::~ResourceEntry()
{
}


//-----------------------------------------------------------------------------
const String& ResourceEntry::getName() const
{
    return name_;
}


//-----------------------------------------------------------------------------
const String& ResourceEntry::getFileType() const
{
    return type_;
}


//-----------------------------------------------------------------------------
bool ResourceEntry::isFile() const
{
    return file_;
}


//-----------------------------------------------------------------------------
bool ResourceEntry::isDirectory() const
{
    return !file_;
}


//-----------------------------------------------------------------------------
bool ResourceEntry::isHidden() const
{
    return hidden_;
}


//-----------------------------------------------------------------------------
__int64 ResourceEntry::getSize() const
{
    return size_;
}


//-----------------------------------------------------------------------------
__int64 ResourceEntry::getWriteTime() const
{
    return writeTime_;
}
