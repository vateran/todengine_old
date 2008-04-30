shared float Time;
shared float4x4 WorldMatrix;
shared float4x4 ViewMatrix;
shared float4x4 ProjectionMatrix;
shared float4x4 WorldViewProjectionMatrix;

texture SceneMap;

sampler SceneSampler =
sampler_state
{
    Texture = <SceneMap>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = None;
};

static const int g_cKernelSize = 13;
static const float g_cWidth = 80;
static const float g_cHeight = 60;

float2 TexelKernel[g_cKernelSize] =
{
    { -6 / g_cWidth, -6 / g_cHeight },
    { -5 / g_cWidth, -5 / g_cHeight },
    { -4 / g_cWidth, -4 / g_cHeight },
    { -3 / g_cWidth, -3 / g_cHeight },
    { -2 / g_cWidth, -2 / g_cHeight },
    { -1 / g_cWidth, -1 / g_cHeight },
    {  0 / g_cWidth,  0 / g_cHeight },
    {  1 / g_cWidth,  1 / g_cHeight },
    {  2 / g_cWidth,  2 / g_cHeight },
    {  3 / g_cWidth,  3 / g_cHeight },
    {  4 / g_cWidth,  4 / g_cHeight },
    {  5 / g_cWidth,  5 / g_cHeight },
    {  6 / g_cWidth,  6 / g_cHeight },
};

static const float BlurWeights[g_cKernelSize] = 
{
    0.002216,
    0.008764,
    0.026995,
    0.064759,
    0.120985,
    0.176033,
    0.199471,
    0.176033,
    0.120985,
    0.064759,
    0.026995,
    0.008764,
    0.002216,
};

float BloomScale = 2.5f;


void vsQuadMain(
    float4 pos              : POSITION,
    float4 diffuse          : COLOR0,
    float2 uv0              : TEXCOORD0,
    out float4 out_pos      : POSITION,
    out float4 out_diffuse  : COLOR0,
    out float2 out_uv0      : TEXCOORD0)
{    
    out_pos = mul(pos, WorldViewProjectionMatrix);
    out_diffuse = diffuse;
    out_uv0 = uv0;
}


float4 psBloomH( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = 0;
    
    for (int i = 0; i < g_cKernelSize; i++)
    {   
        Color += tex2D( SceneSampler, Tex + float2(TexelKernel[i].x, 0) ) * BlurWeights[i];
    }

    return Color * BloomScale;
}


float4 psBloomV( float2 Tex : TEXCOORD0 ) : COLOR0
{
    float4 Color = 0;
    
    for (int i = 0; i < g_cKernelSize; i++)
    {    
        Color += tex2D( SceneSampler, Tex + float2(0, TexelKernel[i].y) ) * BlurWeights[i];
    }

    return Color * BloomScale;
}


technique BloomHPass
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsQuadMain();
        PixelShader  = compile ps_2_0 psBloomH();
        ZEnable = false;
    }
}


technique BloomVPass
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsQuadMain();
        PixelShader  = compile ps_2_0 psBloomV();
        ZEnable = false;
    }
}

