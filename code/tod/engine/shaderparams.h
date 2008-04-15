#ifndef TOD_ENGINE_GRAPHICS_CORE_SHADERPARAMS_H
#define TOD_ENGINE_GRAPHICS_CORE_SHADERPARAMS_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::graphics::ShaderParams
    @brief 
*/

#include <map>
#include <hash_map>
#include "tod/core/name.h"
#include "tod/core/simplevariable.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class Shader;
    class ShaderParams
    {
    public:
        virtual~ShaderParams();

        template <typename T>
        core::SimpleVariable<T>* addShaderParam(const core::Name& name);
        core::Variable* findShaderParam(const core::Name& name);

        void commit(Shader* shader);

    private:
        typedef std::map<core::Name, core::Variable*> Params;

    private:
        Params params_;
    };

#include "tod/engine/shaderparams.inl"

}
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_SHADERPARAMS_H
