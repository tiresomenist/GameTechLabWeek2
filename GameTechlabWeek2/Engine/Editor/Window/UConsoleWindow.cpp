#include "UConsoleWindow.h"
#include "../../FConsole.h"
#include "../../../FVector.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

void UConsoleWindow::AddDebugText()
{
	//FConsole에 AddDebugText 요청
}
void UConsoleWindow::AddDebugError()
{
	//FConsole에 AddDebugError 요청
}
void UConsoleWindow::Clear(uint32 displaystartindex)
{
	displayStartIndex = displaystartindex; //실제 로그파일의 내용은 유지하면서 현재까지 읽은 내용 이후 부터 읽음
}
void UConsoleWindow::Copy()
{
	//FConsole에 Copy 요청
}
void UConsoleWindow::Option()
{
	//과제 시연 영상에는 있었는데 뭐하는지는 모르는 함수
}
void UConsoleWindow::UpdateEditorWindow(const FConsole& console)
{
	TArray<FString> logs = console.Get(Filter);
	ImGui::Begin("Example: Console");
	{
		ImGui::Text("This example implements a console with basic coloring, completion (TAB key) and history (Up/Down keys), A more elaborate implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
		ImGui::Text("Enter 'HELP for help.");

		ImGui::Button("Add Debug Text");
		{
			AddDebugText();
		}
		ImGui::SameLine();
		ImGui::Button("Add Debug Error");
		{
			AddDebugError();
		}
		ImGui::SameLine();
		ImGui::Button("Clear");
		{
			Clear(logs.Size());
		}
		ImGui::Button("Copy");
		{
			Copy();
		}
		ImGui::Separator();
		ImGui::Button("options");
		{
			Option();
		}
		ImGui::SameLine();
		ImGui::InputScalar("Scene Name", ImGuiDataType_S32, &Filter);
		ImGui::SameLine();
		ImGui::Text("Filter (\"incl,-excl\") (\"error\")");
		ImGui::Separator();

		ImGui::BeginChild("##consoleLogArea",ImVec2(0,0),true);

		bool bWasAtBottom = ImGui::GetScrollY() >= ImGui::GetScrollMaxY();

		for (int i = displayStartIndex; i < logs.Size(); i++)
		{
			ImGui::TextUnformatted(logs[i].c_str());
		}
		if (logs.Size() > prevLogIndex && !bWasAtBottom)
		{
			ImGui::SetScrollHereY(1.0f);
		}
		prevLogIndex = logs.Size();
	}
	ImGui::End();
}