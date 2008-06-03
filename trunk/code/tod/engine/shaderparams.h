#ifndef TOD_ENGINE_GRAPHICS_CORE_SHADERPARAMS_H
#define TOD_ENGINE_GRAPHICS_CORE_SHADERPARAMS_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::ShaderParams
    @brief 
*/

#include <map>
#include <hash_map>
#include "tod/core/name.h"
#include "tod/core/uri.h"
#include "tod/core/simplevariable.h"

namespace tod
{
namespace engine
{
    class Shader;
    class ShaderParams
    {
    public:
        virtual~ShaderParams();

        void addTexture(const Name& name, const Uri& uri);
        void addCubeTexture(const Name& name, const Uri& uri);

        template <typename T>
        SimpleVariable<T>* addShaderParam(const Name& name);
        Variable* findShaderParam(const Name& name);

        void commit(Shader* shader);

    private:
        typedef std::map<Name, Variable*> Params;

    private:
        Params params_;
    };

#include "tod/engine/shaderparams.inl"

}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_SHADERPARAMS_H
