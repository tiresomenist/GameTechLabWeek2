#pragma once

#include "UEditorWindow.h"
#include "../../../Engine/Object/FClassType.h"
#include "../../../Matrix.h"
#include "../../../Container/FString.h"
#include "../../../FQuaternion.h"

class USceneWindow : public UEditorWindow
{
private:
	uint32 NumberOfSpawn = 1;
	FWideString SceneName = L"Default";
	bool bOrthogonal = false;
	TArray<FClassType*> Spawnables;
	FClassType* SelectedClass;
	/* Camera Info */
	float FOV = 90.0f;
	float MaxFOV = 175.0f;
	float MinFOV = 5.0f;
	FVector CameraLocation = { 0.0f, 0.0f, 0.0f };
	FQuaternion CameraRotation;
	/*             */
public:
	void SpawnPrimitive();
	void MakeNewScene();
	void SaveCurrentScene();
	void LoadSavedScene();

	void Render() override;
};