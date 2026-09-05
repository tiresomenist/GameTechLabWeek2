#pragma once
#include "UEditorWindow.h"
#include "../../../Matrix.h"
#include "../../../Container/FString.h"

class UPropertyWindow : public UEditorWindow
{
private:
	FVector Translation = { 0.0f, 0.0f, 0.0f };
	FVector Rotation = { 0.0f, 0.0f, 0.0f };
	FVector Scale = { 0.0f, 0.0f, 0.0f };
public:
	UPropertyWindow() = default;
	~UPropertyWindow() = default;
	void UpdatePropertyInfo(FVector translation, FVector rotation, FVector scale);
};