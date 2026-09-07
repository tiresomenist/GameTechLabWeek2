#include "UGrid.h"
#include "../../Engine/Object/UObject.h"
#include "../../Engine/Object/FClassType.h"
#include "../../Engine/Renderer/FVertexSimple.h"

void UGrid::Initialize(FEditor* InEditor)
{
	Editor = InEditor;
}

TArray<FPrimitiveRenderData> UGrid::GetRenderData()
{
	return TArray<FPrimitiveRenderData>();
}