#include "FEditor.h"

#include "Engine/Object/UCameraComponent.h"
#include "Engine/Editor/Window/UEditorWindow.h"

#include "Engine/Editor/Window/UConsoleWindow.h"
#include "Engine/Editor/Window/UPropertyWindow.h"
#include "Engine/Editor/Window/USceneWindow.h"

#include "Engine/Gizmo/UObjectAxisGizmo.h"
#include "Engine/Gizmo/UWorldAxisGizmo.h"
#include "Engine/Gizmo/UWorldGridGizmo.h"

#include "Engine/Object/FObjectFactory.h"
#include "Engine/Log.h"

#include "Engine/InputManager/GInputManager.h"

#include "Engine/Editor/ObjectPicker/FObjectPicker.h"
#include "Engine/GSceneManager.h"

#include "Engine/Scene/UScene.h"

void FEditor::Initialize()
{
	EditorCamera = static_cast<UCameraComponent*>(FObjectFactory::ConstructObject(UCameraComponent::GetClass()));
	EditorCamera->SetRelativeLocation(FVector(-5.0f, 0.0f, 0.0f));

	CameraController.SetCamera(EditorCamera);

	ObjectPicker = new FObjectPicker(this);
	SelectedSceneComponent = nullptr;

	RegisterGizmo(UObjectAxisGizmo::GetClass());
	RegisterGizmo(UWorldAxisGizmo::GetClass());
	RegisterGizmo(UWorldGridGizmo::GetClass());

	// TODO 생성자 고칠 것
	RegisterWindow(new UConsoleWindow());
	RegisterWindow(new UPropertyWindow());
	RegisterWindow(new USceneWindow());
}

void FEditor::Tick(float DeltaTime)
{
	//CameraController.Tick(DeltaTime);
	GEngine& Engine = *GEngine::GetInstance();
	GInputManager& Input = *GInputManager::GetInstance();

	float Time = Engine.GetTime();
	if (Input.ConsumeLeftClick()) {
		//UE_LOG(std::format("[{}] 좌클릭 좌표:{}, {}", Time,
		//	Input.GetLeftCursorX(),
		//	Input.GetLeftCursorY()));
		UPrimitiveComponent* Selected = ObjectPicker->Pick();
		SetSelectedSceneComponent(Selected);
		if (Selected != nullptr) {
			SelectedSceneComponent = Selected;
			UE_LOG("[{}] : [{}번째 오브젝트 선택]", Time, Selected->UUID);
		}
	}
	if (Input.GetKey(GInputManager::EI_RMOUSE)) {
		//UE_LOG(std::format("[{}] 우클릭 좌표:{}, {}", Time,
		//	GInputManager::GetInstance()->GetRightCursorX(),
		//	GInputManager::GetInstance()->GetRightCursorY()));
	}
	CameraController.Tick(DeltaTime);
}

void FEditor::Release()
{
	CameraController.SetCamera(nullptr);
	delete ObjectPicker;
	ObjectPicker = nullptr;
}

void FEditor::SpawnPrimitive(FClassType* PrimitiveType, int Count)
{
	UScene* CurrentScene = GetCurrentScene();

	for (int i = 0; i < Count; ++i)
	{
		CurrentScene->SpawnObject<UObject*>(PrimitiveType);
	}
}

void FEditor::NewScene()
{
	// 똑같이 Scene을 불러오되, Deserialize 과정만 생략
	LoadScene("");
}

void FEditor::LoadScene(FStringView SceneName)
{
	GSceneManager* SceneManager = GSceneManager::GetInstance();
	FClassType* SceneType = GetCurrentScene()->GetClassType();

	SceneManager->LoadScene(SceneType, SceneName);
}

void FEditor::SaveScene(FStringView SceneName)
{
	GSceneManager* SceneManager = GSceneManager::GetInstance();
	SceneManager->SaveScene(SceneName);
}

UScene* FEditor::GetCurrentScene()
{
	GSceneManager* SceneManager = GSceneManager::GetInstance();
	return SceneManager->GetScene();
}

void FEditor::SetSelectedSceneComponent(USceneComponent* Component)
{
	SelectedSceneComponent = Component;
}

void FEditor::DeleteSelectedSceneComponent()
{
	if (SelectedSceneComponent == nullptr) { return; }

	UScene* CurrentScene = GetCurrentScene();
	CurrentScene->Destroy(SelectedSceneComponent);

	SelectedSceneComponent = nullptr;
}

void FEditor::RegisterGizmo(FClassType* Type)
{
	UObject* Object = FObjectFactory::ConstructObject(Type);
	UGizmo* Gizmo = static_cast<UGizmo*>(Object);

	Gizmo->Initialize(this);

	Gizmos.Add(Gizmo);
}

void FEditor::RegisterWindow(UEditorWindow* Window)
{
	Window->Initialize(this);
	Windows.Add(Window);
}
