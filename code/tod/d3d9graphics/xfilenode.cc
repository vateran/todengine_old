#include "tod/d3d9graphics/xfilenode.h"

#include "tod/core/resource.h"
#include "tod/core/simplepropertybinder.h"
#include "tod/engine/timeserver.h"
#include "tod/engine/shader.h"
#include "tod/engine/texture.h"
#include "tod/d3d9graphics/d3d9renderer.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(XFileNode, ShapeNode);

//-----------------------------------------------------------------------------
XFileNode::XFileNode()
{

}


//-----------------------------------------------------------------------------
XFileNode::~XFileNode()
{

}

typedef std::vector<Matrix44> MatrixArray;
typedef std::vector<Texture*> TextureArray;

struct Bone : public D3DXFRAME
{
    Matrix44 combined_;
};

struct MeshContainer : public D3DXMESHCONTAINER
{
    MeshContainer():invalidate_(false), softwareVP_(false), skinMethod_(0),
    attributeGroupCount_(0), influenceCount_(0), boneCombination_(0), paletteEntryCount_(0),
    vpRemap_(0), softwareRemapBegin_(0), originMesh_(0), swmesh_(0)
    {
        memset(this, 0, sizeof(D3DXMESHCONTAINER));
    }

    typedef std::vector<Matrix44> MatrixArray;
    typedef std::vector<Matrix44*> MatrixPtrArray;

    bool invalidate_;
    bool softwareVP_;
    ULONG skinMethod_;
    MatrixArray boneOffsets_;
    MatrixPtrArray boneMatrices_;
    DWORD attributeGroupCount_;
    DWORD influenceCount_;
    ID3DXBuffer* boneCombination_;
    ULONG paletteEntryCount_;
    ULONG* vpRemap_;
    ULONG softwareRemapBegin_;
    ID3DXMesh* originMesh_;
    ID3DXMesh* swmesh_;

    TextureArray textures_;
};

enum SkinMethod
{
    SKINMETHOD_INDEXED              = 1<<0,
    SKINMETHOD_NONINDEXED           = 1<<1,
    SKINMETHOD_SOFTWARE             = 1<<2,
    SKINMETHOD_HLSL                 = 1<<3,
    SKINMETHOD_AUTODETECT           = 1<<4,
    SKINMETHOD_PREFER_HW_NONINDEXED = 1<<5,
    SKINMETHOD_PREFER_SW_INDEXED    = 1<<6,
};

class AllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
    STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame)
    {
        Bone* new_bone = new Bone();
        if (0 == new_bone)
            return E_OUTOFMEMORY;

        if (Name)
            new_bone->Name = _strdup(Name);
        D3DXMatrixIdentity(&new_bone->TransformationMatrix);

        *ppNewFrame = static_cast<LPD3DXFRAME>(new_bone);

        return S_OK;
    }

    STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR Name, CONST D3DXMESHDATA * pMeshData,
                                   CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances,
                                   DWORD NumMaterials, CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, 
                                   LPD3DXMESHCONTAINER *ppNewMeshContainer)
    {
        HRESULT hr = S_OK;
        bool manage_attributes = true;

        if (D3DXMESHTYPE_MESH != pMeshData->Type)
            return E_FAIL;

        ID3DXMesh* mesh = pMeshData->pMesh;
        if (mesh->GetFVF() == 0)
            return E_FAIL;

        MeshContainer* mc = new MeshContainer();
        if (0 == mc)
            return E_FAIL;
        
        if (Name)
            mc->Name = _strdup(Name);

        // if no normals are in the mesh, add them
        if (!(mesh->GetFVF() & D3DFVF_NORMAL))
        {
            IDirect3DDevice9* d3ddevice = 0;

            mc->MeshData.Type = D3DXMESHTYPE_MESH;

            mesh->GetDevice(&d3ddevice);
            if (FAILED(hr = mesh->CloneMeshFVF(
                mesh->GetOptions(),
                mesh->GetFVF() | D3DFVF_NORMAL,
                d3ddevice, &mc->MeshData.pMesh)))
                return hr;
            d3ddevice->Release();

            mesh = mc->MeshData.pMesh;

            D3DXComputeNormals(mesh, pAdjacency);
        }
        else
        {
            mc->MeshData.Type = D3DXMESHTYPE_MESH;
            mc->MeshData.pMesh = mesh;
            mesh->AddRef();
        }

        // copy over adjacency information directly from the passed in 
        if (pAdjacency)
        {
            mc->pAdjacency = new DWORD[mesh->GetNumFaces() * 3];
            if (0 == mc->pAdjacency)
                return E_OUTOFMEMORY;
            memcpy(mc->pAdjacency, pAdjacency, sizeof(DWORD) * mesh->GetNumFaces() * 3);
        }

        mc->NumMaterials = NumMaterials;
        if (NumMaterials > 0 && manage_attributes == true)
        {
            mc->pMaterials = new D3DXMATERIAL[NumMaterials];
            mc->textures_.resize(NumMaterials);

            for (ULONG i = 0; i < NumMaterials; ++i)
            {
                mc->pMaterials[i].MatD3D = pMaterials[i].MatD3D;
                //mc->pMaterials[i].pTextureFilename = _strdup(pMaterials[i].pTextureFilename);

                Uri uri = uri_.getProtocol() + String("://") +
                    uri_.getPackage() + String("#") +
                    uri_.extractPath() + String(pMaterials[i].pTextureFilename);
                mc->textures_[i] = Renderer::instance()->newTexture(uri);
                if (mc->textures_[i]->invalid())
                    mc->textures_[i]->preload();
            }
        }

        // skined mesh
        if (pSkinInfo)
        {
            ID3DXMesh* skinned_mesh = 0;

            mc->pSkinInfo = pSkinInfo;
            pSkinInfo->AddRef();

            mc->originMesh_ = mesh;
            mesh->AddRef();

            ULONG bone_count = pSkinInfo->GetNumBones();
            mc->boneOffsets_.resize(bone_count);

            for (ULONG i = 0; i < bone_count; ++i)
            {
                memcpy(mc->boneOffsets_[i].a_,
                    pSkinInfo->GetBoneOffsetMatrix(i),
                    sizeof(D3DXMATRIX));
            }

            if (FAILED(hr = build_skinned_mesh(mc, mesh, &skinned_mesh)))
                return hr;

            mesh = skinned_mesh;
        }

        *ppNewMeshContainer = static_cast<LPD3DXMESHCONTAINER>(mc);

        return S_OK;
    }

    STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree)
    {
        if (pFrameToFree)
        {
            free(pFrameToFree->Name);
            delete pFrameToFree;
        }

        return S_OK;
    }

    STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerBase)
    {
        return S_OK;
    }

    HRESULT build_skinned_mesh(MeshContainer* mc, ID3DXMesh* mesh, ID3DXMesh** mesh_out)
    {
        HRESULT hr = S_OK;
        IDirect3DDevice9* d3ddevice = 0;
        ID3DXSkinInfo* skin_info = mc->pSkinInfo;
        D3DCAPS9 caps;

        mesh->GetDevice(&d3ddevice);
        d3ddevice->GetDeviceCaps(&caps);
        d3ddevice->Release();

        // calculate the best skinning method and store
        mc->skinMethod_ = detect_skinning_method(caps, skin_info, mesh);

        if (SKINMETHOD_INDEXED == mc->skinMethod_)
        {
        }
        else if (SKINMETHOD_NONINDEXED == mc->skinMethod_)
        {
        }
        else if (SKINMETHOD_HLSL == mc->skinMethod_)
        {
            UINT max_matrices = 26;
            mc->paletteEntryCount_ = min(max_matrices, mc->pSkinInfo->GetNumBones());

            DWORD flags = D3DXMESHOPT_VERTEXCACHE;
            if (caps.VertexShaderVersion >= D3DVS_VERSION(1, 1))
            {
                mc->softwareVP_ = false;
                flags |= D3DXMESH_MANAGED;
            }
            else
            {
                mc->softwareVP_ = true;
                flags |= D3DXMESH_SYSTEMMEM;
            }

            SAFE_RELEASE(mc->MeshData.pMesh);

            if (FAILED(hr = mc->pSkinInfo->ConvertToIndexedBlendedMesh(
                mc->originMesh_, flags, max_matrices,
                mc->pAdjacency, 0, 0, 0,
                &mc->influenceCount_,
                &mc->attributeGroupCount_,
                &mc->boneCombination_,
                &mc->MeshData.pMesh)))
                return hr;

            DWORD new_fvf = (mc->MeshData.pMesh->GetFVF() & D3DFVF_POSITION_MASK) |
                D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_LASTBETA_UBYTE4;
            if (new_fvf != mc->MeshData.pMesh->GetFVF())
            {
                ID3DXMesh* clone_mesh = 0;
                if (FAILED(hr = mc->MeshData.pMesh->CloneMeshFVF(
                    mc->MeshData.pMesh->GetOptions(),
                    new_fvf, d3ddevice, &clone_mesh)))
                    return hr;
                mc->MeshData.pMesh->Release();
                mc->MeshData.pMesh = clone_mesh;
            }

            D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
            LPD3DVERTEXELEMENT9 decl_cur;
            if (FAILED(hr = mc->MeshData.pMesh->GetDeclaration(decl)))
                return hr;
            decl_cur = decl;
            if (FAILED(hr = mc->MeshData.pMesh->UpdateSemantics(decl)))
                return hr;

            boneMatrices_->resize(mc->pSkinInfo->GetNumBones());
        }
        else if (SKINMETHOD_SOFTWARE == mc->skinMethod_)
        {
            if (FAILED(hr = mesh->CloneMeshFVF(
                D3DXMESH_MANAGED, mesh->GetFVF(),
                d3ddevice, &mc->swmesh_)))
                return hr;

            mesh->AddRef();
            *mesh_out = mesh;
        }

        return S_OK;
    }

    ULONG detect_skinning_method(const D3DCAPS9& caps, ID3DXSkinInfo* skin_info, ID3DXMesh* mesh)
    {
        ULONG skin_method = skinMethod_;

        if (skin_method & SKINMETHOD_AUTODETECT)
        {
            bool hw_indexed = false;
            bool hw_nonindexed = false;
            DWORD max_influence = 0;

            if (caps.MaxVertexBlendMatrixIndex > 0)
            {
                IDirect3DIndexBuffer9* ib;
                if (SUCCEEDED(mesh->GetIndexBuffer(&ib)))
                {   
                    skin_info->GetMaxFaceInfluences(ib, mesh->GetNumFaces(), &max_influence);
                    ib->Release();

                    if (caps.MaxVertexBlendMatrixIndex + 1 >= max_influence)
                        hw_indexed = true;
                }
            }

            skin_info->GetMaxVertexInfluences(&max_influence);
            if (caps.MaxVertexBlendMatrices >= max_influence)
                hw_nonindexed = true;

            if (hw_indexed == true && hw_nonindexed == false)
                return SKINMETHOD_INDEXED;
            else if (hw_indexed == false && hw_nonindexed == true)
                return SKINMETHOD_NONINDEXED;
            else if (hw_indexed == true && hw_nonindexed == true)
            {
                if (SKINMETHOD_PREFER_HW_NONINDEXED & skin_method)
                    return SKINMETHOD_NONINDEXED;
                else
                    return SKINMETHOD_INDEXED;
            }
            else
            {
                if (SKINMETHOD_PREFER_SW_INDEXED & skin_method)
                    return SKINMETHOD_INDEXED;
                else
                    return SKINMETHOD_NONINDEXED;
            }
        }

        return skin_method;
    }

public:
    SkinMethod skinMethod_;
    MatrixArray* boneMatrices_;
    TextureArray* textures_;
    Uri uri_;
};

class XFile
{
public:
    XFile():
    d3ddevice_(0), root_(0), animController_(0), option_(0), skinMethod_(SKINMETHOD_HLSL)
    {
    }

    bool load(IDirect3DDevice9* device, const Uri& uri, ULONG mesh_option)
    {
        d3ddevice_ = device;
        option_ = mesh_option;

        tod::Resource resource(uri);
        if (!resource.open(
            tod::Resource::OPEN_READ |
            tod::Resource::OPEN_BINARY))
            return false;

        dynamic_buffer_t buffer;
        resource.read(&buffer);

        AllocateHierarchy allocator;
        allocator.skinMethod_ = skinMethod_;
        allocator.boneMatrices_ = &boneMatrices_;
        allocator.textures_ = &textures_;
        allocator.uri_ = uri;
        if (FAILED(D3DXLoadMeshHierarchyFromXInMemory(
            &buffer[0], buffer.size(), option_, d3ddevice_,
            &allocator, 0, reinterpret_cast<D3DXFRAME**>(&root_), &animController_)))
            return false;

        setup_bone_matrix_pointers(root_);        
        return true;
    }

    void advanceTime(Time elapse, bool update_frame=true)
    {
        if (animController_)
            animController_->AdvanceTime(elapse, 0);
        if (update_frame)
            update_frame_matrices(root_, world_);
    }

    void draw()
    {
        if (!isLoaded())
            return;
        // draw the frame hierarchy
        draw_frame(root_);
    }
    void drawSubset(ULONG attribute_id)
    {
        if (!isLoaded())
            return;
        draw_frame(root_, attribute_id);
    }

    bool isLoaded() const
    {
        return (root_ != 0)?true:false;
    }

private:
    void setup_bone_matrix_pointers(D3DXFRAME* frame)
    {
        if (frame->pMeshContainer)
            setup_bone_matrix_pointers_on_mesh(frame->pMeshContainer);
        if (frame->pFrameSibling)
            setup_bone_matrix_pointers(frame->pFrameSibling);
        if (frame->pFrameFirstChild)
            setup_bone_matrix_pointers(frame->pFrameFirstChild);
    }

    void setup_bone_matrix_pointers_on_mesh(LPD3DXMESHCONTAINER mesh_container)
    {
        MeshContainer* mc = static_cast<MeshContainer*>(mesh_container);

        if (mc->pSkinInfo)
        {
            UINT num_bones = mc->pSkinInfo->GetNumBones();
            mc->boneMatrices_.resize(num_bones);

            for (UINT bone_index = 0; bone_index < num_bones; ++bone_index)
            {
                Bone* bone = static_cast<Bone*>(
                    D3DXFrameFind(root_, mc->pSkinInfo->GetBoneName(bone_index)));
                if (0 == bone)
                    return;
                mc->boneMatrices_[bone_index] = &bone->combined_;
            }
        }
    }

    void draw_frame(D3DXFRAME* frame, ULONG attribute_id=-1)
    {
        LPD3DXMESHCONTAINER mc = 0;
        for (mc = frame->pMeshContainer; mc; mc = mc->pNextMeshContainer)
            draw_mesh_container(mc, frame, attribute_id);

        // move onto next sibiling bone
        if (frame->pFrameSibling)
            draw_frame(frame->pFrameSibling, attribute_id);

        // move onto first child bone
        if (frame->pFrameFirstChild)
            draw_frame(frame->pFrameFirstChild, attribute_id);
    }

    void draw_mesh_container(LPD3DXMESHCONTAINER mesh_container, D3DXFRAME* frame, ULONG attribute_id)
    {
        if (0 == mesh_container)
            return;
        MeshContainer* mc = static_cast<MeshContainer*>(mesh_container);
        ID3DXSkinInfo* skin_info = mc->pSkinInfo;
        if (skin_info)
        {
            // indexed vertex processing
            if (SKINMETHOD_INDEXED == mc->skinMethod_)
            {
                if (mc->softwareVP_)
                    d3ddevice_->SetSoftwareVertexProcessing(true);
            }
            else if (SKINMETHOD_NONINDEXED == mc->skinMethod_)
            {

            }
            else if (SKINMETHOD_SOFTWARE == mc->skinMethod_)
            {
                ULONG bone_count = skin_info->GetNumBones();

                if (mc->invalidate_)
                {
                    for (ULONG i = 0; i < bone_count; ++i)
                    {
                        swMatrices_[i] = mc->boneOffsets_[i] * *mc->boneMatrices_[i];
                    }

                    PBYTE src;
                    PBYTE dest;
                    mc->originMesh_->LockVertexBuffer(
                        D3DLOCK_READONLY, reinterpret_cast<LPVOID*>(&src));
                    mc->swmesh_->LockVertexBuffer(
                        0, reinterpret_cast<LPVOID*>(&dest));
                    skin_info->UpdateSkinnedMesh(
                        reinterpret_cast<D3DXMATRIX*>(&swMatrices_[0]), 0, src, dest);
                    mc->swmesh_->UnlockVertexBuffer();
                    mc->originMesh_->UnlockVertexBuffer();
                }

                Matrix44 identity;
                identity.identity();
                Renderer::instance()->setTransform(TRANSFORM_WORLD, identity);

                if (attribute_id >= 0)
                    mc->swmesh_->DrawSubset(0);
                else
                {
                    mc->swmesh_->DrawSubset(0);
                }
            }
            else if (SKINMETHOD_HLSL == mc->skinMethod_)
            {
                if (mc->softwareVP_)
                {
                    d3ddevice_->SetSoftwareVertexProcessing(true);
                }

                LPD3DXBONECOMBINATION bone_comb =
                    reinterpret_cast<LPD3DXBONECOMBINATION>(
                        mc->boneCombination_->GetBufferPointer());

                for (DWORD attr_id = 0; attr_id < mc->attributeGroupCount_; ++attr_id)
                {
                    for (DWORD p_entry = 0; p_entry < mc->paletteEntryCount_; ++p_entry)
                    {
                        // first cacluate all the world matrices
                        DWORD matrix_index = bone_comb[attr_id].BoneId[p_entry];
                        if (matrix_index != UINT_MAX)
                        {
                            boneMatrices_[p_entry] =
                                mc->boneOffsets_[matrix_index] *
                                *mc->boneMatrices_[matrix_index];
                        }
                    }

                    shader_->setMatrixArray("WorldMatrixArray", &boneMatrices_[0], mc->paletteEntryCount_);
                    shader_->setInt("g_curNumBone", mc->influenceCount_ - 1);
                    shader_->setTexture("DiffuseMap", mc->textures_[0]);
                    shader_->commit();

                    uint32_t num_passes;
                    shader_->begin(num_passes);
                    for(uint32_t pass = 0; pass < num_passes; ++pass)
                    {
                        shader_->beginPass(pass);
                        mc->MeshData.pMesh->DrawSubset(attr_id);
                        shader_->endPass();
                    }
                    shader_->end();
                }
            }
        }
        else
        {
            Bone* bone = static_cast<Bone*>(frame);
            Renderer::instance()->setTransform(TRANSFORM_WORLD, bone->combined_);

            for(UINT m = 0; m < mc->NumMaterials; m++ )
            {
                //pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[iMaterial].MatD3D ) );
                //pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[iMaterial] ) );
                mc->MeshData.pMesh->DrawSubset(m);
            }
        }
    }

    void update_frame_matrices(D3DXFRAME* frame, const Matrix44& m)
    {
    }

private:
    

private:
    IDirect3DDevice9* d3ddevice_;
    Bone* root_;
    ID3DXAnimationController* animController_;
    Matrix44 world_;
    ULONG option_;
    SkinMethod skinMethod_;
    MatrixArray swMatrices_;

public:
    Shader* shader_;
    MatrixArray boneMatrices_;
    TextureArray textures_;
};

XFile xfile;

//-----------------------------------------------------------------------------
void XFileNode::applyGeometry(SceneServer* scene_server)
{

}


//-----------------------------------------------------------------------------
void XFileNode::renderGeometry
(SceneServer* scene_server, SceneContext* scene_context)
{
    xfile.shader_ = getShader();
    if (xfile.shader_ == 0)
        return;
    xfile.advanceTime(0);
    xfile.draw();
}


//-----------------------------------------------------------------------------
bool XFileNode::loadResource()
{
    if (getMeshUri().empty())
        return false;

    super::loadResource();

    D3D9Renderer* renderer = dynamic_cast<D3D9Renderer*>(Renderer::instance());
    if (0 == renderer)
        return false;
    return xfile.load(renderer->getD3DDevice(), uri_, D3DXMESH_MANAGED);
}


//-----------------------------------------------------------------------------
void XFileNode::unloadResource()
{
    //

    super::unloadResource();
}


//-----------------------------------------------------------------------------
bool XFileNode::hasGeometry() const
{
    return true;
}

//-----------------------------------------------------------------------------
void XFileNode::setMeshUri(const Uri& uri)
{
    uri_ = uri;
    unloadResource();
}


//-----------------------------------------------------------------------------
const Uri& XFileNode::getMeshUri() const
{
    return uri_;
}


//-----------------------------------------------------------------------------
void XFileNode::bindProperty()
{
    BIND_PROPERTY(const Uri&, mesh_uri, &setMeshUri, &getMeshUri);
}

static void XFileNode_v_setInt_i(XFileNode* self, Parameter* param)
{
    self->setInt(param->in()->get<int>(0));
}

static void XFileNode_i_getInt_v(XFileNode* self, Parameter* param)
{
    param->out()->get<int>(0) = self->getInt();
}

#include "tod/core/methodbinder.h"
void XFileNode::bindMethod()
{
    BIND_METHOD(v_setInt_i, XFileNode_v_setInt_i);
    BIND_METHOD(i_getInt_v, XFileNode_i_getInt_v);
}