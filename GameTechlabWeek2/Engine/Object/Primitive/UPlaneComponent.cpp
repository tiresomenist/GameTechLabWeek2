#include "UPlaneComponent.h"
#include "Engine/GResourceManager.h"
#include "Engine/Primitive/GPrimitive.h"

FPrimitiveRenderData UPlaneComponent::GetRenderData()
{
	return Super::CreateRenderData(this, GPrimitive::GetPlane());
}
