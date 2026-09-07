#pragma once
#include "Engine/Editor/Window/UEditorWindow.h"
#include "../../../Matrix.h"
#include "../../../FQuaternion.h"
#include "../../../Container/FString.h"

class UPropertyWindow : public UEditorWindow
{
private:
	FVector Translation = { 0.0f, 0.0f, 0.0f };
	FQuaternion Rotation;
	FVector OScale = { 0.0f, 0.0f, 0.0f };
public:
	
	void UpdateTranslation();
	void UpdateRotation();
	void UpdateScale();

	void Render() override;
};