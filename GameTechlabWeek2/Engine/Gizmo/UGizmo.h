#pragma once
#include "Container/TArray.h"
#include "Engine/Editor/FEditor.h"
#include "Engine/Renderer/FPrimitiveRenderData.h"
#include "Engine/Object/UObject.h"

class UGizmo : public UObject
{

    UCLASS(UGizmo, "Gizmo", UObject)

private:

	FEditor* Editor = nullptr;

public:

	void Initialize(FEditor* InEditor);

	// 렌더러에게 전달할 렌더 정보
	virtual TArray<FPrimitiveRenderData> GetRenderData();

};
