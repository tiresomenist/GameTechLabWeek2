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
	
	// ImGUI
	virtual void RenderImGUI();


	// NOTE: 언젠가 추상화 계층을 깊게 깊게 도입한다면, ImGUI를 UGizmo 내부에서 include 해선 안되며
	// UI 클래스를 따로 만들어서 해당 클래스의 구현부가 ImGUI를 직접 쓰고
	// UGizmo는 UI를 그리기 위해 해당 클래스를 사용해서만 구현해야함
	// 하지만 이건 좀 먼 이야기...

};
