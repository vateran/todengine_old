#include "tod/core/resource.h"

#include "tod/core/resourcemanager.h"
#include "tod/core/resourceimplementator.h"

using namespace tod;

//-----------------------------------------------------------------------------
Resource::Resource(const Uri& uri):ri_(0)
{
    if (uri.size())
        ri_ = ResourceManager::instance()->create(uri);
}


//-----------------------------------------------------------------------------
Resource::~Resource()
{
    if (ri_)
        ri_->close();
}


//-----------------------------------------------------------------------------
bool Resource::open(int mode)
{
    if (ri_)
        return ri_->open(mode);
    return false;
}


//-----------------------------------------------------------------------------
void Resource::close()
{
    if (ri_)
        ri_->close();
}


//-----------------------------------------------------------------------------
int Resource::write(const dynamic_buffer_t& buffer)
{
    if (ri_)
	    return ri_->write(buffer);
    return 0;
}


//-----------------------------------------------------------------------------
int Resource::write(const buffer_t* buffer, length_t len)
{
    if (ri_)
        return ri_->write(buffer, len);
    return 0;
}


//-----------------------------------------------------------------------------
int Resource::read(buffer_t* buffer, length_t len)
{
    if (ri_)
        return ri_->read(buffer, len);
    return 0;
}


//-----------------------------------------------------------------------------
int Resource::read(dynamic_buffer_t* buffer)
{
    if (0 == buffer)
        return 0;
    int s = size();
    buffer->resize(s);
    return read(&(*buffer)[0], s);
}


//-----------------------------------------------------------------------------
int Resource::size() const
{
    if (ri_)
        return ri_->size();
    return 0;
}
