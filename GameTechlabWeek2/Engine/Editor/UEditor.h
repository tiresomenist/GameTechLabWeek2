#pragma once

#include "../GEngine.h"
#include "../../URenderer.h"
#include <Windows.h>


class UEditor : public GEngine
{
public:
	UEditor() = default;
	~UEditor() = default;

	void startEditor(HWND Hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
	void updateEditor(URenderer &renderer);
	void endEditor();
};

