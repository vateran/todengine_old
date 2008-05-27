#include "tod/engine/terrainsection.h"

#include "tod/engine/renderer.h"

using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
TerrainSection::TerrainSection()
{
    // empty
}


//-----------------------------------------------------------------------------
TerrainSection::~TerrainSection()
{
    // empty
}

//-----------------------------------------------------------------------------
VertexBuffer* vb = 0;
Texture* height_map = 0;
#include "tod/engine/texture.h"
#include "tod/engine/vertexbuffer.h"
#include "tod/engine/indexbuffer.h"
void TerrainSection::render()
{
    if (vb == 0)
    {   
        height_map = Renderer::instance()->
            newTexture(STRING("managed://texture#map.bmp"));
        height_map->preload();
        char* ptr = 0;
        int pitch;
        height_map->lockRect(0, 0, (void*&)&ptr, &pitch);
        height_map->unlockRect(0);

        vb = Renderer::instance()->newVertexBuffer(STRING("test"));
        //vb->create();
    }
}
