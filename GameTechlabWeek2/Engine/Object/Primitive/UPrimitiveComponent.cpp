#include "UPrimitiveComponent.h"
#include "Engine/GResourceManager.h"
#include "Engine/Primitive/FMeshResource.h"
#include "Engine/Primitive/GPrimitive.h"

FPrimitiveRenderData UPrimitiveComponent::GetRenderData()
{
	GResourceManager& ResourceManager = *GResourceManager::GetInstance();
	FMeshResource* MeshResource = ResourceManager.GetPrimitive(FString{ Type });

FPrimitiveRenderData UPrimitiveComponent::CreateRenderData(UPrimitiveComponent* self, FMeshResource* Resource)
{
	FPrimitiveRenderData RenderData{};

	if (Resource == nullptr) { return RenderData; }

	RenderData.VertexBuffer		= Resource->VertexBuffer;
	RenderData.IndexBuffer		= Resource->IndexBuffer;
	RenderData.IndexCount		= Resource->IndexCount;
	RenderData.Stride			= Resource->Stride;
 // RenderData.Material			= &GetMaterial();
	RenderData.WorldMatrix		= &(self->GetWorldMatrix());

	return RenderData;
}
