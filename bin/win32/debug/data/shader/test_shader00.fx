shared float Time;
shared float4x4 WorldViewProjectionMatrix;

texture Diffuse;

sampler DefaultSampler =
sampler_state
{
    Texture = <Diffuse>;
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

VsOutput VertexShaderMain(VsInput input)
{
    VsOutput output;
        
    output.pos = mul(input.pos, WorldViewProjectionMatrix);
    output.diffuse = input.diffuse;
    output.uv0 = input.uv0;
    return output;
}

float4 PixelShaderMain(VsOutput input) : COLOR
{
    float4 output;
    output = input.diffuse;
    return output;
}

technique Test
{
    pass P0
    {
        CullMode = None;
        Lighting = False;

        VertexShader = compile vs_2_0 VertexShaderMain();
        PixelShader  = compile ps_2_0 PixelShaderMain();
    }
}
