#include "UCubeComponent.h"
#include "Engine/GResourceManager.h"

FPrimitiveRenderData UCubeComponent::GetRenderData()
{
	return Super::CreateRenderData(this, "Cube");
}