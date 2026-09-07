#include "USceneWindow.h"
#include "Container/TArray.h"
#include "Engine/Object/FClassType.h"
#include "Engine/Object/Primitive/USphereComponent.h"
#include "Engine/Object/Primitive/UCubeComponent.h"
#include "Engine/Object/Primitive/UPlaneComponent.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

void USceneWindow::SpawnPrimitive() 
{
	//UEditor에 해당 Primitive 생성 요청 (SlectedClass 및 NumbeOfSpawn 입력)
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
void USceneWindow::UpdateOrthogonal()
{
	//GEngine::GetInstance()->GetEditor()->UpdateOrthogonal();
}
void USceneWindow::UpdateCameraLocation(){
	//GEngine::GetInstance()->GetEditor()->UpdateCameraLocation();
}
void USceneWindow::UpdateCameraRotation()
{
	//GEngine::GetInstance()->GetEditor()->UpdateCameraRocation();
}
void USceneWindow::UpdateFOV()
{

}
void USceneWindow::Begin()
{
	Spawnables.Empty();
	Spawnables.Add(USphereComponent::GetClass());
	Spawnables.Add(UCubeComponent::GetClass());
	Spawnables.Add(UPlaneComponent::GetClass());
	if (!Spawnables.IsEmpty())
	{
		SelectedClass = *Spawnables.begin();
	}
}
void USceneWindow::End()
{

}
void USceneWindow::Tick()
{
	//CameraRotation = GEngine::GetInstance()->GetEditor()->GetCameraRotation();
	//CameraLocation = GEngine::GetInstance()->GetEditor()->GetCameraLotation();
	const ImGuiIO& IO = ImGui::GetIO(); //ImGui의 입출력 및 프레임 상태를 모아둔 객체
	const float FPS = IO.Framerate; //ImGui가 계산한 평균 FPS

	const ImGuiViewport* Viewport = ImGui::GetMainViewport(); //뷰포트에 대한 정보를 가져옴
	const ImVec2 Position = Viewport->WorkPos; // UI창의 왼쪽 위부분 시작지점(메뉴바 제외)
	const ImVec2 Size = Viewport->WorkSize; // UI창이 실제 배치될 수 있는 영역 크기(메뉴바 제외)

	ImGui::SetNextWindowPos(
		ImVec2(Position.x, Position.y),
		ImGuiCond_Always
	);

	ImGui::SetNextWindowSize(
		ImVec2(Size.x * 0.4f, Size.y * 0.3),
		ImGuiCond_Always
	);
	
	float WindowWidth = ImGui::GetWindowSize().x;

	float Scale = WindowWidth / 400.0f;
	Scale = std::clamp(Scale, 0.8f, 1.5f);

	ImGui::SetWindowFontScale(Scale); // 현재 창 폰트 크기 설정

	ImVec2 Available = ImGui::GetContentRegionAvail(); // 현재창크기
	float ButtonWidth = Available.x * 0.15; // 창 크기 0.15 비율
	float ButtonHeight = Available.y * 0.05; // 창크기 0.05 비율

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,ImVec2(3.0f * Scale , 2.0f * Scale)); // 버튼 안쪽 여백 증가

	const ImGuiStyle& Style = ImGui::GetStyle();
	ImVec2 ItemSpacing = Style.ItemSpacing; // 아이템간 패딩 값
	
	ImGui::Begin("Jungle Control Panel");
	{
		ImGui::Text("Hello Jungle World!");
		ImGui::Text("FPS %.0f (%.0f ms)", FPS, 1000.0f / FPS);
		ImGui::Separator();

		if(ImGui::Button("Spawn"))
		{
			SpawnPrimitive();
		}
		ImGui::SameLine();
		
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

		ImGui::InputScalar("Number Of Spawn", ImGuiDataType_U32, &NumberOfSpawn);
		ImGui::Separator();

		ImGui::InputScalar("Scene Name", ImGuiDataType_S32, &SceneName);
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
		{
			UpdateOrthogonal();
		}
		ImGui::PopStyleVar();
		ImGui::PushItemWidth(ButtonWidth * 3.0f + ItemSpacing.x * 2.0f); // Item 너비 설정
		if(ImGui::DragFloat("FOV", &FOV, 1.0f))
		{
			UpdateFOV();
		}
		ImGui::PopItemWidth();
		ImGui::PushItemWidth(ButtonWidth); // Item 너비 설정
		if(ImGui::DragFloat("##cameraX", &CameraLocation.X, 0.1f))
		{
			UpdateCameraLocation();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##cameraY", &CameraLocation.Y, 0.1f))
		{
			UpdateCameraLocation();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##cameraZ", &CameraLocation.Z, 0.1f))
		{
			UpdateCameraLocation();
		}
		ImGui::SameLine();
		ImGui::Text("Camera Location");
		if(ImGui::DragFloat("##cameraRX", &CameraRotation.X, 0.001f))
		{
			UpdateCameraRotation();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##cameraRY", &CameraRotation.Y, 0.001f))
		{
			UpdateCameraRotation();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##cameraRZ", &CameraRotation.Z, 0.001f))
		{
			UpdateCameraRotation();
		}
		ImGui::SameLine();
		ImGui::Text("Camera Rotation");
		ImGui::PopItemWidth(); // 여기까지 반영
	}
	ImGui::End();
}