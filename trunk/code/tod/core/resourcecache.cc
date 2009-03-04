#include "tod/core/resourcecache.h"

#include "tod/core/resourceimplementator.h"

using namespace tod;

//-----------------------------------------------------------------------------
ResourceCache::ResourceCache()
{
    // empty
}


//-----------------------------------------------------------------------------
ResourceCache::~ResourceCache()
{
    for (Cache::iterator i = cache_.begin();
         i != cache_.end(); ++i)
         delete i->second;
    cache_.clear();
}


//-----------------------------------------------------------------------------
bool ResourceCache::add(const Uri& uri, ResourceImplementator* ri)
{
    Cache::iterator fi = cache_.find(uri);
    if (cache_.end() != fi)
        return false;
    cache_.insert(Cache::value_type(uri, ri));
    return true;
}


//-----------------------------------------------------------------------------
ResourceImplementator* ResourceCache::find(const Uri& uri)
{
    Cache::iterator fi = cache_.find(uri);
    if (cache_.end() == fi)
        return 0;
    return fi->second;
}
