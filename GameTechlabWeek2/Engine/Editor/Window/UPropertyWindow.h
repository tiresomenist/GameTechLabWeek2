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
	float SnapSize = 0.001f;
	int SelectedSnapIndex = 0;
	TArray<float> SnapSizeList = {0.001f, 0.01f, 0.1f, 1.0f, 5.0f};
	bool bScaleLock;
public:

	void GetSelectedValue();
	void SetSelectedValue();

	void DeleteSelected();

	void Render(float DeltaTime) override;
};