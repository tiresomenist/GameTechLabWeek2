#include "UPrimitiveComponent.h"

UPrimitiveComponent::~UPrimitiveComponent()
{
	if (VertexBuffer) { VertexBuffer->Release(); VertexBuffer = nullptr; }
	if (IndexBuffer) { IndexBuffer->Release(); IndexBuffer = nullptr; }
}

FPrimitiveRenderData UPrimitiveComponent::GetRenderData() const
{
    FPrimitiveRenderData Data;
    Data.VertexBuffer = VertexBuffer;
    Data.IndexBuffer = IndexBuffer;
    Data.VertexStride = VertexStride;
    Data.IndexCount = IndexCount;
    Data.Topology = Topology;
    Data.WorldMatrix = &GetWorldMatrix();
    return Data;
}

//DirectX::BoundingBox UPrimitiveComponent::GetWorldBoundingBox() const
//{
//    DirectX::BoundingBox WorldBox;
//    LocalBoundingBox.Transform(WorldBox, GetWorldMatrix());
//    return WorldBox;
//}

void UPrimitiveComponent::UpdateGeometry(ID3D11Buffer* NewVB, ID3D11Buffer* NewIB, uint32 InStride, uint32 InIndexCount)
{
    // 기존 버퍼 Release
    if (VertexBuffer) { VertexBuffer->Release(); }
    if (IndexBuffer) { IndexBuffer->Release(); }

    // 새 버퍼 Set
    VertexBuffer = NewVB;
    IndexBuffer = NewIB;
    if (VertexBuffer) VertexBuffer->AddRef();
    if (IndexBuffer) IndexBuffer->AddRef();

    VertexStride = InStride;
    IndexCount = InIndexCount;
}