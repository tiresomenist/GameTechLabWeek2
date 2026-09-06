#include "USphereComponent.h"
#include "Engine/GResourceManager.h"
#include "Engine/Primitive/GPrimitive.h"

FPrimitiveRenderData USphereComponent::GetRenderData()
{
	return Super::CreateRenderData(this, GPrimitive::GetSphere());
}