#pragma once

#include "UEditorWindow.h"
#include "../../../Engine/Object/FClassType.h"
#include "../../../Matrix.h"
#include "../../../Container/FString.h"
#include "../../../FQuaternion.h"

class USceneWindow : public UEditorWindow
{
private:
	uint32 NumberOfSpawn = 0;
	FWideString SceneName = L"Default";
	bool bOrthogonal = false;
	TArray<FClassType*> Spawnables;
	FClassType* SelectedClass;
	/* Camera Info */
	float FOV = 60;
	FVector CameraLocation = { 0.0f, 0.0f, 0.0f }; // Todo : 카메라 객체에서 값을 받아와서 초기값 설정
	FQuaternion CameraRotation; // Todo : 카메라 객체에서 값을 받아와서 초기값 설정
	/*             */
public:
	void SpawnPrimitive();
	void MakeNewScene();
	void SaveCurrentScene();
	void LoadSavedScene();
	void UpdateOrthogonal();
	void UpdateFOV();
	void UpdateCameraLocation();
	void UpdateCameraRotation();

	void Render() override;
};