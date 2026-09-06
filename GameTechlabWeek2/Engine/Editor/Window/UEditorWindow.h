#pragma once

#include "../../Object/UObject.h"
#include "../../../Container/TArray.h"
#include <Windows.h>


class UEditorWindow {
public:
	UEditorWindow() = default;
	virtual ~UEditorWindow() = default;
	virtual void Begin() = 0; // 멤버 변수를 자주 사용하게될 GEngine이 가지는 요소를 가리키게 합니다.
	virtual void Tick() = 0; // ImGui가 업데이트 됩니다.
	virtual void End() = 0; // Begin때 업데이트한 멤버 변수를 nullptr로 바꿉니다.
};