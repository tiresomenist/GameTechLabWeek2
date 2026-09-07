#include "UCubeComponent.h"
#include "Engine/GResourceManager.h"
#include "Engine/Primitive/GPrimitive.h"

FPrimitiveRenderData UCubeComponent::GetRenderData()
{
	return Super::CreateRenderData(this, GPrimitive::GetCube());
}