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

#include "../../ImGui/imgui.h"

void FEditor::Initialize()
{
	EditorCamera = static_cast<UCameraComponent*>(FObjectFactory::ConstructObject(UCameraComponent::GetClass()));
	EditorCamera->SetRelativeLocation(FVector(-5.0f, 0.0f, 0.0f));

	CameraController.SetCamera(EditorCamera);
	SelectedSceneComponent = nullptr;
	ObjectPicker = new FObjectPicker(EditorCamera, GSceneManager::GetInstance()->GetScene());

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

	ImGuiIO& IO = ImGui::GetIO();
	bool bWantToCaptureMouse = IO.WantCaptureMouse;
	bool bWantToCaptureKeyboard = IO.WantCaptureKeyboard;

	float Time = Engine.GetTime();
	if (Input.ConsumeLeftClick() && !bWantToCaptureMouse) {
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
		//UE_LOG("[{}] 우클릭 좌표:{}, {}", Time,
		//	GInputManager::GetInstance()->GetRightCursorX(),
		//	GInputManager::GetInstance()->GetRightCursorY());
	}

	bool bRightClickDragging = Input.GetKey(GInputManager::EI_RMOUSE);
	bool bAllowCameraMouse = !bWantToCaptureMouse;
	bool bAllowCameraKeyboard = !bWantToCaptureKeyboard || (bAllowCameraMouse && bRightClickDragging);

	if(bAllowCameraKeyboard && bAllowCameraMouse)
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
	// TODO
}

void FEditor::NewScene()
{
	// TODO
}

void FEditor::LoadScene(FString SceneName)
{
	// TODO
}

void FEditor::SaveScene(FString SceneName)
{
	// TODO
}

void FEditor::SetSelectedSceneComponent(USceneComponent* Component)
{
	SelectedSceneComponent = Component;
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
