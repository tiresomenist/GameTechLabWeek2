// ShaderW0.hlsl
cbuffer constants : register(b0)
{
    row_major float4x4 MVP;
}


struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
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
    
    output.color = input.color;
    
    return output;
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    return input.color;
}

VS_OUTPUT VS_Highlight(VS_INPUT input)
{
    VS_OUTPUT output;
    
    float3 expandedPos = input.position * 1.05f;
    
    output.Pos = mul(float4(expandedPos, 1.0f), MVP);
    
    return output;
}

float4 PS_Highlight(VS_OUTPUT input) : SV_Target
{
    return float4(1.0f, 1.0f, 0.0f, 1.0f);
}

}

//cbuffer CameraBuffer : register(b0)
//{
//    matrix MVP;
//    float3 CameraPos;
//    float Padding;
//};

//// 정점 셰이더에서 '월드 좌표(WorldPos)'를 픽셀 셰이더로 넘겨주도록 수정해야 합니다.
//struct VS_OUTPUT
//{
//    float4 Pos : SV_POSITION;
//    float3 WorldPos : POSITION1; // 현재 픽셀의 진짜 3D 월드 좌표
//};

//float4 PS_Grid(VS_OUTPUT input) : SV_Target
//{
//    // 1. 수학적 모듈러(fmod) 연산: 좌표가 1.0 단위로 떨어지는지 확인
//    // x나 z 좌표를 1.0으로 나눈 나머지(frac)를 이용해 선의 위치를 찾습니다.
//    float2 gridUV = input.WorldPos.xz;
    
//    // 선의 두께 설정
//    float thickness = 0.02f;
    
//    // fmod 또는 frac 연산으로 선분이 지나갈 자리를 계산 (0.0 근처일 때 선을 그림)
//    float2 grid = abs(frac(gridUV - 0.5f) - 0.5f);
//    float lineX = step(grid.x, thickness);
//    float lineZ = step(grid.y, thickness);
    
//    // X선이나 Z선 중 하나라도 해당되면 1.0 (선이 그려짐)
//    float gridLine = max(lineX, lineZ);
    
//    // 2. 만약 선이 아니면 투명하게 날려버림
//    if (gridLine == 0.0f)
//    {
//        discard; // 픽셀을 아예 그리지 않고 버림 (성능 대폭 향상!)
//    }
    
//    // 3. 거리 기반 페이드아웃 (Fade-out)
//    // 카메라 위치에서 현재 픽셀까지의 거리를 구합니다.
//    float dist = distance(CameraPos, input.WorldPos);
    
//    // 예: 50.0f 거리부터 서서히 투명해져서 100.0f에서 완전 투명해짐
//    float alpha = 1.0f - smoothstep(50.0f, 100.0f, dist);
    
//    // 4. 선의 색상 (회색)과 계산된 투명도(Alpha)를 반환
//    return float4(0.5f, 0.5f, 0.5f, alpha);
//}