#pragma once

#include "UEditorWindow.h"
#include "../../../Engine/Object/FClassType.h"
#include "../../../Matrix.h"
#include "../../Object/Primitive/UPrimitiveComponent.h"
#include "../../../Container/FString.h"

class USceneWindow : public UEditorWindow
{


private:
	bool bOrthogonal = false;
	uint32 NumberOfSpawn = 0;
	uint32 SelectedIndex = 0;
	float FOV = 0;
	FVector CameraLocation = { 0.0f, 0.0f, 0.0f };
	FVector CameraRotation = { 0.0f, 0.0f, 0.0f };
	FClassType* SelectedClass = nullptr;
	TArray<FClassType*> Spawnables;
	FWideString SceneName = L"Default";
	//UPrimitiveComponent SelectedPrimitive; // Todo : default를 Sphere로 

public:
	USceneWindow() = default;
	~USceneWindow() = default;

	void SpawnPrimitive();
	void MakeNewScene();
	void SaveCurrentScene();
	void LoadSavedScene();
	void UpdateOrthogonal();
	void UpdateFOV();
	void UpdateCameraLocation();
	void UpdateCameraRotation();

	void Begin();
	void End();
	void Tick(); 
};