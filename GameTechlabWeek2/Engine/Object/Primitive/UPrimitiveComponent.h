#pragma once
#include "../USceneComponent.h"
#include <d3d11.h>
#include <DirectXcollision.h>
#include "Engine/Renderer/FPrimitiveRenderData.h"

class UPrimitiveComponent : public USceneComponent
{
    UCLASS(UPrimitiveComponent, "PrimitiveComponent", USceneComponent)

public:
    ~UPrimitiveComponent();

    void InitGeometry(ID3D11Buffer* InVB, ID3D11Buffer* InIB, uint32 InStride, uint32 InCount);

    FPrimitiveRenderData GetRenderData() const;
    //DirectX::BoundingBox GetWorldBoundingBox() const;

    // @RTTI
    void UpdateGeometry(ID3D11Buffer* NewVB, ID3D11Buffer* NewIB, uint32 InStride, uint32 InIndexCount);

protected:
    UPrimitiveComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
        : USceneComponent(InUUID, InInternalIndex, InClassType) {}

protected:
    // GPU Buffers
    ID3D11Buffer* VertexBuffer = nullptr;
    ID3D11Buffer* IndexBuffer = nullptr;
    uint32 VertexStride = 0;
    uint32 IndexCount = 0;

    D3D_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    // For Picking & Culling (Local)
    DirectX::BoundingBox LocalBoundingBox;
};

