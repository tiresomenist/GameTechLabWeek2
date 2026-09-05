#include "UPropertyWindow.h"
#include "../../../FVector.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

void UPropertyWindow::UpdateEditorWindow(FVector& translation, FVector& rotation, FVector& scale)
{
	ImGui::Begin("Jungle Property Window");
	{
		ImGui::DragFloat("##translationX", &translation.X, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##translationY", &translation.Y, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##translationZ", &translation.Z, 0.001f);
		ImGui::SameLine();
		ImGui::Text("Translation");
		ImGui::DragFloat("##rotationR", &rotation.X, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##rotationP", &rotation.Y, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##rotationY", &rotation.Z, 0.001f);
		ImGui::SameLine();
		ImGui::Text("Rotation");
		ImGui::DragFloat("##scaleX", &scale.X, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##scaleY", &scale.Y, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##scaleZ", &scale.Z, 0.001f);
		ImGui::SameLine();
		ImGui::Text("Scale");
	}
	ImGui::End();
}