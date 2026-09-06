#include "USphereComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData USphereComponent::GetRenderData(FStringView Type)
{
	return Super::CreateRenderData(this, "Sphere");
}