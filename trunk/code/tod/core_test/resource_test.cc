#include "resource_test.h"

#include <map>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include "tod/core/primitivetype.h"
#include "tod/core/time.h"
#include "tod/core/uri.h"
#include "tod/core/resource.h"
#include "tod/core/resourcemanager.h"

using namespace tod;

//-----------------------------------------------------------------------------
void ResourceTestCase::test_Uri_split()
{
    Uri uri;
    // test managed protocol
    uri.set(STRING("managed://img#test.png"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("managed"));
    TODUNIT_ASSERT(uri.getPackage() == STRING("img"));
    TODUNIT_ASSERT(uri.getPath() == STRING("test.png"));

    // test http protocol (ip + port)
    uri.set(STRING("http://127.0.0.1:8000/test.png"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("http"));
    TODUNIT_ASSERT(uri.getIp() == STRING("127.0.0.1"));
    TODUNIT_ASSERT(uri.getPort() == STRING("8000"));
    TODUNIT_ASSERT(uri.getPath() == STRING("test.png"));

    // test http protocol (only ip)
    uri.set(STRING("http://127.0.0.1/test.png"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("http"));
    TODUNIT_ASSERT(uri.getIp() == STRING("127.0.0.1"));
    TODUNIT_ASSERT(uri.getPort() == STRING(""));
    TODUNIT_ASSERT(uri.getPath() == STRING("test.png"));

    // test file protocol
    // relative path
    uri.set(STRING("file://test.png"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("file"));
    TODUNIT_ASSERT(uri.getPath() == STRING("test.png"));

    // absolute path
    uri.set(STRING("file://C:\\test.png"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("file"));
    TODUNIT_ASSERT(uri.getPath() == STRING("C:\\test.png"));

    // 불완전한 Uri 테스트
    uri.set(STRING("managed"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING(""));
    TODUNIT_ASSERT(uri.getPackage() == STRING(""));
    TODUNIT_ASSERT(uri.getPath() == STRING(""));
    TODUNIT_ASSERT(uri.getIp() == STRING(""));
    TODUNIT_ASSERT(uri.getPort() == STRING(""));
    uri.set(STRING("managed://"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("managed"));
    TODUNIT_ASSERT(uri.getPackage() == STRING(""));
    TODUNIT_ASSERT(uri.getPath() == STRING(""));
    uri.set(STRING("managed://img"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("managed"));
    TODUNIT_ASSERT(uri.getPackage() == STRING("img"));
    TODUNIT_ASSERT(uri.getPath() == STRING(""));
    uri.set(STRING("managed://img#"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("managed"));
    TODUNIT_ASSERT(uri.getPackage() == STRING("img"));
    TODUNIT_ASSERT(uri.getPath() == STRING(""));
    uri.set(STRING("managed://img#test."));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("managed"));
    TODUNIT_ASSERT(uri.getPackage() == STRING("img"));
    TODUNIT_ASSERT(uri.getPath() == STRING("test."));

    uri.set(STRING("http://"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("http"));
    TODUNIT_ASSERT(uri.getIp() == STRING(""));
    TODUNIT_ASSERT(uri.getPort() == STRING(""));
    TODUNIT_ASSERT(uri.getPackage() == STRING(""));
    TODUNIT_ASSERT(uri.getPath() == STRING(""));
    uri.set(STRING("http://127.0.0.1"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("http"));
    TODUNIT_ASSERT(uri.getIp() == STRING("127.0.0.1"));
    uri.set(STRING("http://127.0.0.1:8000"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("http"));
    TODUNIT_ASSERT(uri.getIp() == STRING("127.0.0.1"));
    TODUNIT_ASSERT(uri.getPort() == STRING("8000"));
    uri.set(STRING("http://127.0.0.1:8000/"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("http"));
    TODUNIT_ASSERT(uri.getIp() == STRING("127.0.0.1"));
    TODUNIT_ASSERT(uri.getPort() == STRING("8000"));
    TODUNIT_ASSERT(uri.getPath() == STRING(""));
    uri.set(STRING("http://127.0.0.1:8000/test.png"));
    TODUNIT_ASSERT(uri.getProtocol() == STRING("http"));
    TODUNIT_ASSERT(uri.getIp() == STRING("127.0.0.1"));
    TODUNIT_ASSERT(uri.getPort() == STRING("8000"));
    TODUNIT_ASSERT(uri.getPath() == STRING("test.png"));

    // get uri
    uri.set(STRING("managed://img#test.png"));
    TODUNIT_ASSERT(uri.get() == STRING("managed://img#test.png"));

    // extract
    uri.set(STRING("managed://img#test.png"));
    TODUNIT_ASSERT(uri.extractFile() == STRING("test.png"));
    uri.set(STRING("managed://img#test/test.png"));
    TODUNIT_ASSERT(uri.extractFile() == STRING("test.png"));

    uri.set(STRING("managed://img#test.png"));
    TODUNIT_ASSERT(uri.extractExtension() == STRING("png"));
    uri.set(STRING("managed://img#test/test.png"));
    TODUNIT_ASSERT(uri.extractExtension() == STRING("png"));

    uri.set(STRING("managed://img#test.png"));
    TODUNIT_ASSERT(uri.extractFileName() == STRING("test"));
    uri.set(STRING("managed://img#test/test.png"));
    TODUNIT_ASSERT(uri.extractFileName() == STRING("test"));

    uri.set(STRING("managed://img#.png"));
    TODUNIT_ASSERT(uri.extractFileName() == STRING(""));
    uri.set(STRING("managed://img#test/.png"));
    TODUNIT_ASSERT(uri.extractFileName() == STRING(""));

    uri.set(STRING("managed://img#test."));
    TODUNIT_ASSERT(uri.extractExtension() == STRING(""));
    uri.set(STRING("managed://img#test/test."));
    TODUNIT_ASSERT(uri.extractExtension() == STRING(""));

    uri.set(STRING("managed://img#test/test/test.png"));
    TODUNIT_ASSERT(uri.extractPath() == STRING("test/test"));

    uri.set(STRING("managed://shader#test_shader00.fx"));
    TODUNIT_ASSERT(uri.extractPath() == STRING(""));
    TODUNIT_ASSERT(uri.extractFileName() == STRING("test_shader00"));
    TODUNIT_ASSERT(uri.extractFile() == STRING("test_shader00.fx"));
    TODUNIT_ASSERT(uri.extractExtension() == STRING("fx"));
}


//-----------------------------------------------------------------------------
#define DATA "test test test resource"
void ResourceTestCase::test_ResourceManager_addResource()
{
    ResourceManager::instance()->initialize(STRING("data"));

    Resource r(STRING("managed://img#test/test/test.png"));
    TODUNIT_ASSERT(r.open(Resource::OPEN_WRITE | Resource::OPEN_BINARY));

    char buffer[256];
    memset(buffer, 0, 256);
    memcpy(buffer, DATA, strlen(DATA));

    TODUNIT_ASSERT(r.write(buffer, 256) == 256);
    r.close();

    memset(buffer, 0, 256);
    TODUNIT_ASSERT(r.open(Resource::OPEN_READ | Resource::OPEN_BINARY));
    TODUNIT_ASSERT(r.read(buffer, 256) == 256);
    TODUNIT_ASSERT(strcmp(buffer, DATA) == 0);
    r.close();

}
#undef DATA

//-----------------------------------------------------------------------------
void ResourceTestCase::test_ResourceManager_removeResource()
{
}

//-----------------------------------------------------------------------------
void ResourceTestCase::test_ResourceManager_findResource()
{
}
