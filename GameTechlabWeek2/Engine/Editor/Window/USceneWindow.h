#pragma once

#include "UEditorWindow.h"
#include "../../../Matrix.h"
#include "../../Object/Primitive/UPrimitiveComponent.h"
#include "../../../Container/FString.h"

class USceneWindow : public UEditorWindow
{
private:
	float currentFPS = 0;
	uint32 numberOfSpawn = 0;
	UPrimitiveComponent spawnPrimitive; // Todo : default를 Sphere로 
	FWideString sceneNawme = L"Default";
	bool bIsOrthogonal = false;
	/* Camera Info */
	uint32 FOV = 60;
	FVector cameraLocation = { 0.0f, 0.0f, 0.0f }; // Todo : 카메라 객체에서 값을 받아와서 초기값 설정
	FVector cameraRotation = { 0.0f, 0.0f, 0.0f }; // Todo : 카메라 객체에서 값을 받아와서 초기값 설정
	/*             */
public:
	USceneWindow() = default;
	~USceneWindow() = default;

	void SpawnPrimitive();
	void MakeNewScene();
	void SaveCurrentScene();
	void LoadSavedScene();
	void UpdateCamerInfo();
};

