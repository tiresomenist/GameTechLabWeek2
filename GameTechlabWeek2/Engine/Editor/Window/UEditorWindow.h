#pragma once

#include "../../GEngine.h"
#include "../../FRenderer.h"
#include "../../../Container/TArray.h"
#include <Windows.h>


class UEditorWindow : public UObject
{
public:
	UEditorWindow() = default;

	virtual ~UEditorWindow() = 0;
	virtual void UpdateEditorWindow() = 0;


	//Todo : FEditor에서 해야할 작업 관련 함수들 이므로 옮겨야함                                                         
	void startEditor(HWND Hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
	void updateEditor(FRenderer& renderer);
	void endEditor();
};