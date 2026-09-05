#include "UCubeComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData UCubeComponent::GetRenderData(FStringView Type)
{
	return Super::GetRenderData("Cube");
}