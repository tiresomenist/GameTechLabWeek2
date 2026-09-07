#pragma once

#include "Engine/GEngine.h"
#include <Windows.h>

class FEditor;

class UEditorWindow
{
protected:

	FEditor* Editor;

public:

	void Initialize(FEditor* InEditor);

	virtual void Render() {}
};

