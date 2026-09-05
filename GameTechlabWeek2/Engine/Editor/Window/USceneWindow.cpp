#include "USceneWindow.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

void USceneWindow::SpawnPrimitive() 
{

}
void USceneWindow::MakeNewScene()
{

}
void USceneWindow::SaveCurrentScene()
{

}
void USceneWindow::LoadSavedScene()
{

}
//
//TArray<FClassType> SpawnableList
//{
//	USphereComponent::GetClass(),
//	USphereComponent::GetClass(),
//	USphereComponent::GetClass(),
//	USphereComponent::GetClass(),
//	USphereComponent::GetClass(),
//}


void USceneWindow::UpdateEditorWindow(float fps, bool& bIsOrthogonal, float& fov, FVector& cameralocation, FVector& camerarotation)
{
	ImGui::Begin("Jungle Control Panel");
	{
		ImGui::Text("Hello Jungle World!");
		ImGui::Text("FPS %.0f (%.0f ms)", fps, 1000.0f / fps);
		ImGui::Separator();

		//ImGui::Combo();


		// Todo :: 미구현 부분 구현
		ImGui::Button("Spawn");
		{
			SpawnPrimitive();
		}
		ImGui::SameLine();
		ImGui::InputScalar("Number Of Spawn", ImGuiDataType_U32, &numberOfSpawn);
		ImGui::Separator();

		ImGui::InputScalar("Scene Name", ImGuiDataType_S32, &sceneName);
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