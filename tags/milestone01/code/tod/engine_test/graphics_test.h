#ifndef TOD_ENGINETEST_GRAPHICSTESTCASE_H
#define TOD_ENGINETEST_GRAPHICSTESTCASE_H

#include "tod/core/unittest.h"

class GraphicsTestCase : public tod::TestCase<GraphicsTestCase>
{
public:
    TODUNIT_BEGINE_TESTSUITE(GraphicsTestCase)
        TODUNIT_TEST(test_Format);
        TODUNIT_TEST(test_DisplayMode);
        TODUNIT_TEST(test_D3D9Renderer);
        //TODUNIT_TEST(test_VertexBuffer);
        //TODUNIT_TEST(test_Mesh);
        TODUNIT_TEST(test_Scene);
    TODUNIT_END_TESTSUITE()

    void test_Format();
    void test_DisplayMode();
    void test_D3D9Renderer();
    void test_VertexBuffer();
    void test_Mesh();
    void test_Scene();
};

#endif // TOD_ENGINETEST_GRAPHICSTESTCASE_H
