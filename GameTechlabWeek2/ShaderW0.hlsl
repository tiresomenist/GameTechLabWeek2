// ShaderW0.hlsl
cbuffer constants : register(b0)
{
    row_major float4x4 MVP;
}


struct VS_INPUT
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output;
    
    //MVP행렬 곱으로 위치 변환
    output.position = mul(float4(input.position.xyz, 1.0f), MVP);
    
    output.color = float4(abs(input.normal), 1.0f);
    
    return output;
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    return input.color;
}
