#pragma once

#include <d3d11.h>

#include "Container/TArray.h"
#include "Engine/Renderer/FVertexSimple.h"
#include "Engine/Core.h"

struct FMeshResource
{
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;
	UINT VertexCount = 0;
	UINT IndexCount = 0;
	UINT Stride = 0;

	TArray<FVertexSimple> vertexs;
	TArray<uint32> indexes;
};
