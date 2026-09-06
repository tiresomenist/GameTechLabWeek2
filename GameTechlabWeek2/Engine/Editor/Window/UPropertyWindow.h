#pragma once
#include "UEditorWindow.h"
#include "../../FEditor.h"
#include "../../../Matrix.h"
#include "../../../FQuaternion.h"
#include "../../../Container/FString.h"

class UPropertyWindow : public UEditorWindow
{
private:
	FVector Translation = { 0.0f, 0.0f, 0.0f };
	FQuaternion Rotation;
	FVector Scale = { 0.0f, 0.0f, 0.0f };
public:
	UPropertyWindow() = default;
	~UPropertyWindow() = default;
	void UpdatePropertyInfo(FVector translation, FQuaternion rotation, FVector scale);
};