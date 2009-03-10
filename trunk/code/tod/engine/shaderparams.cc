#include "tod/engine/rpbase.h"

#include "tod/engine/shader.h"
#include "tod/engine/texture.h"
#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
ShaderParams::~ShaderParams()
{
    for (Params::iterator i = params_.begin();
        i != params_.end(); ++i)
        delete i->second;
}


//-----------------------------------------------------------------------------
void ShaderParams::setFloat(const String& name, float value)
{
    // set shader parameter
    typedef SimpleVariable<float> FloatVariable;
    FloatVariable* f = getShaderParam<FloatVariable>(name);
    *f = value;
}


//-----------------------------------------------------------------------------
void ShaderParams::setTexture(const String& name, const Uri& uri)
{   
    Texture* texture = 0;
    if (uri.size())
    {
        // load texture
        texture = Renderer::instance()->newTexture(uri);
        if (0 == texture)
            return;
    }

    // set shader parameter
    typedef SimpleVariable<Texture*> TextureVariable;
    TextureVariable* t = getShaderParam<TextureVariable>(name);
    *t = texture;
}


//-----------------------------------------------------------------------------
void ShaderParams::setCubeTexture(const String& name, const Uri& uri)
{
    Texture* texture = 0;
    if (uri.size())
    {
        // load texture
        texture = Renderer::instance()->newCubeTexture(uri);
        if (0 == texture)
            return;
    }

    // add shader parameter
    typedef SimpleVariable<Texture*> TextureVariable;
    TextureVariable* t = getShaderParam<TextureVariable>(name);
    *t = texture;
}


//-----------------------------------------------------------------------------
Variable* ShaderParams::findShaderParam(const String& name)
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
            Texture* t = *static_cast<TextureVariable*>(v);
            if (t)
            {
                if (t->invalid())
                    t->preload();
            }
            shader->setTexture(i->first, t);
        }
    }
    shader->commit();
}
