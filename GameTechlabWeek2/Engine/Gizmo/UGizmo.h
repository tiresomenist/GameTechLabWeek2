#pragma once
#include "Container/TArray.h"
#include "Engine/Editor/FEditor.h"
#include "Engine/Renderer/FPrimitiveRenderData.h"
#include "Engine/Object/UObject.h"
#include "Engine/GResourceManager.h"


class UGizmo : public UObject
{

    UCLASS(UGizmo, "Gizmo", UObject)

protected:

	FEditor* Editor = nullptr;

public:

	void Initialize(FEditor* InEditor);

	// 렌더러에게 전달할 렌더 정보
	virtual TArray<FPrimitiveRenderData> GetRenderData();
	TArray<FMeshResource*> GetMeshResources() const {
		TArray< FMeshResource*> GizmoArray;
		GizmoArray.Add(GResourceManager::GetInstance()->GetPrimitive("ArrowRed"));		// X축
		GizmoArray.Add(GResourceManager::GetInstance()->GetPrimitive("ArrowGreen"));	// Y축
		GizmoArray.Add(GResourceManager::GetInstance()->GetPrimitive("ArrowBlue"));		// Z축
		return GizmoArray;
	}

};
