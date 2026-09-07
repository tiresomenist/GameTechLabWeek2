#pragma once

#include "../GEngine.h"
#include "../FRenderer.h"
#include <Windows.h>

class FEditor;

class UEditorWindow
{
private: 
	
	FEditor* Editor;

public:
	void startEditor(HWND Hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);
	virtual void updateEditor() {}
	void endEditor();

	void Initialize(FEditor* InEditor);

	virtual void Render() {}
};

