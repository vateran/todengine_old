#include "tod/engine/rpbase.h"

#include "tod/engine/shader.h"
#include "tod/engine/texture.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
ShaderParams::~ShaderParams()
{
    for (Params::iterator i = params_.begin();
        i != params_.end(); ++i)
        delete i->second;
}


//-----------------------------------------------------------------------------
Variable* ShaderParams::findShaderParam(const Name& name)
{
    Params::iterator find_iter = params_.find(name);
    if (params_.end() == find_iter)
        return 0;
    return find_iter->second;
}


//-----------------------------------------------------------------------------
void ShaderParams::commit(Shader* shader)
{
    for (Params::iterator i = params_.begin();
        i != params_.end(); ++i)
    {
        Variable* v = i->second;

        if (v->getType() == TypeId<float>::id())
        {
            typedef SimpleVariable<float> FloatVariable;
            FloatVariable* rv = static_cast<FloatVariable*>(v);
            shader->setFloat(i->first, rv->get());
        }
        // Matrix44
        else if (v->getType() == TypeId<Matrix44>::id())
        {

        }
        // Texture
        else if (v->getType() == TypeId<Texture*>::id())
        {
            typedef SimpleVariable<Texture*> TextureVariable;
            TextureVariable* rv = static_cast<TextureVariable*>(v);
            shader->setTexture(i->first, rv->get());
        }
    }
    shader->commit();
}
