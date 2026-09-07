#include "USceneWindow.h"
#include "Engine/Editor/FEditor.h"
#include "../../FConsole.h"
#include "../../GEngine.h"
#include "Container/TArray.h"
#include "Engine/Object/FClassType.h"
#include "Engine/Object/Primitive/USphereComponent.h"
#include "Engine/Object/Primitive/UCubeComponent.h"
#include "Engine/Object/Primitive/UPlaneComponent.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Engine/InputManager/GInputManager.h"

#include "Engine/GSceneManager.h"

void USceneWindow::SpawnPrimitive() 
{
	//테스트 코드
	Editor->SpawnPrimitives(SelectedClass, NumberOfSpawn);
}
void USceneWindow::MakeNewScene()
{
	//UEditor에 JSON 파일로 씬 생성 요청 (SceneName 입력값)
}
void USceneWindow::SaveCurrentScene()
{
	//UEditor에 JSON 파일로 저장 요청
}
void USceneWindow::LoadSavedScene()
{
	//UEditor에 JSON 파일이 저장된곳에서 JSON 파일 로드해서 USceneComponent에 전달요청
}
void USceneWindow::Render()
{
	float FPS = 60.0f;

	if (Spawnables.IsEmpty())
	{
		Spawnables.Empty();
		Spawnables.Add(USphereComponent::GetClass());
		Spawnables.Add(UCubeComponent::GetClass());
		Spawnables.Add(UPlaneComponent::GetClass());
		SelectedClass = *Spawnables.begin();
	}
	CameraLocation = Editor->GetCameraLocation();
	CameraRotation = Editor->GetCamerRotation();
	FOV = Editor->GetCameraFOV();

	const ImGuiViewport* Viewport = ImGui::GetMainViewport();
	const ImVec2 WorkPosition = Viewport->WorkPos; // 메뉴창을 제외한 제일 왼쪽 위 위치
	const ImVec2 WorkSize = Viewport->WorkSize;    // 메뉴창을 제외한 Imgui를 띄울 수 있는 공간

	// 전체 프로그램 창 크기에 대한 비율
	constexpr float WindowWidthRatio = 0.42f;
	constexpr float WindowHeightRatio = 0.36f;

	float WindowWidth = WorkSize.x * WindowWidthRatio;
	float WindowHeight = WorkSize.y * WindowHeightRatio;

	ImGui::SetNextWindowPos(
		WorkPosition,
		ImGuiCond_Once
	);

	ImGui::SetNextWindowSize(
		ImVec2(WindowWidth, WindowHeight),
		ImGuiCond_Once
	);
	
	ImVec2 Available = ImGui::GetContentRegionAvail();
	float Scale = std::clamp(WindowWidth / 400.0f, 0.1f, 5.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,ImVec2(3.0f * Scale , 2.0f * Scale)); // 버튼 안쪽 여백 증가
	const ImGuiStyle& Style = ImGui::GetStyle();
	ImVec2 ItemSpacing = Style.ItemSpacing; // 아이템간 패딩 값

	float ButtonWidth = Available.x * 0.2f; // Button, DragFloat
	float WideItemWidth = ButtonWidth * 3.0f + ItemSpacing.x * 2.0f; // FOV, NumberOfSpawn
	
	ImGui::Begin("Jungle Control Panel", nullptr, ImGuiWindowFlags_HorizontalScrollbar);
	{
		ImGui::Text("Hello Jungle World!");
		ImGui::Text("FPS %.0f (%.0f ms)", FPS, 1000.0f / FPS);
		ImGui::Separator();

		if (ImGui::Button("Save"))
		{
			GSceneManager::GetInstance()->SaveScene();
		}

		ImGui::PushItemWidth(WideItemWidth);
		if (ImGui::BeginCombo("Primitive", SelectedClass->Name.c_str()))
		{
			for (FClassType* ClassType : Spawnables)
			{
				bool bSelected = (SelectedClass == ClassType);

				if (ImGui::Selectable(ClassType->Name.c_str(), bSelected))
				{
					SelectedClass = ClassType;
				}

				if (bSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (ImGui::Button("Spawn"))
		{
			SpawnPrimitive();
		}
		ImGui::SameLine();
		ImGui::InputScalar("Number Of Spawn", ImGuiDataType_U32, &NumberOfSpawn);
		ImGui::Separator();
		ImGui::PushItemWidth(WideItemWidth);
		ImGui::InputScalar("Scene Name", ImGuiDataType_S32, &SceneName);
		ImGui::PopItemWidth();
		if(ImGui::Button("New Scene"))
		{
			MakeNewScene();
		}
		if(ImGui::Button("Save Scene"))
		{
			SaveCurrentScene();
		}
		if(ImGui::Button("Load Scene"))
		{
			LoadSavedScene();
		}
		ImGui::Separator();
		ImGui::Checkbox("Orthogonal", &bOrthogonal);

		ImGui::PushItemWidth(WideItemWidth); // Item 너비 설정
		if (ImGui::DragFloat("FOV", &FOV, 1.0f, MinFOV, MaxFOV))
		{
			Editor->SetCameraFOV(FOV); // 무조건 업데이트 시키면 라디안 값 FOV가 0에 가까워지므로 조건부로
		}
		ImGui::PopItemWidth();
		ImGui::PushItemWidth(ButtonWidth); // Item 너비 설정
		ImGui::DragFloat("##cameraX", &CameraLocation.X, 0.1f);
		ImGui::SameLine();
		ImGui::DragFloat("##cameraY", &CameraLocation.Y, 0.1f);
		ImGui::SameLine();
		ImGui::DragFloat("##cameraZ", &CameraLocation.Z, 0.1f);
		ImGui::SameLine();
		ImGui::Text("Camera Location");
		ImGui::DragFloat("##cameraRX", &CameraRotation.X, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##cameraRY", &CameraRotation.Y, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##cameraRZ", &CameraRotation.Z, 0.001f);
		ImGui::SameLine();
		ImGui::Text("Camera Rotation");
		ImGui::PopItemWidth();
		ImGui::PopStyleVar();
	}
	Editor->SetCameraLocation(CameraLocation);
	Editor->SetCamerRotation(CameraRotation);
	ImGui::End();
}