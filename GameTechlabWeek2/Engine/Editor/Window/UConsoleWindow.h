#pragma once

#include "Engine/Editor/UEditorWindow.h"
#include "Matrix.h"
#include "Container/FString.h"

class UConsoleWindow : public UEditorWindow
{
public:
	void Render() override;
};

