#include "UPropertyWindow.h"
#include "../../FEditor.h"
#include "../../../FVector.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

void UPropertyWindow::UpdateTranslation()
{
	//Editor->TranslationUpdated(FVector Translation);
}
void UPropertyWindow::UpdateRotation()
{
	//Editor->RotationUpdated(FVector Rotation);
}
void UPropertyWindow::UpdateScale()
{
	//Editor->ScaleUpdated(FVector Scale);
}

void UPropertyWindow::Begin()
{
	//Editor = *GEngine::GetInstance()->GetEditor();
}

void UPropertyWindow::End()
{
	//Editor = nullptr;
}

void UPropertyWindow::Tick()
{
	ImGui::Begin("Jungle Property Window");
	{
		ImGui::DragFloat("##translationX", &Translation.X, 0.001f);
		{
			UpdateTranslation();
		}
		ImGui::SameLine();
		ImGui::DragFloat("##translationY", &Translation.Y, 0.001f);
		{
			UpdateTranslation();
		}
		ImGui::SameLine();
		ImGui::DragFloat("##translationZ", &Translation.Z, 0.001f);
		{
			UpdateTranslation();
		}
		ImGui::SameLine();
		ImGui::Text("Translation");
		ImGui::DragFloat("##rotationR", &Rotation.X, 0.001f);
		{
			UpdateRotation();
		}
		ImGui::SameLine();
		ImGui::DragFloat("##rotationP", &Rotation.Y, 0.001f);
		{
			UpdateRotation();
		}
		ImGui::SameLine();
		ImGui::DragFloat("##rotationY", &Rotation.Z, 0.001f);
		{
			UpdateRotation();
		}
		ImGui::SameLine();
		ImGui::Text("Rotation");
		ImGui::DragFloat("##scaleX", &Scale.X, 0.001f);
		{
			UpdateScale();
		}
		ImGui::SameLine();
		ImGui::DragFloat("##scaleY", &Scale.Y, 0.001f);
		{
			UpdateScale();
		}
		ImGui::SameLine();
		ImGui::DragFloat("##scaleZ", &Scale.Z, 0.001f);
		{
			UpdateScale();
		}
		ImGui::SameLine();
		ImGui::Text("Scale");
	}
	ImGui::End();
}