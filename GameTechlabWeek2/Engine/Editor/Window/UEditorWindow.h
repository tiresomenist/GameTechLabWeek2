#pragma once

#include "Engine/GEngine.h"
#include "Imgui/imgui.h"
#include <Windows.h>

class FEditor;

class UEditorWindow
{
protected:

	FEditor* Editor;

public:

	virtual void Initialize(FEditor* InEditor);

	virtual void Render(float DeltaTime) {}

	void DrawItemBottomLine(uint32 Color, float Thickness);
};

