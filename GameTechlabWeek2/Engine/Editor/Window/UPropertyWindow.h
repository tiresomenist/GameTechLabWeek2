#pragma once
#include "Engine/Editor/Window/UEditorWindow.h"
#include "../../../Matrix.h"
#include "../../../FQuaternion.h"
#include "../../../Container/FString.h"

class UPropertyWindow : public UEditorWindow
{
private:
	FVector Translation;
	FVector Rotation;
	FVector OScale;
public:
	
	void UpdateTranslation();
	void UpdateRotation();
	void UpdateScale();

	void Render() override;
};