#ifndef TOD_CORE_TYPE_URI_H
#define TOD_CORE_TYPE_URI_H
/**
    @ingroup TodCoreType
    @class tod::core::Uri
    @brief Universal Resource Identifier

    @section URIParts
        - Protocol
            - managed://
            - file://
            - http://
        - IP
        - Port
        - Path
        - Assembled example
            - managed://local/world/heightmap.png
            - file://c:/world/heightmap.png
            - http://192.168.0.1:8000/world/heightmap.png
*/

#include "tod/core/string.h"

namespace tod
{
namespace core
{
    class Uri
    {
    public:
        Uri();
        Uri(const char_t* uri);
        Uri(const String& uri);

        void set(const char_t* uri);
        const String& get() const;
        const char_t* c_str() const;

        void setProtocol(const char_t* protocol);
        void setPackage(const char_t* managed);
        void setIp(const char_t* ip);
        void setPort(const char_t* port);
        void setPath(const char_t* path);

        const String& getProtocol() const;
        const String& getPackage() const;
        const String& getIp() const;
        const String& getPort() const;
        const String& getPath() const;

        String extractPath() const;
        String extractFile() const;
        String extractFileName() const;
        String extractExtension() const;

        bool operator < (const Uri& rhs) const;

    private:
        String uri_;
        String protocol_;
        String managed_;
        String ip_;
        String port_;
        String path_;
    };

#include "tod/core/uri.inl"

}
}

#endif // TOD_CORE_TYPE_URI_H
