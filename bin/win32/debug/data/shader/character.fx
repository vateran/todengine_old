static const int MAX_MATRICES = 26;

shared float Time;
shared float4x4 WorldMatrix;
shared float4x4 WorldMatrixArray[MAX_MATRICES];
shared float4x4 ViewMatrix;
shared float4x4 ProjectionMatrix;
shared float4x4 WorldViewProjectionMatrix;

texture DiffuseMap;

float4 g_lightDir = {0.0f, 0.0f, 1.0f, 0.0f};    //light Direction
float4 g_materialAmbient : MATERIALAMBIENT = {0.1f, 0.1f, 0.1f, 1.0f};
float4 g_materialDiffuse : MATERIALDIFFUSE = {0.8f, 0.8f, 0.8f, 1.0f};

sampler DefaultSampler =
sampler_state
{
    Texture = <DiffuseMap>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = None;
};


struct VsInput
{
    float4 pos          : POSITION;
    float4 blendWeights : BLENDWEIGHT;
    float4 blendIndices : BLENDINDICES;
    float4 diffuse      : COLOR0;
    float3 normal       : NORMAL;
    float2 uv0          : TEXCOORD0;
};


struct VsOutput
{
    float4 pos          : POSITION;
    float4 diffuse      : COLOR0;
    float2 uv0          : TEXCOORD0;
};


float3 Diffuse(float3 normal)
{
    float cos_theta;
    
    // N.L Clamped
    cos_theta = max(0.0f, dot(normal, g_lightDir.xyz));
       
    // propogate scalar result to vector
    return (cos_theta);
}


VsOutput CharacterVertexShaderMain(VsInput input, uniform int num_bones)
{
    VsOutput output;
    
    int4 index_vector = D3DCOLORtoUBYTE4(input.blendIndices);
    
    float blend_weight[4] = (float[4])input.blendWeights;
    int index[4] = (int[4])index_vector;
    
    float3 pos = 0;
    float3 normal = 0;
    float last_weight = 0;
    for (int bone = 0; bone < num_bones - 1; ++bone)
    {
        last_weight = last_weight + blend_weight[bone];
        float4x4 m = WorldMatrixArray[index[bone]] * blend_weight[bone];
        pos += mul(input.pos, m);
        normal += mul(input.normal, m);
    }
    
    last_weight = 1.0f - last_weight;
    float4x4 m = WorldMatrixArray[index[bone]] * blend_weight[bone];
    pos += mul(input.pos, m);
    normal += mul(input.normal, m);
    
    output.pos = mul(float4(pos.xyz, 1.0f), WorldViewProjectionMatrix);
    output.pos = mul(input.pos, WorldViewProjectionMatrix);
    
    normal = normalize(normal);
    
    output.diffuse.xyz = Diffuse(normal) * g_materialDiffuse.xyz;
    output.diffuse.w = 1.0f;
    
    output.uv0 = input.uv0;
    
    return output;
}


float4 CharacterPixelShaderMain(
    float4 pos      : POSITION,
    float4 diffuse  : COLOR0,
    float2 uv0      : TEXCOORD0) : COLOR
{
    return tex2D(DefaultSampler, uv0) * diffuse;
}


int g_curNumBone = 2;
VertexShader vsArray[4] =
{
    compile vs_2_0 CharacterVertexShaderMain(1),
    compile vs_2_0 CharacterVertexShaderMain(2),
    compile vs_2_0 CharacterVertexShaderMain(3),
    compile vs_2_0 CharacterVertexShaderMain(4)
};

technique Character
{
    pass P0
    {
        VertexShader = vsArray[g_curNumBone];
        PixelShader  = compile ps_2_0 CharacterPixelShaderMain();
        //FillMode = Solid;
        //CullMode = CCW;
    }
}
