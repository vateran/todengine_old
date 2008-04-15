#include "tod/core/resourcemanager.h"

#include "tod/core/define.h"
#include "tod/core/exception.h"
#include "tod/core/fsresourceprotocol.h"

using namespace tod::core;

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
}


//-----------------------------------------------------------------------------
void ResourceManager::finalize()
{
    for (ResourceProtocols::iterator iter = protocols_.begin();
         iter != protocols_.end(); ++iter)
         delete iter->second;
    basePath_.clear();
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
