#include "UPropertyWindow.h"
#include "../../../FVector.h"
#include "ImGui/imgui.h"
#include "Engine/Editor/FEditor.h"
#include "FQuaternion.h"

void UPropertyWindow::GetSelectedValue()
{
	USceneComponent* NewComponent = Editor->GetSelectedSceneComponent();

	if (SelectedComponent != NewComponent)
	{
		SelectedComponent = NewComponent;

		if (SelectedComponent)
		{
			Translation = SelectedComponent->GetRelativeLocation();
			const FQuaternion& Quaternion = SelectedComponent->GetRelativeRotation();
			Rotation = FQuaternion::ToEuler(Quaternion);
			OScale = SelectedComponent->GetRelativeScale3D();
		}
	}
}

void UPropertyWindow::SetSelectedValue()
{
	if (SelectedComponent != nullptr)
	{
		SelectedComponent->SetRelativeLocation(Translation);
		SelectedComponent->SetRelativeRotation(FQuaternion::FromEuler(Rotation));
		SelectedComponent->SetRelativeScale3D(OScale);
	}
}

void UPropertyWindow::DeleteSelected()
{
	Editor->DeleteSelectedSceneComponent();
	SelectedComponent = nullptr;
}

void UPropertyWindow::Render(float DeltaTime)
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
	//float Scale = std::clamp(WindowWidth / 400.0f, 0.1f, 5.0f);
	//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3.0f * Scale, 2.0f * Scale)); // 버튼 안쪽 여백 증가
	const ImGuiStyle& Style = ImGui::GetStyle();
	ImVec2 ItemSpacing = Style.ItemSpacing; // 아이템간 패딩 값
	float ButtonWidth = Available.x * 0.2f; // Button, DragFloat
	float ComboWidth = Available.x * 0.3f;

	GetSelectedValue();

	ImGui::Begin("Jungle Property Window");
	{
		ImGui::PushItemWidth(ButtonWidth);
		ImGui::DragFloat("##translationX", &Translation.X, SnapSize);
		ImGui::SameLine();
		ImGui::DragFloat("##translationY", &Translation.Y, SnapSize);
		ImGui::SameLine();
		ImGui::DragFloat("##translationZ", &Translation.Z, SnapSize);
		ImGui::SameLine();
		ImGui::Text("Translation");
		ImGui::DragFloat("##rotationR", &Rotation.X, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##rotationP", &Rotation.Y, 0.001f);
		ImGui::SameLine();
		ImGui::DragFloat("##rotationY", &Rotation.Z, 0.001f);
		ImGui::SameLine();
		ImGui::Text("Rotation");
		//클램프해야함
		float PrevScaleX = OScale.X;
		if (ImGui::DragFloat("##scaleX", &OScale.X, 0.001f))
		{
			if (bScaleLock)
			{
				float ScaleRatio = OScale.X / PrevScaleX;
				OScale.Y *= ScaleRatio;
				OScale.Z *= ScaleRatio;
			}
		}
		ImGui::SameLine();
		float PrevScaleY = OScale.Y;
		if (ImGui::DragFloat("##scaleY", &OScale.Y, 0.001f))
		{
			if (bScaleLock)
			{
				float ScaleRatio = OScale.Y / PrevScaleY;
				OScale.X *= ScaleRatio;
				OScale.Z *= ScaleRatio;
			}
		}
		ImGui::SameLine();
		float PrevScaleZ = OScale.Z;
		if (ImGui::DragFloat("##scaleZ", &OScale.Z, 0.001f))
		{
			if (bScaleLock)
			{
				float ScaleRatio = OScale.Z / PrevScaleZ;
				OScale.X *= ScaleRatio;
				OScale.Y *= ScaleRatio;
			}
		}
		ImGui::SameLine();
		ImGui::Text("Scale");
		ImGui::PopItemWidth();
		//ImGui::PopStyleVar();
		ImGui::PushItemWidth(ComboWidth);
		char SnapPrev[32];
		snprintf(SnapPrev, sizeof(SnapPrev), "%g", SnapSizeList[SelectedSnapIndex]);
		if (ImGui::BeginCombo("SnapSize", SnapPrev))
		{
			for (int i = 0; i < SnapSizeList.Size(); i++)
			{
				bool bSelected = (SelectedSnapIndex == i);

				char ItemName[32];
				snprintf(ItemName, sizeof(ItemName), "%g", SnapSizeList[i]);

				if (ImGui::Selectable(ItemName, bSelected))
				{
					SelectedSnapIndex = i;
				}

				if (bSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
				SnapSize = SnapSizeList[SelectedSnapIndex];
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Checkbox("Scale Lock", &bScaleLock);
		if (ImGui::Button("Delete"))
		{
			DeleteSelected();
		}
	}
	ImGui::End();

	SetSelectedValue();
}