// GridShader.hlsl

cbuffer TransformBuffer : register(b0)
{
    row_major float4x4 MVP;
};

cbuffer GridConstants : register(b1)
{
    float3 CameraPos;
    float Padding;
};

struct VS_INPUT
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 WorldPos : POSITION1;
};

VS_OUTPUT VS_Grid(VS_INPUT input)
{
    VS_OUTPUT output;


    float2 gridOrigin = floor(CameraPos.xy);
    float3 worldPos = input.Pos + float3(gridOrigin, 0.0f);
    
    // 화면(Clip Space) 좌표 계산
    output.Pos = mul(float4(worldPos, 1.0f), MVP);
    
    // 월드 좌표를 픽셀 셰이더로 전달
    output.WorldPos = worldPos;
    
    return output;
}

float4 PS_Grid(VS_OUTPUT input) : SV_Target
{
    // 수학적 모듈러(fmod) 연산: 좌표가 1.0 단위로 떨어지는지 확인
    // x나 y 좌표를 1.0으로 나눈 나머지(frac)를 이용해 선의 위치를 찾음
    float2 gridUV = input.WorldPos.xy;
    
    float thickness = 0.001f;
    
    // fmod 또는 frac 연산으로 선분이 지나갈 자리를 계산 (0.0 근처일 때 선을 그림)
    float2 grid = abs(frac(gridUV - 0.5f) - 0.5f);
    float2 antiAliasWidth = max(fwidth(gridUV), float2(0.0001f, 0.0001f));
    float2 lineMask = 1.0f - smoothstep(thickness, thickness + antiAliasWidth, grid);
    float lineX = lineMask.x;
    float lineY = lineMask.y;
    
    // X선이나 Y선 중 하나라도 해당되면 선을 그림
    float gridLine = max(lineX, lineY);
    
    // 만약 선이 아니면 날려
    if (gridLine <= 0.001f)
    {
        discard;
    }
    
    // 거리 기반 페이드아웃 (Fade-out)
    // 카메라 위치에서 현재 픽셀까지의 거리
    float dist = distance(CameraPos, input.WorldPos);
    
    float alpha = 1.0f - smoothstep(20.0f, 40.0f, dist);
    
    // 선의 색상 (회색)과 계산된 투명도(Alpha)를 반환
    return float4(0.5f, 0.5f, 0.5f, alpha * gridLine);
}
