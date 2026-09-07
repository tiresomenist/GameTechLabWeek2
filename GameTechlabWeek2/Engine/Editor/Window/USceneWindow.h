#pragma once

#include "UEditorWindow.h"
#include "../../../Engine/Object/FClassType.h"
#include "../../../Matrix.h"
#include "../../Object/Primitive/UPrimitiveComponent.h"
#include "../../../Container/FString.h"

class USceneWindow : public UEditorWindow
{
private:
	uint32 NumberOfSpawn = 0;
	uint32 SelectedIndex = 0;
	FClassType SelectedClass;
	FWideString SceneName = L"Default";

public:
	void SpawnPrimitive();
	void MakeNewScene();
	void SaveCurrentScene();
	void LoadSavedScene();

	void Render() override;
};