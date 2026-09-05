#include "UConsoleWindow.h"
#include "../../FConsole.h"
#include "../../../FVector.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

void UConsoleWindow::AddDebugText()
{

}
void UConsoleWindow::AddDebugError()
{

}
void UConsoleWindow::Clear(uint32 displaystartindex)
{
	displayStartIndex = displaystartindex;
}
void UConsoleWindow::Copy()
{

}
void UConsoleWindow::Option()
{

}
void UConsoleWindow::UpdateEditorWindow(const FConsole& console)
{
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
			Clear(10); // Todo : console에서 로그를 받는 방식 확정시키고 수정하기
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
		if (Filter.size() <= 0) 
		{
			/*
			const auto& logs = console.GetLogs();
			bool bWasAtBottom = ImGui::GetScrollY() >= ImGui::GetScrollMaxY();

			for (int i = displayStartIndex; i < logs.size(); i++)
			{
				uint32 temp = 0;
				FWString.
				for(int k = 0; k < logs[i].size(); k++)
				{
					if(lo
				}
				ImGui::TextUnformatted(logs[i].c_str());
			}
			if (logs.size() > PreviousLogCount && !bWasAtBottom)
			{
				ImGui::SetScrollHereY(1.0f);
			}

			PreviousLogCount = logs.size();
			*/
		}
	}
	ImGui::End();
}