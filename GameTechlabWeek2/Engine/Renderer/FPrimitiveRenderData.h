#pragma once

#include <d3d11.h>

struct FMatrix;

struct FPrimitiveRenderData
{
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	UINT                Stride;
	UINT                IndexCount;
	D3D11_PRIMITIVE_TOPOLOGY Topology;

	ID3D11ShaderResourceView* Material;       // VS/PS, 텍스처 SRV 등을 들고 있는 객체
	const FMatrix* WorldMatrix;    // 컴포넌트가 소유한 월드행렬 가리키기
};