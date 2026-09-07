#include "UPepeComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData UPepeComponent::GetRenderData(FStringView Type)
{
	return Super::GetRenderData("Pepe");
}