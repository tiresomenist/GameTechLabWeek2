#include "WndProc.h"
#include "GInputManager.h"
#include "../../../ImGui/imgui.h"
#include "../../../ImGui/imgui_internal.h"
#include "../../../ImGui/imgui_impl_dx11.h"
#include "../../../ImGui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))

	switch (message)
	{
		//keyboard
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'W':
			GInputManager::getInstance()->onKeyDown(W);
			break;
		case 'A':
			GInputManager::getInstance()->onKeyDown(A);
			break;
		case 'S':
			GInputManager::getInstance()->onKeyDown(S);
			break;
		case 'D':
			GInputManager::getInstance()->onKeyDown(D);
			break;
		}
		return 0;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'W':
			GInputManager::getInstance()->onKeyUp(W);
			break;
		case 'A':
			GInputManager::getInstance()->onKeyUp(A);
			break;
		case 'S':
			GInputManager::getInstance()->onKeyUp(S);
			break;
		case 'D':
			GInputManager::getInstance()->onKeyUp(D);
			break;
		}
		return 0;
		//mouse

	case WM_LBUTTONDOWN:
		GInputManager::getInstance()->onKeyDown(LMOUSE);
		break;
	case WM_RBUTTONDOWN:
		GInputManager::getInstance()->onKeyDown(RMOUSE);
		break;
	case WM_LBUTTONUP:
		GInputManager::getInstance()->onKeyUp(LMOUSE);
		break;
	case WM_RBUTTONUP:
		GInputManager::getInstance()->onKeyUp(RMOUSE);
		break;

	case WM_KILLFOCUS:
		GInputManager::getInstance()->killFocus();
		break;

	case WM_DESTROY:
		// Signal that the app should quit
		OutputDebugStringA("!!! WM_DESTROY !!!\n");
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}