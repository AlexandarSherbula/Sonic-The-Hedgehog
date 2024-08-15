cbuffer Camera : register(b0)
{
    float4x4 projection;
}

struct VS_INPUT
{
    float3 inPos      : aPosition;
    float4 inColor    : aColor;
    float2 inTexCoord : aTexCoord;
    int    inTexIndex : aTexIndex;
};

struct VS_OUTPUT
{
    float4 outPos      : SV_POSITION;
    float4 outColor    : COLOR;
    float2 outTexCoord : TEXCOORD0;
    int    outTexIndex : TEXCOORD1;
};

VS_OUTPUT VSMain(VS_INPUT input)
{
    VS_OUTPUT output;
    output.outPos = mul(projection, float4(input.inPos, 1.0));
    output.outColor = input.inColor;
    output.outTexCoord = input.inTexCoord;
    output.outTexIndex = input.inTexIndex;
    return output;
}

struct PS_INPUT
{
    float4 inPos      : SV_POSITION;
    float4 inColor    : COLOR;
    float2 inTexCoord : TEXCOORD;
    int    inTexIndex : TEXCOORD1;
};

Texture2D objTexture[32] : TEXTURE : register(t0);
SamplerState objSampler: SAMPLER : register(s0);

bool IsEqual(float4 color1, float4 color2, float epsilon)
{
    return all(abs(color1 - color2) < epsilon);
}

float4 PSMain(PS_INPUT input) : SV_TARGET
{
    int index = input.inTexIndex;
    
    float4 targetColor = float4(24.0 / 255.0, 136.0 / 255.0, 240.0 / 255.0, 1.0);
    float4 newColor = float4(0, 0, 1.0, 0.9);
    
    float4 pixel = float4(0.0, 0.5, 0.5, 0.7);
    objTexture[0].Sample(objSampler, input.inTexCoord) * input.inColor;
        
    if (IsEqual(pixel, targetColor, 0.1))
        pixel = newColor;
    
    return pixel;
}