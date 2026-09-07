#pragma once

#include "Container/TArray.h"
#include "Engine/Object/FObjectFactory.h"
#include "Engine/Renderer/RenderUtil.h"
#include "Engine/Editor/Controller/FCameraController.h"

class USceneComponent;
class UCameraComponent;
class UEditorWindow;
class UGizmo;

class FEditor
{
private:

	// 현재 선택된 SceneComponent;
	UCameraComponent* EditorCamera;
	FCameraController CameraController;

	USceneComponent* SelectedSceneComponent;
	TArray<UGizmo*> Gizmos;
	TArray<UEditorWindow*> Windows;

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

public:
	friend TArray<FPrimitiveRenderData> RenderUtil::GetRenderList(FEditor* Editor, UScene* Scene);
};