#include "UArrowGreenComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData UArrowGreenComponent::GetRenderData(FStringView Type)
{
	return Super::GetRenderData("ArrowGreen");
}