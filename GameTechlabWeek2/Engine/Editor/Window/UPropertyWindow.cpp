#include "UPropertyWindow.h"
#include "../../../FVector.h"
#include "ImGui/imgui.h"

void UPropertyWindow::UpdateTranslation()
{

}
void UPropertyWindow::UpdateRotation()
{

}
void UPropertyWindow::UpdateScale()
{

}

void UPropertyWindow::Render()
{
	ImGui::Begin("Jungle Property Window");
	{
		if (ImGui::DragFloat("##translationX", &Translation.X, 0.001f))
		{
			UpdateTranslation();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##translationY", &Translation.Y, 0.001f))
		{
			UpdateTranslation();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##translationZ", &Translation.Z, 0.001f))
		{
			UpdateTranslation();
		}
		ImGui::SameLine();
		ImGui::Text("Translation");
		if(ImGui::DragFloat("##rotationR", &Rotation.X, 0.001f))
		{
			UpdateRotation();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##rotationP", &Rotation.Y, 0.001f))
		{
			UpdateRotation();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##rotationY", &Rotation.Z, 0.001f))
		{
			UpdateRotation();
		}
		ImGui::SameLine();
		ImGui::Text("Rotation");
		if(ImGui::DragFloat("##scaleX", &Scale.X, 0.001f))
		{
			UpdateScale();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##scaleY", &Scale.Y, 0.001f))
		{
			UpdateScale();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##scaleZ", &Scale.Z, 0.001f))
		{
			UpdateScale();
		}
		ImGui::SameLine();
		ImGui::Text("Scale");
	}
	ImGui::End();
}