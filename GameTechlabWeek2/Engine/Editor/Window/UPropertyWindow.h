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
	FVector Scale = { 0.0f, 0.0f, 0.0f };
public:
	UPropertyWindow()
	{
		Begin();
	}
	~UPropertyWindow() = default;
	
	void UpdateTranslation();
	void UpdateRotation();
	void UpdateScale();

	void Begin() override;
	void Tick() override;
	void End() override;
	void Render() override;
};