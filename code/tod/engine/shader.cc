#include "tod/engine/shader.h"

using namespace tod::engine;

//-----------------------------------------------------------------------------
void ShaderParamTypeEnumerationInitializer::initialize()
{
    add(STRING("TYPE_VOID"), ShaderParamDesc::TYPE_VOID);
    add(STRING("TYPE_BOOL"), ShaderParamDesc::TYPE_BOOL);
    add(STRING("TYPE_INT"), ShaderParamDesc::TYPE_INT);
    add(STRING("TYPE_FLOAT"), ShaderParamDesc::TYPE_FLOAT);
    add(STRING("TYPE_STRING"), ShaderParamDesc::TYPE_STRING);
    add(STRING("TYPE_TEXTURE"), ShaderParamDesc::TYPE_TEXTURE);
    add(STRING("TYPE_TEXTURE1D"), ShaderParamDesc::TYPE_TEXTURE1D);
    add(STRING("TYPE_TEXTURE2D"), ShaderParamDesc::TYPE_TEXTURE2D);
    add(STRING("TYPE_TEXTURE3D"), ShaderParamDesc::TYPE_TEXTURE3D);
    add(STRING("TYPE_TEXTURECUBE"), ShaderParamDesc::TYPE_TEXTURECUBE);
    add(STRING("TYPE_SAMPLER"), ShaderParamDesc::TYPE_SAMPLER);
    add(STRING("TYPE_SAMPLER1D"), ShaderParamDesc::TYPE_SAMPLER1D);
    add(STRING("TYPE_SAMPLER2D"), ShaderParamDesc::TYPE_SAMPLER2D);
    add(STRING("TYPE_SAMPLER3D"), ShaderParamDesc::TYPE_SAMPLER3D);
    add(STRING("TYPE_SAMPLERCUBE"), ShaderParamDesc::TYPE_SAMPLERCUBE);
    add(STRING("TYPE_PIXELSHADER"), ShaderParamDesc::TYPE_PIXELSHADER);
    add(STRING("TYPE_VERTEXSHADER"), ShaderParamDesc::TYPE_VERTEXSHADER);
    add(STRING("TYPE_PIXELFRAGMENT"), ShaderParamDesc::TYPE_PIXELFRAGMENT);
    add(STRING("TYPE_VERTEXFRAGMENT"), ShaderParamDesc::TYPE_VERTEXFRAGMENT);
    add(STRING("TYPE_UNSUPPORTED"), ShaderParamDesc::TYPE_UNSUPPORTED);
}
