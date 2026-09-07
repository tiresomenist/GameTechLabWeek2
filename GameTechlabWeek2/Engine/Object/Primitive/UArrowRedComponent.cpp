#include "UArrowRedComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData UArrowRedComponent::GetRenderData(FStringView Type)
{
	return Super::GetRenderData("ArrowRed");
}