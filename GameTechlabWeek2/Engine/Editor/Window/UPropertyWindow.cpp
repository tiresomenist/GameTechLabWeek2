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
	const ImGuiViewport* Viewport = ImGui::GetMainViewport();
	const ImVec2 WorkPosition = Viewport->WorkPos; // 메뉴창을 제외한 제일 왼쪽 위 위치
	const ImVec2 WorkSize = Viewport->WorkSize;    // 메뉴창을 제외한 Imgui를 띄울 수 있는 공간

	// 전체 프로그램 창 크기에 대한 비율
	constexpr float WindowWidthRatio = 0.35f;
	constexpr float WindowHeightRatio = 0.25f;

	float WindowWidth = WorkSize.x * WindowWidthRatio;
	float WindowHeight = WorkSize.y * WindowHeightRatio;

	ImVec2 NewPosition = WorkPosition;
	NewPosition.x += WorkSize.x * 0.42f;

	ImGui::SetNextWindowPos(
		NewPosition,
		ImGuiCond_Once
	);

	ImGui::SetNextWindowSize(
		ImVec2(WindowWidth, WindowHeight),
		ImGuiCond_Once
	);

	ImVec2 Available = ImGui::GetContentRegionAvail();
	float Scale = std::clamp(WindowWidth / 400.0f, 0.1f, 5.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3.0f * Scale, 2.0f * Scale)); // 버튼 안쪽 여백 증가
	const ImGuiStyle& Style = ImGui::GetStyle();
	ImVec2 ItemSpacing = Style.ItemSpacing; // 아이템간 패딩 값
	float ButtonWidth = Available.x * 0.2f; // Button, DragFloat

	ImGui::Begin("Jungle Property Window");
	{
		ImGui::PushItemWidth(ButtonWidth);
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
		if(ImGui::DragFloat("##scaleX", &OScale.X, 0.001f))
		{
			UpdateScale();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##scaleY", &OScale.Y, 0.001f))
		{
			UpdateScale();
		}
		ImGui::SameLine();
		if(ImGui::DragFloat("##scaleZ", &OScale.Z, 0.001f))
		{
			UpdateScale();
		}
		ImGui::SameLine();
		ImGui::Text("Scale");
		ImGui::PopItemWidth();
		ImGui::PopStyleVar();
	}
	ImGui::End();
}