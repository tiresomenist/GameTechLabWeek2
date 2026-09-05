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
	UPrimitiveComponent SpawnPrimitive; // Todo : default를 Sphere로 

public:
	USceneWindow() = default;
	~USceneWindow() = default;

	void SpawnPrimitive();
	void MakeNewScene();
	void SaveCurrentScene();
	void LoadSavedScene();

	void UpdateEditorWindow(float fps, bool& bIsOrthogonal, float& fov, FVector& cameralocation, FVector& camerarotation);
};