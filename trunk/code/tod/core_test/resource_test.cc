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
    uri.set("managed://img#test.png");
    TODUNIT_ASSERT(uri.getProtocol() == "managed");
    TODUNIT_ASSERT(uri.getPackage() == "img");
    TODUNIT_ASSERT(uri.getPath() == "test.png");

    // test http protocol (ip + port)
    uri.set("http://127.0.0.1:8000/test.png");
    TODUNIT_ASSERT(uri.getProtocol() == "http");
    TODUNIT_ASSERT(uri.getIp() == "127.0.0.1");
    TODUNIT_ASSERT(uri.getPort() == "8000");
    TODUNIT_ASSERT(uri.getPath() == "test.png");

    // test http protocol (only ip)
    uri.set("http://127.0.0.1/test.png");
    TODUNIT_ASSERT(uri.getProtocol() == "http");
    TODUNIT_ASSERT(uri.getIp() == "127.0.0.1");
    TODUNIT_ASSERT(uri.getPort() == "");
    TODUNIT_ASSERT(uri.getPath() == "test.png");

    // test file protocol
    // relative path
    uri.set("file://test.png");
    TODUNIT_ASSERT(uri.getProtocol() == "file");
    TODUNIT_ASSERT(uri.getPath() == "test.png");

    // absolute path
    uri.set("file://C:\\test.png");
    TODUNIT_ASSERT(uri.getProtocol() == "file");
    TODUNIT_ASSERT(uri.getPath() == "C:\\test.png");

    // 불완전한 Uri 테스트
    uri.set("managed");
    TODUNIT_ASSERT(uri.getProtocol() == "");
    TODUNIT_ASSERT(uri.getPackage() == "");
    TODUNIT_ASSERT(uri.getPath() == "");
    TODUNIT_ASSERT(uri.getIp() == "");
    TODUNIT_ASSERT(uri.getPort() == "");
    uri.set("managed://");
    TODUNIT_ASSERT(uri.getProtocol() == "managed");
    TODUNIT_ASSERT(uri.getPackage() == "");
    TODUNIT_ASSERT(uri.getPath() == "");
    uri.set("managed://img");
    TODUNIT_ASSERT(uri.getProtocol() == "managed");
    TODUNIT_ASSERT(uri.getPackage() == "img");
    TODUNIT_ASSERT(uri.getPath() == "");
    uri.set("managed://img#");
    TODUNIT_ASSERT(uri.getProtocol() == "managed");
    TODUNIT_ASSERT(uri.getPackage() == "img");
    TODUNIT_ASSERT(uri.getPath() == "");
    uri.set("managed://img#test.");
    TODUNIT_ASSERT(uri.getProtocol() == "managed");
    TODUNIT_ASSERT(uri.getPackage() == "img");
    TODUNIT_ASSERT(uri.getPath() == "test.");

    uri.set("http://");
    TODUNIT_ASSERT(uri.getProtocol() == "http");
    TODUNIT_ASSERT(uri.getIp() == "");
    TODUNIT_ASSERT(uri.getPort() == "");
    TODUNIT_ASSERT(uri.getPackage() == "");
    TODUNIT_ASSERT(uri.getPath() == "");
    uri.set("http://127.0.0.1");
    TODUNIT_ASSERT(uri.getProtocol() == "http");
    TODUNIT_ASSERT(uri.getIp() == "127.0.0.1");
    uri.set("http://127.0.0.1:8000");
    TODUNIT_ASSERT(uri.getProtocol() == "http");
    TODUNIT_ASSERT(uri.getIp() == "127.0.0.1");
    TODUNIT_ASSERT(uri.getPort() == "8000");
    uri.set("http://127.0.0.1:8000/");
    TODUNIT_ASSERT(uri.getProtocol() == "http");
    TODUNIT_ASSERT(uri.getIp() == "127.0.0.1");
    TODUNIT_ASSERT(uri.getPort() == "8000");
    TODUNIT_ASSERT(uri.getPath() == "");
    uri.set("http://127.0.0.1:8000/test.png");
    TODUNIT_ASSERT(uri.getProtocol() == "http");
    TODUNIT_ASSERT(uri.getIp() == "127.0.0.1");
    TODUNIT_ASSERT(uri.getPort() == "8000");
    TODUNIT_ASSERT(uri.getPath() == "test.png");

    // get uri
    uri.set("managed://img#test.png");
    TODUNIT_ASSERT(uri.get() == "managed://img#test.png");

    // extract
    uri.set("managed://img#test.png");
    TODUNIT_ASSERT(uri.extractFile() == "test.png");
    uri.set("managed://img#test/test.png");
    TODUNIT_ASSERT(uri.extractFile() == "test.png");

    uri.set("managed://img#test.png");
    TODUNIT_ASSERT(uri.extractExtension() == "png");
    uri.set("managed://img#test/test.png");
    TODUNIT_ASSERT(uri.extractExtension() == "png");

    uri.set("managed://img#test.png");
    TODUNIT_ASSERT(uri.extractFileName() == "test");
    uri.set("managed://img#test/test.png");
    TODUNIT_ASSERT(uri.extractFileName() == "test");

    uri.set("managed://img#.png");
    TODUNIT_ASSERT(uri.extractFileName() == "");
    uri.set("managed://img#test/.png");
    TODUNIT_ASSERT(uri.extractFileName() == "");

    uri.set("managed://img#test.");
    TODUNIT_ASSERT(uri.extractExtension() == "");
    uri.set("managed://img#test/test.");
    TODUNIT_ASSERT(uri.extractExtension() == "");

    uri.set("managed://img#test/test/test.png");
    TODUNIT_ASSERT(uri.extractPath() == "test/test");

    uri.set("managed://shader#test_shader00.fx");
    TODUNIT_ASSERT(uri.extractPath() == "");
    TODUNIT_ASSERT(uri.extractFileName() == "test_shader00");
    TODUNIT_ASSERT(uri.extractFile() == "test_shader00.fx");
    TODUNIT_ASSERT(uri.extractExtension() == "fx");
}


//-----------------------------------------------------------------------------
#define DATA "test test test resource"
void ResourceTestCase::test_ResourceManager_addResource()
{
    ResourceManager::instance()->initialize("data");

    Resource r("managed://img#test/test/test.png");
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
