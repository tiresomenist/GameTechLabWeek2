#include "UEditor.h"
#include "../FRenderer.h"
#include "../../ImGui/imgui.h"
#include "../../ImGui/imgui_internal.h"
#include "../../ImGui/imgui_impl_dx11.h"
#include "../../ImGui/imgui_impl_win32.h"
#include <Windows.h>

void UEditor::startEditor(HWND Hwnd,ID3D11Device* device, ID3D11DeviceContext* device_context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(Hwnd);
	ImGui_ImplDX11_Init(device, device_context);
}
void UEditor::updateEditor(FRenderer &renderer)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	// here
	ImGui::Begin("Jungle Property Window");
	{
		ImGui::Text("Hello Jungle World!");
	}
	ImGui::End();


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	//renderer.SwapBuffer();
}
void UEditor::endEditor()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}