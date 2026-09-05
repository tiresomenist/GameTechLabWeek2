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
	//USceneComponent에 해당 Primitive 생성 요청 (SlectedClass 및 NumbeOfSpawn 입력)
}
void USceneWindow::MakeNewScene()
{
	//USceneComponent에 JSON 파일로 씬 생성 요청 (SceneName 입력값)
}
void USceneWindow::SaveCurrentScene()
{
	//USceneComponent에 JSON 파일로 저장 요청
}
void USceneWindow::LoadSavedScene()
{
	//JSON 파일이 저장된곳에서 JSON 파일 로드해서 USceneComponent에 전달
}

/*
TArray<FClassType> Spawnables
{
	USphereComp::GetClass();
	UCubeComp::GetClass();
	UPlaneComp::GetClass();
};
*/

void USceneWindow::UpdateEditorWindow(float fps, bool& bIsOrthogonal, float& fov, FVector& cameralocation, FVector& camerarotation)
{
	ImGui::Begin("Jungle Control Panel");
	{
		ImGui::Text("Hello Jungle World!");
		ImGui::Text("FPS %.0f (%.0f ms)", fps, 1000.0f / fps);
		ImGui::Separator();

		ImGui::Button("Spawn");
		{
			SpawnPrimitive();
		}
		ImGui::SameLine();
		/*
		if (ImGui::BeginCombo(Spawnable.begin()->Name, PreviewName))
		{
			for (FClassType* ClassType : Spawnables)
			{
				bool bSelected = (SelectedClass == ClassType);

				if (ImGui::Selectable(
					ClassType->Name.c_str(),
					bSelected))
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
		*/

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
		/*                          */

		ImGui::Checkbox("Orthogonal", &bIsOrthogonal);
		ImGui::DragFloat("FOV", &fov, 1.0f);
		ImGui::DragFloat("##cameraX", &cameralocation.X, 0.1f);
		ImGui::SameLine();
		ImGui::DragFloat("##cameraY", &cameralocation.Y, 0.1f);
		ImGui::SameLine();
		ImGui::DragFloat("##cameraZ", &cameralocation.Z, 0.1f);
		ImGui::SameLine();
		ImGui::Text("Camera Location");
		ImGui::DragFloat("##cameraR", &camerarotation.X, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##cameraP", &camerarotation.Y, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##cameraY", &camerarotation.Z, 0.001f);
		ImGui::SameLine();
		ImGui::Text("Camera Rocation");
	}
	ImGui::End();
}