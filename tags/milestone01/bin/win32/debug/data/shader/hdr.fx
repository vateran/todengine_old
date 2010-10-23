shared float Time;
shared float4x4 WorldMatrix;
shared float4x4 ViewMatrix;
shared float4x4 ProjectionMatrix;
shared float4x4 WorldViewProjectionMatrix;

texture SceneMap;
texture ToneMap;

float Luminance = 0.08f;
float ExposureLevel = 2;
float VinetteLevel = 1;

static const float fMiddleGray = 0.18f;
static const float fWhiteCutoff = 0.8f;

static const float g_csWidth = 800;
static const float g_csHeight = 600;

shared float2 PixelOffset = float2( 1.0 / g_csWidth, 1.0 / g_csHeight );

float2 PixelCoordsDownFilter[16] =
{
    { 1.5 / g_csWidth,  -1.5 / g_csHeight },
    { 1.5 / g_csWidth,  -0.5 / g_csHeight },
    { 1.5 / g_csWidth,   0.5 / g_csHeight },
    { 1.5 / g_csWidth,   1.5 / g_csHeight },

    { 0.5 / g_csWidth,  -1.5 / g_csHeight },
    { 0.5 / g_csWidth,  -0.5 / g_csHeight },
    { 0.5 / g_csWidth,   0.5 / g_csHeight },
    { 0.5 / g_csWidth,   1.5 / g_csHeight },

    {-0.5 / g_csWidth,  -1.5 / g_csHeight },
    {-0.5 / g_csWidth,  -0.5 / g_csHeight },
    {-0.5 / g_csWidth,   0.5 / g_csHeight },
    {-0.5 / g_csWidth,   1.5 / g_csHeight },

    {-1.5 / g_csWidth,  -1.5 / g_csHeight },
    {-1.5 / g_csWidth,  -0.5 / g_csHeight },
    {-1.5 / g_csWidth,   0.5 / g_csHeight },
    {-1.5 / g_csWidth,   1.5 / g_csHeight },
};


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


void vsCompose(
    float4 pos              : POSITION,
    float4 diffuse          : COLOR0,
    float2 uv0              : TEXCOORD0,
    out float4 out_pos      : POSITION,
    out float4 out_diffuse  : COLOR0,
    out float2 out_uv0      : TEXCOORD0)
{    
    out_pos = mul(pos, WorldViewProjectionMatrix);
    out_diffuse = diffuse;
    out_uv0 = uv0 + (PixelOffset * 0.5);
}


float4 psOpaque(
    float4 pos      : POSITION,
    float4 diffuse  : COLOR0,
    float2 uv0      : TEXCOORD0) : COLOR
{
    return tex2D(SceneSampler, uv0) * diffuse;
}


float4 psDownFilter(
    float4 pos      : POSITION,
    float4 diffuse  : COLOR0,
    float2 uv0      : TEXCOORD0) : COLOR
{
    float4 color = 0;

    for (int i = 0; i < 16; i++)
    {
        color += tex2D(SceneSampler, uv0 + PixelCoordsDownFilter[i].xy );
    }

    return color / 16;
}


float4 psCompose(
    float4 pos      : POSITION,
    float4 diffuse  : COLOR0,
    float2 uv0      : TEXCOORD0) : COLOR
{
    float4 original = tex2D(SceneSampler, uv0);
    float4 blur     = tex2D(ToneSampler, uv0);
   
    float4 color = lerp(original, blur, 0.4f);
    
    uv0 -= 0.5;
    float vignette = 1 - dot(uv0, uv0);
    color *= pow(vignette, VinetteLevel);
    color *= ExposureLevel;
    
    return color;
    
    //return (tex2D(SceneSampler, uv0) + tex2D(ToneSampler, uv0)) * diffuse;
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
        FillMode = Solid;
        CullMode = CCW;
    }
}


technique DownFilterPass
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsQuad();
        PixelShader  = compile ps_2_0 psDownFilter();
        FillMode = Solid;
        CullMode = CCW;
    }
}


technique OpaqueQuadPass
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsQuad();
        PixelShader  = compile ps_2_0 psOpaque();
        FillMode = Solid;
        CullMode = CCW;
    }
}


technique ComposeScenePass
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsCompose();
        PixelShader  = compile ps_2_0 psCompose();
        FillMode = Solid;
        CullMode = CCW;
    }
}


technique BrightPass
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsQuad();
        PixelShader  = compile ps_2_0 psBrightPassFilter();
        ZEnable = false;
        FillMode = Solid;
        CullMode = CCW;
    }
}
