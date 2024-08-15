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

float4 PSMain(PS_INPUT input) : SV_TARGET
{
    int index = input.inTexIndex;
    float4 pixel = float4(0.0, 0.5, 0.5, 0.5);
    
    //switch (index)
    //{
    //    case 0:  pixel = objTexture[0].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 1:  pixel = objTexture[1].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 2:  pixel = objTexture[2].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 3:  pixel = objTexture[3].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 4:  pixel = objTexture[4].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 5:  pixel = objTexture[5].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 6:  pixel = objTexture[6].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 7:  pixel = objTexture[7].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 8:  pixel = objTexture[8].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 9:  pixel = objTexture[9].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 10: pixel = objTexture[10].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 11: pixel = objTexture[11].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 12: pixel = objTexture[12].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 13: pixel = objTexture[13].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 14: pixel = objTexture[14].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 15: pixel = objTexture[15].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 16: pixel = objTexture[16].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 17: pixel = objTexture[17].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 18: pixel = objTexture[18].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 19: pixel = objTexture[19].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 20: pixel = objTexture[20].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 21: pixel = objTexture[21].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 22: pixel = objTexture[22].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 23: pixel = objTexture[23].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 24: pixel = objTexture[24].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 25: pixel = objTexture[25].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 26: pixel = objTexture[26].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 27: pixel = objTexture[27].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 28: pixel = objTexture[28].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 29: pixel = objTexture[29].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 30: pixel = objTexture[30].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //    case 31: pixel = objTexture[31].Sample(objSampler, input.inTexCoord) * input.inColor; break;
    //}    
    return pixel;
}