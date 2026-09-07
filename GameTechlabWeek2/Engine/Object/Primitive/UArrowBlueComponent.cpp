#include "UArrowBlueComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData UArrowBlueComponent::GetRenderData(FStringView Type)
{
	return Super::GetRenderData("ArrowBlue");
}