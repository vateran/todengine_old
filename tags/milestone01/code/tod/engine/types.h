#ifndef TOD_ENGINE_GRAPHICS_CORE_TYPES_H
#define TOD_ENGINE_GRAPHICS_CORE_TYPES_H

namespace tod
{
namespace engine
{
    enum Usage
    {
        USAGE_RENDERTARGET     = (0x00000001L),
        USAGE_DEPTHSTENCIL     = (0x00000002L),
        USAGE_DYNAMIC          = (0x00000200L),
        USAGE_NONSECURE        = (0x00800000L),
        USAGE_AUTOGENMIPMAP    = (0x00000400L),
        USAGE_DMAP             = (0x00004000L),
        USAGE_QUERY_LEGACYBUMPMAP               = (0x00008000L),
        USAGE_QUERY_SRGBREAD                    = (0x00010000L),
        USAGE_QUERY_FILTER                      = (0x00020000L),
        USAGE_QUERY_SRGBWRITE                   = (0x00040000L),
        USAGE_QUERY_POSTPIXELSHADER_BLENDING    = (0x00080000L),
        USAGE_QUERY_VERTEXTEXTURE               = (0x00100000L),
        USAGE_QUERY_WRAPANDMIP                    = (0x00200000L),
        USAGE_WRITEONLY          = (0x00000008L),
        USAGE_SOFTWAREPROCESSING = (0x00000010L),
        USAGE_DONOTCLIP          = (0x00000020L),
        USAGE_POINTS             = (0x00000040L),
        USAGE_RTPATCHES          = (0x00000080L),
        USAGE_NPATCHES           = (0x00000100L),
        USAGE_TEXTAPI            = (0x10000000L),
    };


    enum Transform
    {
        TRANSFORM_WORLD         = 0,
        TRANSFORM_VIEW          = 2,
        TRANSFORM_PROJECTION    = 3,

        TRANSFORM_MAX,
    };


    enum PrimitiveType
    {
        PRIMITIVETYPE_POINTLIST = 1,
        PRIMITIVETYPE_LINELIST,
        PRIMITIVETYPE_LINESTRIP,
        PRIMITIVETYPE_TRIANGLELIST,
        PRIMITIVETYPE_TRIANGLESTRIP,
        PRIMITIVETYPE_TRIANGLEFAN,

        PRIMITIVETYPE_FORCE_DWORD = 0x7fffffff
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_TYPES_H
