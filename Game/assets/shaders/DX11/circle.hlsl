cbuffer Camera : register(b0)
{
    float4x4 projection;
}

struct VS_INPUT
{
    float3 inPos           : aPosition;
    float3 inLocalPosition : aLocalPosition;
    float4 inColor         : aColor;
    float  inThickness     : aThickness;
    float  inFade          : aFade;
};

struct VS_OUTPUT
{
    float4 outPos           : SV_POSITION;
    float3 outLocalPosition : TEXCOORD0;
    float4 outColor         : COLOR;
    float  outThickness     : TEXCOORD1;
    float  outFade          : TEXCOORD2;
};

VS_OUTPUT VSMain(VS_INPUT input)
{
    VS_OUTPUT output;
    output.outLocalPosition = input.inLocalPosition;
    output.outColor = input.inColor;
    output.outThickness = input.inThickness;
    output.outFade = input.inFade;
    
    output.outPos = mul(projection, float4(input.inPos, 1.0));
    return output;
}

struct PS_INPUT
{
    float4 inPos           : SV_POSITION;
    float3 inLocalPosition : TEXCOORD0;
    float4 inColor         : COLOR;
    float  inThickness     : TEXCOORD1;
    float  inFade          : TEXCOORD2;
};

float4 PSMain(PS_INPUT input) : SV_TARGET
{
    float distance = 1.0 - length(input.inLocalPosition);
	
    float circle = smoothstep(0.0, input.inFade, distance);
    circle *= smoothstep(input.inThickness + input.inFade, input.inThickness, distance);

    if (circle == 0.0)
        discard;
    
    float4 pixelColor = input.inColor;
    pixelColor.a *= circle;
    
    return pixelColor;
}