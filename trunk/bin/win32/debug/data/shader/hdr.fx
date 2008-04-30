shared float Time;
shared float4x4 WorldMatrix;
shared float4x4 ViewMatrix;
shared float4x4 ProjectionMatrix;
shared float4x4 WorldViewProjectionMatrix;

texture SceneMap;
texture ToneMap;

float Luminance = 0.08f;
static const float fMiddleGray = 0.18f;
static const float fWhiteCutoff = 0.8f;


sampler SceneSampler =
sampler_state
{
    Texture = <SceneMap>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = None;
};


sampler ToneSampler =
sampler_state
{
    Texture = <ToneMap>;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = None;
};


void vsQuad(
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


float4 psOpaque(
    float4 pos      : POSITION,
    float4 diffuse  : COLOR0,
    float2 uv0      : TEXCOORD0) : COLOR
{
    return tex2D(SceneSampler, uv0) * diffuse;
}


float4 psCompose(
    float4 pos      : POSITION,
    float4 diffuse  : COLOR0,
    float2 uv0      : TEXCOORD0) : COLOR
{
    return (tex2D(SceneSampler, uv0) + tex2D(ToneSampler, uv0)) * diffuse;
}


float4 psBrightPassFilter(float2 uv0 : TEXCOORD0) : COLOR0
{
    float3 color = tex2D(SceneSampler, uv0);
    
    color *= fMiddleGray / (Luminance + 0.001f);
    color *= (1.0f + (color / (fWhiteCutoff * fWhiteCutoff)));
    color -= 5.0f;
    color = max(color, 0);
    color /= (10 + color);
    return float4(color, 1);
}


technique ScenePass
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsQuad();
        PixelShader  = compile ps_2_0 psOpaque();
    }
}


technique OpaqueQuadPass
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsQuad();
        PixelShader  = compile ps_2_0 psOpaque();
    }
}


technique ComposeScenePass
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsQuad();
        PixelShader  = compile ps_2_0 psCompose();
    }
}


technique BrightPass
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsQuad();
        PixelShader  = compile ps_2_0 psBrightPassFilter();
        ZEnable = false;
    }
}
