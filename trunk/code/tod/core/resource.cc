#include "tod/core/resource.h"

#include "tod/core/resourcemanager.h"
#include "tod/core/resourceimplementator.h"

using namespace tod;

//-----------------------------------------------------------------------------
Resource::Resource(const Uri& uri)
{
    ri_ = ResourceManager::instance()->create(uri);
}


//-----------------------------------------------------------------------------
Resource::~Resource()
{
    delete ri_;
}


//-----------------------------------------------------------------------------
bool Resource::open(int mode)
{
    return ri_->open(mode);
}


//-----------------------------------------------------------------------------
void Resource::close()
{
    ri_->close();
}


//-----------------------------------------------------------------------------
int Resource::write(const buffer_t* buffer, length_t len)
{
    return ri_->write(buffer, len);
}


//-----------------------------------------------------------------------------
int Resource::read(buffer_t* buffer, length_t len)
{
    return ri_->read(buffer, len);
}


//-----------------------------------------------------------------------------
int Resource::read(dynamic_buffer_t& buffer)
{
    int s = size();
    buffer.resize(s);
    return read(&buffer[0], s);
}


//-----------------------------------------------------------------------------
int Resource::size() const
{
    return ri_->size();
}
