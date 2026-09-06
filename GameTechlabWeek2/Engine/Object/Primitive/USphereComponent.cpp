#include "USphereComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData USphereComponent::GetRenderData()
{
	return Super::CreateRenderData(this, "Sphere");
}