#pragma once

#include "Engine/GEngine.h"
#include <Windows.h>

class FEditor;

class UEditorWindow
{
protected:

	FEditor* Editor;

public:

	virtual void Initialize(FEditor* InEditor);

	virtual void Render(float DeltaTime) {}
};

