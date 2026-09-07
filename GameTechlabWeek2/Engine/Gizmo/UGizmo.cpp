#include "UGizmo.h"
#include "FVertexSimple.h"
#include "Engine/Object/UObject.h"

void UGizmo::Initialize(FEditor* InEditor)
{
	Editor = InEditor;
}

TArray<FPrimitiveRenderData> UGizmo::GetRenderData()
{
	return TArray<FPrimitiveRenderData>();
}