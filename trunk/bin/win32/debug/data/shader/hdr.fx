shared float Time;
shared float4x4 WorldMatrix;
shared float4x4 ViewMatrix;
shared float4x4 ProjectionMatrix;
shared float4x4 WorldViewProjectionMatrix;

texture DiffuseMap;

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
    float4 diffuse      : COLOR0;
    float2 uv0          : TEXCOORD0;
};

struct VsOutput
{
    float4 pos          : POSITION;
    float4 diffuse      : COLOR0;
    float2 uv0          : TEXCOORD0;
};

VsOutput vsQuadMain(VsInput input)
{
    VsOutput output;
    
    output.pos = mul(input.pos, WorldViewProjectionMatrix);
    output.diffuse = input.diffuse;
    output.uv0 = input.uv0;
    return output;
}

float4 psComposeMain(VsOutput input) : COLOR
{
    float4 output;
    output = tex2D(DefaultSampler, input.uv0) * input.diffuse;
    return output;
}



float Luminance = 0.08f;
static const float fMiddleGray = 0.18f;
static const float fWhiteCutoff = 0.8f;

float4 psBrightPassFilter(float2 uv0 : TEXCOORD0) : COLOR0
{
    float3 color = tex2D(DefaultSampler, uv0);
    
    color *= fMiddleGray / (Luminance + 0.001f);
    color *= (1.0f + (color / (fWhiteCutoff * fWhiteCutoff)));
    color -= 5.0f;
    color = max(color, 0);
    color /= (10 + color);
    return float4(color, 1);
}

technique ComposeScene
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsQuadMain();
        PixelShader  = compile ps_2_0 psComposeMain();
    }
}

technique BrightPass
{
    pass P0
    {
        VertexShader = compile vs_2_0 vsQuadMain();
        PixelShader  = compile ps_2_0 psBrightPassFilter();
        ZEnable = false;
    }
}