#include "FEditor.h"

#include "Engine/Object/UCameraComponent.h"
#include "Engine/Editor/Window/UEditorWindow.h"

#include "Engine/Editor/Window/UConsoleWindow.h"
#include "Engine/Editor/Window/UPropertyWindow.h"
#include "Engine/Editor/Window/USceneWindow.h"

#include "Engine/Gizmo/UObjectAxisGizmo.h"
#include "Engine/Gizmo/UWorldAxisGizmo.h"
#include "Engine/Gizmo/UWorldGridGizmo.h"

#include "Engine/Editor/UGrid.h"

#include "Engine/Object/FObjectFactory.h"
#include "Engine/Log.h"

#include "Engine/InputManager/GInputManager.h"

#include "Engine/Editor/ObjectPicker/FObjectPicker.h"
#include "Engine/Editor/ObjectPicker/FGizmoPicker.h"	

#include "Engine/GSceneManager.h"

#include "Engine/Scene/UScene.h"

#include "../../ImGui/imgui.h"


void FEditor::Initialize()
{

	EditorCamera = static_cast<UCameraComponent*>(FObjectFactory::ConstructObject(UCameraComponent::GetClass()));
	EditorCamera->SetRelativeLocation(FVector(-5.0f, 0.0f, 0.0f));

	CameraController.SetCamera(EditorCamera);

	ObjectPicker = new FObjectPicker(this);
	SelectedSceneComponent = nullptr;
	GizmoPicker = new FGizmoPicker(this);


	RegisterGizmo(UObjectAxisGizmo::GetClass());
	RegisterGizmo(UWorldAxisGizmo::GetClass());
	RegisterGizmo(UWorldGridGizmo::GetClass());

	GizmoController = new FGizmoController(this);

	// TODO 생성자 고칠 것
	RegisterWindow(new UConsoleWindow());
	RegisterWindow(new UPropertyWindow());
	RegisterWindow(new USceneWindow());

	RegisterGrid(UGrid::GetClass());
}

void FEditor::Tick(float DeltaTime)
{
	//CameraController.Tick(DeltaTime);
	GEngine& Engine = *GEngine::GetInstance();
	GInputManager& Input = *GInputManager::GetInstance();

	ImGuiIO& IO = ImGui::GetIO();
	bool bWantToCaptureMouse = IO.WantCaptureMouse;
	bool bWantToCaptureKeyboard = IO.WantCaptureKeyboard;

	float Time = Engine.GetTime();
	const bool bWasDragging = GizmoController->IsDragging();

	if (Input.ConsumeLeftClick() &&!bWasDragging &&!bWantToCaptureMouse &&!Input.GetKey(GInputManager::EI_RMOUSE))
	{
		int32 SelectedGizmo = GizmoPicker->Pick(ObjectAxisGizmo);
		//기즈모가 선택되면 드래그 시작
		if (SelectedGizmo != -1) {
			if (Input.GetKey(GInputManager::EI_LMOUSE))
				GizmoController->BeginDrag(SelectedGizmo);
		}
		//기즈모가 선택 안되면 오브젝트 선택
		else
		{
			UPrimitiveComponent* Selected = ObjectPicker->Pick();

			if (SelectedSceneComponent)
			{
				if (SelectedSceneComponent->IsA(UPrimitiveComponent::GetClass()))
				{
					UPrimitiveComponent* Comp = static_cast<UPrimitiveComponent*>(SelectedSceneComponent);
					Comp->RenderData.isSelected = false;
				}
			}

			SetSelectedSceneComponent(Selected);
			if (Selected != nullptr) {
				//SelectedSceneComponent = Selected;
				UE_LOG("[{}] : [{}번째 오브젝트 선택]", Time, Selected->UUID);
				Selected->RenderData.isSelected = true;
			}
		}
	}

	const bool bGizmoOwnsInput =bWasDragging || GizmoController->IsDragging();

	GizmoController->Tick();
	if (bGizmoOwnsInput)
	{
		// 카메라를 막는 동안 쌓인 회전 입력 폐기
		int32 DX, DY;
		Input.ConsumeRightDragDelta(DX, DY);
	}
	bool bRightClickDragging = Input.GetKey(GInputManager::EI_RMOUSE);
	bool bAllowCameraMouse = !bWantToCaptureMouse;
	bool bAllowCameraKeyboard = !bWantToCaptureKeyboard || (bAllowCameraMouse && bRightClickDragging);

	if (!bGizmoOwnsInput && bAllowCameraKeyboard && bAllowCameraMouse)
	{
		CameraController.Tick(DeltaTime);
	}
	const bool bSpacePressed = Input.ConsumeSpacePress();
	if (bSpacePressed && !IO.WantCaptureKeyboard)
	{
		GizmoController->ChangeMod();
	}
}

void FEditor::Release()
{
	delete GizmoController;
	GizmoController = nullptr;
	CameraController.SetCamera(nullptr);
	delete ObjectPicker;
	ObjectPicker = nullptr;
	delete GizmoPicker;
	GizmoPicker = nullptr;
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
	SetSelectedSceneComponent(nullptr);
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
	if (GizmoController != nullptr)GizmoController->SetSelectedObject(Component);
}

void FEditor::DeleteSelectedSceneComponent()
{
	if (SelectedSceneComponent == nullptr) { return; }

	UScene* CurrentScene = GetCurrentScene();
	CurrentScene->Destroy(SelectedSceneComponent);

	SetSelectedSceneComponent(nullptr);
}

void FEditor::RegisterGizmo(FClassType* Type)
{
	UObject* Object = FObjectFactory::ConstructObject(Type);
	UGizmo* Gizmo = static_cast<UGizmo*>(Object);

	Gizmo->Initialize(this);
	if (Gizmo->IsA(UObjectAxisGizmo::GetClass())) {
		SetObjectAxisGizmo(Gizmo);
	}
	Gizmos.Add(Gizmo);
}

void FEditor::RegisterWindow(UEditorWindow* Window)
{
	Window->Initialize(this);
	Windows.Add(Window);
}

void FEditor::SetObjectAxisGizmo(UGizmo* InGizmo)
{
	ObjectAxisGizmo = InGizmo;
}

UGizmo* FEditor::GetObjectAxisGizmo() const
{
	return ObjectAxisGizmo;
}

void FEditor::RegisterGrid(FClassType* Type)
{
	UObject* Object = FObjectFactory::ConstructObject(Type);
	UGrid* Grid = static_cast<UGrid*>(Object);

	Grid->Initialize(this);
	Grids.Add(Grid);
}
