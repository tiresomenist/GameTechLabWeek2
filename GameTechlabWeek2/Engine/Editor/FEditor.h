#pragma once

#include "Container/TArray.h"
#include "Engine/Object/FObjectFactory.h"
#include "Engine/Renderer/RenderUtil.h"
#include "Engine/Editor/Controller/FCameraController.h"

//TESTCODE//
#include "Engine/Object/UCameraComponent.h"
#include "Engine/GEngine.h"
#include "Engine/FConsole.h"

class USceneComponent;
class UCameraComponent;
class UEditorWindow;
class UGizmo;
class FObjectPicker;
class UGrid;

class FEditor
{
private:

	// 현재 선택된 SceneComponent;
	UCameraComponent* EditorCamera;
	FCameraController CameraController;
	FObjectPicker* ObjectPicker = nullptr;

	USceneComponent* SelectedSceneComponent;
	TArray<UGizmo*> Gizmos;
	TArray<UEditorWindow*> Windows;
	TArray<UGrid*> Grids;
	

public:

	void Initialize();

	void Tick(float DeltaTime);

	void Release();

	void SpawnPrimitive(FClassType* PrimitiveType, int Count);

	void NewScene();
	void LoadScene(FString SceneName);
	void SaveScene(FString SceneName);

	UCameraComponent* GetEditorCamera() { return EditorCamera; }

	USceneComponent* GetSelectedSceneComponent() const { return SelectedSceneComponent; }
	void SetSelectedSceneComponent(USceneComponent* Component);

	void RegisterGizmo(FClassType* Type);
	void RegisterWindow(UEditorWindow* Window);

	TArray<UGizmo*>& GetGizmos() { return Gizmos; }
	TArray<UEditorWindow*>& GetWindows() { return Windows; }
	TArray<UGrid*>& GetGrids() { return Grids; }

	//TEST CODE//
	FVector GetCameraLocation() { return GetEditorCamera()->GetRelativeLocation(); }
	void SetCameraLocation(FVector NewCameraLocation) { EditorCamera->SetRelativeLocation(NewCameraLocation); }
	FQuaternion GetCamerRotation() { return GetEditorCamera()->GetRelativeRotation(); }
	void SetCamerRotation(FQuaternion NewCameraRotation) { EditorCamera->SetRelativeRotation(NewCameraRotation); }
	float GetCameraFOV() { return GetEditorCamera()->GetFOV() * 180.0f / PI; }
	void SetCameraFOV(float NewFOV) { EditorCamera->SetFOVByDegree(NewFOV); }
	void SpawnPrimitives(FClassType* ClassType, uint32 num) { GEngine::GetInstance()->GetConsole()->Append(std::format("Make {}, {} times",ClassType->Name,num)); }

public:
	friend TArray<FPrimitiveRenderData> RenderUtil::GetRenderList(FEditor* Editor, UScene* Scene);
};