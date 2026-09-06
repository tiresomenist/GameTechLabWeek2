#include "UPrimitiveComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData UPrimitiveComponent::GetRenderData()
{
	return CreateRenderData(this, "");
}

FPrimitiveRenderData UPrimitiveComponent::CreateRenderData(UPrimitiveComponent* self, FStringView Type)
{
	GResourceManager& ResourceManager = *GResourceManager::GetInstance();
	FMeshResource* MeshResource = ResourceManager.GetOrCreatePrimitive(FString{ Type });

	FPrimitiveRenderData RenderData{};
	if (MeshResource == nullptr) { return RenderData; }

	RenderData.VertexBuffer		= MeshResource->VertexBuffer;
	RenderData.IndexBuffer		= MeshResource->IndexBuffer;
	RenderData.IndexCount		= MeshResource->IndexCount;
	RenderData.Stride			= MeshResource->Stride;
 // RenderData.Material			= &GetMaterial();
	RenderData.WorldMatrix		= &(self->GetWorldMatrix());

	return RenderData;
}
