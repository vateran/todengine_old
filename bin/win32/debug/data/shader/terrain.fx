shared float4x4 WorldMatrix;
shared float4x4 ViewMatrix;
shared float4x4 ProjectionMatrix;

shared float4x4 WorldViewMatrix;
shared float4x4 WorldViewProjectionMatrix;

shared float4x4 InvWorldMatrix;
shared float4x4 InvViewMatrix;
shared float4x4 RevViewMatrix;
shared float4x4 InvWorldViewMatrix;
shared float4x4 InvWorldViewProjectionMatrix;

float3 DirLight = float3(0, 0, -1);

float4 i_a : LIGHTAMBIENT <string name="Light Ambient";> = {1, 1, 1, 1};
float4 i_d : LIGHTDIFFUSE <string name="Light Diffuse";> = {1, 1, 1, 1};
float4 i_s : LIGHTSPECULAR <string name="Light Specular";> = {1, 1, 1, 1};

float4 k_a : MATERIALAMBIENT <string name="Material Ambient";> = {1, 1, 1, 1};
float4 k_d : MATERIALDIFFUSE <string name="Material Diffuse";> = {1, 1, 1, 1};
float4 k_s : MATERIALSPECUAL <string name="Material Specular";> = {1, 1, 1, 1}; 

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
    float3 normal       : NORMAL;
    float2 uv0          : TEXCOORD0;
};

struct VsOutput
{
    float4 pos          : POSITION;
    float4 diffuse      : COLOR0;
    float2 uv0          : TEXCOORD0;
    float3 normal       : TEXCOORD1;
    float3 eye          : TEXCOORD2;
    float3 light        : TEXCOORD3;
};

VsOutput TerrainVertexShaderMain(VsInput input)
{
    VsOutput output;    
    output.pos = mul(input.pos, WorldViewProjectionMatrix);
    output.uv0 = input.uv0;
    output.normal = input.normal;
    
    output.light = -normalize(mul(DirLight, InvWorldMatrix));
    float4 eye_pos = mul(float4(0, 0, 0, 1), InvWorldViewMatrix);
    output.eye = normalize(eye_pos - input.pos);
    
    output.diffuse = i_a * k_a + i_d * k_d * input.diffuse * max(0, dot(DirLight, input.normal));
    
    return output;
}

float4 TerrainPixelShaderMain(VsOutput input) : COLOR
{   
    return float4(1, 1, 1, 1);
    float3 L = normalize(input.light);
	float3 V = normalize(input.eye);
	float3 N = normalize(input.normal);
	float3 H = normalize(V + L);
	
	float m = 0.3f;
	float NH = dot(N, H);
	float NH2 = pow(NH, 2);
	float m2 = pow(m, 2);
	float D = exp((-1 + NH2) / (m2 * NH2)) / (4 * m2 * pow(NH2, 2));
	
	float NV = dot(N, V);
	float VH = dot(V, H);
	float NL = dot(N, L);
	
	float Ga = (2 * NH * NV) / VH;
	float Gb = (2 * NH * NL) / VH;
	float G = min(min(Ga, Gb), 1);
	
	float n = 4;
	float c = dot(L, H);
	float g = sqrt(pow(n, 2) + pow(c, 2) - 1);
	float F = 0.5 * pow((g - c)/ (g + c), 2) * (1 + (pow((c * (g + c) -1) / (c * (g - c) + 1), 2)));
	
	float4 ks = i_s * k_s;
	return tex2D(DefaultSampler, input.uv0) * input.diffuse + ks * max(0, (D * G * F) / NV);
}

technique Terrain
{
    pass P0
    {
        VertexShader = compile vs_2_0 TerrainVertexShaderMain();
        PixelShader  = compile ps_2_0 TerrainPixelShaderMain();
    }
}

