#include "UConsoleWindow.h"
#include "../../FConsole.h"
#include "../../../FVector.h"
#include "../../GEngine.h"
#include "ImGui/imgui.h"
#include "Engine/GEngine.h"

void UConsoleWindow::AddDebugText(FString DebugText)
{
	GEngine::GetInstance()->GetConsole()->Append(DebugText);
}
void UConsoleWindow::AddDebugError(FString ErrorText)
{
	GEngine::GetInstance()->GetConsole()->Append(ErrorText);
	//해당 명렁어로 logs에 추가되는경우 (Fstring, bool) 구조체로 에러 메세지인지 아닌지 해서
	//if문으로 ImGui::TextColored(ImVec4(1, 0, 0, 1), "Red"); 같이 색 다르게 하는 아이디어
}
void UConsoleWindow::Clear()
{
	logs.Empty();
}
void UConsoleWindow::Copy()
{
	FString ClipBoardText;
	for (uint32 i = 0; i < logs.Size(); i++)
	{
		ClipBoardText += logs[i];
		ClipBoardText += "\n";
	}
	ImGui::SetClipboardText(ClipBoardText.c_str()); // 클립보드로 복사
}
void UConsoleWindow::Option()
{
	//과제 시연 영상에는 있었는데 뭐하는지는 모르는 함수
}
void UConsoleWindow::Render()
{
	FConsole* console = GEngine::GetInstance()->GetConsole();
	TArray<FString> logs = console->Get(Filter);
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
		prevLogIndex = logs.Size();

		ImGui::EndChild();
	}
	ImGui::End();
}