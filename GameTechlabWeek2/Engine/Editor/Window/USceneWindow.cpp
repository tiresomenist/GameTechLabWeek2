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
void USceneWindow::UpdateCameraLocation()
{
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

	ImGui::Begin("Jungle Control Panel");
	{
		ImGui::Text("Hello Jungle World!");
		ImGui::Text("FPS %.0f (%.0f ms)", FPS, 1000.0f / FPS);
		ImGui::Separator();

		ImGui::Button("Spawn");
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
		ImGui::Button("New Scene");
		{
			MakeNewScene();
		}
		ImGui::Button("Save Scene");
		{
			SaveCurrentScene();
		}
		ImGui::Button("Load Scene");
		{
			LoadSavedScene();
		}
		ImGui::Separator();

		ImGui::Checkbox("Orthogonal", &bOrthogonal);
		{
			UpdateOrthogonal();
		}
		ImGui::DragFloat("FOV", &FOV, 1.0f);
		{
			UpdateFOV();
		}
		ImGui::DragFloat("##cameraX", &CameraLocation.X, 0.1f);
		{
			UpdateCameraLocation();
		}
		ImGui::SameLine();
		ImGui::DragFloat("##cameraY", &CameraLocation.Y, 0.1f);
		{
			UpdateCameraLocation();
		}
		ImGui::SameLine();
		ImGui::DragFloat("##cameraZ", &CameraLocation.Z, 0.1f);
		{
			UpdateCameraLocation();
		}
		ImGui::SameLine();
		ImGui::Text("Camera Location");
		ImGui::DragFloat("##cameraR", &CameraRotation.X, 0.001f);
		{
			UpdateCameraRotation();
		}
		ImGui::SameLine();
		ImGui::DragFloat("##cameraP", &CameraRotation.Y, 0.001f);
		{
			UpdateCameraRotation();
		}
		ImGui::SameLine();
		ImGui::DragFloat("##cameraY", &CameraRotation.Z, 0.001f);
		{
			UpdateCameraRotation();
		}
		ImGui::SameLine();
		ImGui::Text("Camera Rotation");
	}
	ImGui::End();
}