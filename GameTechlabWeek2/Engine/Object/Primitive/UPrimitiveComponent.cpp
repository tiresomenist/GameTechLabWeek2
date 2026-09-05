#include "UPrimitiveComponent.h"
#include "../FObjectFactory.h"

FClassType* UPrimitiveComponent::GetClass()
{
    static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
        {
            return new UPrimitiveComponent(UUID, InternalIndex, InClassType);
        };

    static FClassType Type{ "UPrimitiveComponent", CreateObject, USceneComponent::GetClass() };
    return &Type;
}


UPrimitiveComponent::~UPrimitiveComponent()
{
	if (VertexBuffer) { VertexBuffer->Release(); VertexBuffer = nullptr; }
	if (IndexBuffer) { IndexBuffer->Release(); IndexBuffer = nullptr; }
}

void UPrimitiveComponent::InitGeometry(ID3D11Buffer* InVB, ID3D11Buffer* InIB, uint32 InStride, uint32 InCount)
{
    if (VertexBuffer) VertexBuffer->Release();
    if (IndexBuffer) IndexBuffer->Release();

    VertexBuffer = InVB;
    IndexBuffer = InIB;
    VertexStride = InStride;
    IndexCount = InCount;
}

FPrimitiveRenderData UPrimitiveComponent::GetRenderData() const
{
    FPrimitiveRenderData Data;
    Data.VertexBuffer = VertexBuffer;
    Data.IndexBuffer = IndexBuffer;
    Data.Stride = VertexStride;
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
