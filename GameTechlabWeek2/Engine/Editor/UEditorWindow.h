#pragma once

#include "../GEngine.h"
#include "../FRenderer.h"
#include <Windows.h>


class UEditorWindow
{
public:
	UEditorWindow() = default;
	virtual ~UEditorWindow() = default;

	void startEditor(HWND Hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
	virtual void updateEditor(FRenderer &renderer) = 0;
	void endEditor();
};

