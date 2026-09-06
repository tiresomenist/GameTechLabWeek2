#include "UPlaneComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData UPlaneComponent::GetRenderData()
{
	return Super::CreateRenderData(this, "Plane");
}
