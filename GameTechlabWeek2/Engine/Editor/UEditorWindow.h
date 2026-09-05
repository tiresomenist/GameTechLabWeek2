#pragma once

#include "../GEngine.h"
#include "../../URenderer.h"
#include <Windows.h>


class UEditorWindow
{
public:
	UEditorWindow() = default;
	~UEditorWindow() = default;

	void startEditor(HWND Hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
	void updateEditor(URenderer &renderer);
	void endEditor();
};

