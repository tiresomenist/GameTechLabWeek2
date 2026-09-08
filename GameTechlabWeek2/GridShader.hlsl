// GridShader.hlsl

cbuffer TransformBuffer : register(b0)
{
    matrix MVP; // (또는 row_major float4x4 MVP;)
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
    
    // 1. 화면(Clip Space) 좌표 계산 (기존 b0의 MVP 사용)
    output.Pos = mul(float4(input.Pos, 1.0f), MVP);
    
    // 2. 월드 좌표를 픽셀 셰이더로 전달
    // 그리드는 보통 원점(0,0,0)에 고정된 거대한 판이므로, 
    // 입력된 정점의 로컬 좌표(input.Pos)가 곧 월드 좌표가 됩니다.
    output.WorldPos = input.Pos;
    
    return output;
}

float4 PS_Grid(VS_OUTPUT input) : SV_Target
{
    // 1. 수학적 모듈러(fmod) 연산: 좌표가 1.0 단위로 떨어지는지 확인
    // x나 z 좌표를 1.0으로 나눈 나머지(frac)를 이용해 선의 위치를 찾습니다.
    float2 gridUV = input.WorldPos.xz;
    
    // 선의 두께 설정
    float thickness = 0.02f;
    
    // fmod 또는 frac 연산으로 선분이 지나갈 자리를 계산 (0.0 근처일 때 선을 그림)
    float2 grid = abs(frac(gridUV - 0.5f) - 0.5f);
    float lineX = step(grid.x, thickness);
    float lineZ = step(grid.y, thickness);
    
    // X선이나 Z선 중 하나라도 해당되면 1.0 (선이 그려짐)
    float gridLine = max(lineX, lineZ);
    
    // 만약 선이 아니면 날려
    if (gridLine == 0.0f)
    {
        discard;
    }
    
    // 3. 거리 기반 페이드아웃 (Fade-out)
    // 카메라 위치에서 현재 픽셀까지의 거리를 구합니다.
    float dist = distance(CameraPos, input.WorldPos);
    
    // 예: 50.0f 거리부터 서서히 투명해져서 100.0f에서 완전 투명해짐
    float alpha = 1.0f - smoothstep(50.0f, 100.0f, dist);
    
    // 4. 선의 색상 (회색)과 계산된 투명도(Alpha)를 반환
    return float4(0.5f, 0.5f, 0.5f, alpha);
}