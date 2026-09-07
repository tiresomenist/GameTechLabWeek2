#include "UPrimitiveComponent.h"
#include "Engine/GResourceManager.h"
#include "Engine/Primitive/FMeshResource.h"
#include "Engine/Primitive/GPrimitive.h"


FPrimitiveRenderData UPrimitiveComponent::GetRenderData(FStringView Type)
{
	GResourceManager& ResourceManager = *GResourceManager::GetInstance();
	FMeshResource* MeshResource = ResourceManager.GetPrimitive(FString{ Type });

	FPrimitiveRenderData RenderData{};
	if (MeshResource == nullptr) { return RenderData; }

	RenderData.VertexBuffer = MeshResource->VertexBuffer;
	RenderData.IndexBuffer = MeshResource->IndexBuffer;
	RenderData.IndexCount = MeshResource->IndexCount;
	RenderData.Stride = MeshResource->Stride;
	// RenderData.Material			= &GetMaterial();
	RenderData.WorldMatrix = &GetWorldMatrix();

	return RenderData;

}