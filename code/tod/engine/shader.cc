#include "tod/engine/shader.h"

using namespace tod::engine;

//-----------------------------------------------------------------------------
void ShaderParamTypeEnumerationInitializer::initialize()
{
    add("TYPE_VOID", ShaderParamDesc::TYPE_VOID);
    add("TYPE_BOOL", ShaderParamDesc::TYPE_BOOL);
    add("TYPE_INT", ShaderParamDesc::TYPE_INT);
    add("TYPE_FLOAT", ShaderParamDesc::TYPE_FLOAT);
    add("TYPE_STRING", ShaderParamDesc::TYPE_STRING);
    add("TYPE_TEXTURE", ShaderParamDesc::TYPE_TEXTURE);
    add("TYPE_TEXTURE1D", ShaderParamDesc::TYPE_TEXTURE1D);
    add("TYPE_TEXTURE2D", ShaderParamDesc::TYPE_TEXTURE2D);
    add("TYPE_TEXTURE3D", ShaderParamDesc::TYPE_TEXTURE3D);
    add("TYPE_TEXTURECUBE", ShaderParamDesc::TYPE_TEXTURECUBE);
    add("TYPE_SAMPLER", ShaderParamDesc::TYPE_SAMPLER);
    add("TYPE_SAMPLER1D", ShaderParamDesc::TYPE_SAMPLER1D);
    add("TYPE_SAMPLER2D", ShaderParamDesc::TYPE_SAMPLER2D);
    add("TYPE_SAMPLER3D", ShaderParamDesc::TYPE_SAMPLER3D);
    add("TYPE_SAMPLERCUBE", ShaderParamDesc::TYPE_SAMPLERCUBE);
    add("TYPE_PIXELSHADER", ShaderParamDesc::TYPE_PIXELSHADER);
    add("TYPE_VERTEXSHADER", ShaderParamDesc::TYPE_VERTEXSHADER);
    add("TYPE_PIXELFRAGMENT", ShaderParamDesc::TYPE_PIXELFRAGMENT);
    add("TYPE_VERTEXFRAGMENT", ShaderParamDesc::TYPE_VERTEXFRAGMENT);
    add("TYPE_UNSUPPORTED", ShaderParamDesc::TYPE_UNSUPPORTED);
}
