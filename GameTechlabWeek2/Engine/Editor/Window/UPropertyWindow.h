#pragma once
#include "UEditorWindow.h"
#include "../../../Matrix.h"
#include "../../../Container/FString.h"

class UPropertyWindow : public UEditorWindow
{
public:
	~UPropertyWindow() = default;

	void UpdateEditorWindow(FVector& translation, FVector& rotation, FVector& scale);
};