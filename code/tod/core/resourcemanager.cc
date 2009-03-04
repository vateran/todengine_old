#include "tod/core/resourcemanager.h"

#include "tod/core/define.h"
#include "tod/core/exception.h"
#include "tod/core/fsresourceprotocol.h"

using namespace tod;

IMPLEMENT_CLASS(ResourceManager, Object);

//-----------------------------------------------------------------------------
ResourceManager::ResourceManager()
{
    // empty
}


//-----------------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
    finalize();
}


//-----------------------------------------------------------------------------
void ResourceManager::initialize(const path_t* base_path)
{
    protocols_.insert(
        ResourceProtocols::value_type(STRING("managed"),
        new FsResourceProtocol()));
    /*protocols_.insert(
        ResourceProtocols::value_type(STRING("file"),
        new FileResourceProtocol()));
    protocols_.insert(
        ResourceProtocols::value_type(STRING("http"),
        new HttpResourceProtocol()));*/
    setBasePath(base_path);

    for (ResourceProtocols::iterator rpi = protocols_.begin();
         rpi != protocols_.end(); ++rpi)
    {
        rpi->second->findStorages(&storages_);
    }
}


//-----------------------------------------------------------------------------
void ResourceManager::finalize()
{
    for (ResourceProtocols::iterator iter = protocols_.begin();
         iter != protocols_.end(); ++iter)
         delete iter->second;
    protocols_.clear();
    for (ResourceStorages::iterator rpi = storages_.begin();
         rpi != storages_.end(); ++rpi)
        delete *rpi;
    protocols_.clear();
    basePath_.clear();
}


//-----------------------------------------------------------------------------
ResourceStorage* ResourceManager::findStorage(const String& name)
{
    for (ResourceStorages::iterator rpi = storages_.begin();
         rpi != storages_.end(); ++rpi)
    {
        if ((*rpi)->getName() == name)
            return *rpi;
    }
    return 0;
}


//-----------------------------------------------------------------------------
ResourceStorages::iterator ResourceManager::firstStorage()
{
    return storages_.begin();
}


//-----------------------------------------------------------------------------
ResourceStorages::iterator ResourceManager::lastStorage()
{
    return storages_.end();
}


//-----------------------------------------------------------------------------
void ResourceManager::setBasePath(const path_t* path)
{
    basePath_ = path;
    for (ResourceProtocols::iterator iter = protocols_.begin();
        iter != protocols_.end(); ++iter)
        iter->second->setBasePath(path);
}


//-----------------------------------------------------------------------------
const String& ResourceManager::getBasePath() const
{
    return basePath_;
}


//-----------------------------------------------------------------------------
ResourceImplementator* ResourceManager::create(const Uri& uri)
{
    ResourceProtocol* protocol = find_protocol(uri.getProtocol());
    if (0 == protocol)
    {
        TOD_THROW_EXCEPTION(
            0, String(STRING("not found protocol \'%s\'"),
                uri.getProtocol().c_str()));
        return 0;
    }
    return protocol->create(uri);
}


//-----------------------------------------------------------------------------
bool ResourceManager::destroy(const Uri& uri)
{
    ResourceProtocol* protocol = find_protocol(uri.getProtocol());
    if (0 == protocol)
        return 0;
    return protocol->destroy(uri);
}    


//-----------------------------------------------------------------------------
ResourceProtocol* ResourceManager::find_protocol(const String& protocol)
{
    ResourceProtocols::iterator find_iter = protocols_.find(protocol);
    if (protocols_.end() == find_iter)
        return 0;
    return find_iter->second;
}
