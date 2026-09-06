#pragma once
#include "UEditorWindow.h"
#include "../../FEditor.h"
#include "../../../Matrix.h"
#include "../../../Container/FString.h"

class UPropertyWindow : public UEditorWindow
{
private:
	FVector Translation;
	FVector Rotation;
	FVector Scale;
	//FEditor& Editor;

public:
	UPropertyWindow() = default;
	~UPropertyWindow() = default;

	void UpdateTranslation();
	void UpdateRotation();
	void UpdateScale();
	void Begin();
	void Tick();
	void End();
};