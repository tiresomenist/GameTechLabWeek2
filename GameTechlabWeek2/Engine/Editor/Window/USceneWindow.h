#pragma once

#include "UEditorWindow.h"
#include "../../../Matrix.h"
#include "../../Object/Primitive/UPrimitiveComponent.h"
#include "../../../Container/FString.h"

class USceneWindow : public UEditorWindow
{
private:
	uint32 numberOfSpawn = 0;
	FWideString sceneName = L"Default";
	UPrimitiveComponent spawnPrimitive; // Todo : default를 Sphere로 

public:
	USceneWindow() = default;
	~USceneWindow() = default;

	void SpawnPrimitive();
	void MakeNewScene();
	void SaveCurrentScene();
	void LoadSavedScene();

	void UpdateEditorWindow(float fps, bool& bIsOrthogonal, float& fov, FVector& cameralocation, FVector& camerarotation);
};