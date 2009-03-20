#include "tod/core/fsresourceimplementator.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "tod/core/define.h"
#include "tod/core/primitivetype.h"
#include "tod/core/exception.h"
#include "tod/core/resource.h"

using namespace tod;

//-----------------------------------------------------------------------------
FsResourceImplementator::FsResourceImplementator(const String& path):path_(path)
{
    mtime_ = get_mtime();
}


//-----------------------------------------------------------------------------
FsResourceImplementator::~FsResourceImplementator()
{
    close();
}


//-----------------------------------------------------------------------------
bool FsResourceImplementator::open(int mode)
{
    std::ios_base::openmode om = 0;
    if (mode & Resource::OPEN_WRITE)
        om |= std::ios_base::out;
    if (mode & Resource::OPEN_READ)
        om |= std::ios_base::in;
    if (mode & Resource::OPEN_BINARY)
        om |= std::ios_base::binary;

    file_.open(path_.c_str(), om);
    if (!file_.is_open())
    {
        TOD_THROW_EXCEPTION(TODEXCEPTIONCODE_RESOURCEOPEN,
            String("Could not open resource(%s)\n", path_.c_str()));
        return false;
    }
    return true;
}


//-----------------------------------------------------------------------------
void FsResourceImplementator::close()
{
    if (file_.is_open())
    {
	    file_.clear();
        file_.close();
    }
}


//-----------------------------------------------------------------------------
int FsResourceImplementator::write(const dynamic_buffer_t& buffer)
{
	std::ios_base::streampos p = file_.tellp();
	file_.write(&buffer[0], buffer.size());
	return file_.tellp() - p;
}


//-----------------------------------------------------------------------------
int FsResourceImplementator::write(const buffer_t* buffer, length_t len)
{
    // buffer cahce
    buffer_.resize(len);
    memcpy(&buffer_[0], buffer, len);
    
    // write to file on-the-fly
    std::ios_base::streampos p = file_.tellp();
    file_.write(buffer, len);
    return file_.tellp() - p;
}


//-----------------------------------------------------------------------------
int FsResourceImplementator::read(buffer_t* buffer, length_t len)
{
    // read from cache buffer
    length_t read_len = len;
    if (read_len > buffer_.size())
        read_len = buffer_.size();
    if (isUpdated())
        reload();
    memcpy(buffer, &buffer_[0], len);
    return read_len;
}


//-----------------------------------------------------------------------------
int FsResourceImplementator::size() const
{
    std::ios_base::streampos g = file_.tellg();
    file_.seekg(0, std::ios_base::end);
    int s = file_.tellg();;
    file_.seekg(g, std::ios_base::beg);
    return s;
}


//-----------------------------------------------------------------------------
bool FsResourceImplementator::isUpdated() const
{
    if (buffer_.size() == 0)
        return true;
    if (buffer_.size() != size())
        return true;
    if (mtime_ != get_mtime())
        return true;
    return false;
}


//-----------------------------------------------------------------------------
void FsResourceImplementator::reload()
{
    length_t len = size();
    buffer_.resize(len);
    file_.seekg(0, std::ios_base::beg);
    file_.read(&buffer_[0], len);
}


//-----------------------------------------------------------------------------
uint64_t FsResourceImplementator::get_mtime() const
{
    int fd = -1;
    struct _stat buf;
    buf.st_mtime = 0;
    _sopen_s(&fd, path_.c_str(), _O_RDONLY, _SH_SECURE, 0);
    if(-1 != fd)
    {   
        _fstat(fd, &buf);
        _close(fd);
    }
    return buf.st_mtime;
}
