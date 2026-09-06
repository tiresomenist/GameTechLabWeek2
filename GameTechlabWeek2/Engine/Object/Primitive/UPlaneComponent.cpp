#include "UPlaneComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData UPlaneComponent::GetRenderData(FStringView Type)
{
	return Super::GetRenderData("Plane");
}
