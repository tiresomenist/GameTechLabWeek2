#include "UConsoleWindow.h"
#include "../../FConsole.h"
#include "../../../FVector.h"
#include "../../GEngine.h"
#include "ImGui/imgui.h"

void UConsoleWindow::AddDebugText(FString DebugText)
{
	GEngine::GetInstance()->GetConsole()->Append(DebugText);
}
void UConsoleWindow::AddDebugError(FString ErrorText)
{
	GEngine::GetInstance()->GetConsole()->Append(ErrorText);
}
void UConsoleWindow::Clear()
{

}
void UConsoleWindow::Copy()
{
	FString ClipBoardText;
	/*
	for (uint32 i = 0; i < logs.Size(); i++)
	{
		ClipBoardText += logs[i];
		ClipBoardText += "\n";
	}
	ImGui::SetClipboardText(ClipBoardText.c_str()); // 클립보드로 복사
	*/
}
void UConsoleWindow::Option()
{
	//과제 시연 영상에는 있었는데 뭐하는지는 모르는 함수
}
void UConsoleWindow::Render()
{
	FConsole* console = GEngine::GetInstance()->GetConsole();
	TArray<FString> logs = console->Get(Filter);

	const ImGuiViewport* Viewport = ImGui::GetMainViewport();
	const ImVec2 WorkPosition = Viewport->WorkPos; // 메뉴창을 제외한 제일 왼쪽 위 위치
	const ImVec2 WorkSize = Viewport->WorkSize;    // 메뉴창을 제외한 Imgui를 띄울 수 있는 공간

	// 전체 프로그램 창 크기에 대한 비율
	constexpr float WindowWidthRatio = 1.0f;
	constexpr float WindowHeightRatio = 0.3f;

	float WindowWidth = WorkSize.x * WindowWidthRatio;
	float WindowHeight = WorkSize.y * WindowHeightRatio;

	ImVec2 NewPosition = WorkPosition;
	NewPosition.y += WorkSize.y - WindowHeight;

	ImGui::SetNextWindowPos(
		NewPosition,
		ImGuiCond_Once
	);

	ImGui::SetNextWindowSize(
		ImVec2(WindowWidth, WindowHeight),
		ImGuiCond_Once
	);

	ImGui::Begin("Example: Console");
	{
		ImGui::Text("This example implements a console with basic coloring, completion (TAB key) and history (Up/Down keys), A more elaborate implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
		ImGui::Text("Enter 'HELP for help.");

		if(ImGui::Button("Add Debug Text"))
		{
			AddDebugText("[Debug] Test");
		}
		ImGui::SameLine();
		if(ImGui::Button("Add Debug Error"))
		{
			AddDebugError("[Error] Test");
		}
		ImGui::SameLine();
		if(ImGui::Button("Clear"))
		{
			Clear();
		}
		ImGui::SameLine();
		if(ImGui::Button("Copy"))
		{
			Copy();
		}
		ImGui::Separator();
		if(ImGui::Button("options"))
		{
			Option();
		}
		ImGui::SameLine();
		ImGui::InputScalar("##SearchFilter", ImGuiDataType_S32, &Filter);
		ImGui::SameLine();
		ImGui::Text("Filter (\"incl,-excl\") (\"error\")");
		ImGui::Separator();

		ImGui::BeginChild("##consoleLogArea",ImVec2(0,0),true, ImGuiWindowFlags_HorizontalScrollbar);

		bool bWasAtBottom = ImGui::GetScrollY() >= ImGui::GetScrollMaxY();

		for (auto & i : logs)
		{
			ImGui::TextUnformatted(i.c_str());
		}
		if (bWasAtBottom)
		{
			ImGui::SetScrollHereY(1.0f);
		}
		ImGui::EndChild();
	}
	ImGui::End();
}