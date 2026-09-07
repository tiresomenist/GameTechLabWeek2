#include "UOctopusComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData UOctopusComponent::GetRenderData(FStringView Type)
{
	return Super::GetRenderData("Octopus");
}