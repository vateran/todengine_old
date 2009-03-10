#include "tod/core/resourcestorage.h"

#include "tod/core/resourceprotocol.h"

using namespace tod;

IMPLEMENT_CLASS(ResourceStorage, Object);

//-----------------------------------------------------------------------------
ResourceStorage::ResourceStorage():
protocol_(0)
{
}


//-----------------------------------------------------------------------------
ResourceStorage::ResourceStorage(const String& name, ResourceProtocol* rp):
name_(name), protocol_(rp)
{
}


//-----------------------------------------------------------------------------
ResourceStorage::ResourceStorage(const ResourceStorage& rs)
{
    *this = rs;
}


//-----------------------------------------------------------------------------
ResourceStorage::~ResourceStorage()
{
}


//-----------------------------------------------------------------------------
void ResourceStorage::setName(const String& name)
{
    name_ = name;
}


//-----------------------------------------------------------------------------
const String& ResourceStorage::getName() const
{
    return name_;
}


//-----------------------------------------------------------------------------
const ResourceEntries& ResourceStorage::findEntries
(const path_t* path, bool file)
{
    entries_.clear();

    String tpath(name_ + "/" + path);
    tpath.replace("//", "/");
        
    protocol_->findEntries(&entries_, tpath, file);
    return entries_;
}
