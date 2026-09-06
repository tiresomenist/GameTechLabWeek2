#include "WndProc.h"
#include "Engine/InputManager/GInputManager.h"
#include "Engine/Core.h"

LRESULT HandleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GInputManager& Input = *GInputManager::GetInstance();

	switch (message)
	{
		//keyboard
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'W':
			Input.SetKey(GInputManager::EI_W, true);
			break;
		case 'A':
			Input.SetKey(GInputManager::EI_A, true);
			break;
		case 'S':
			Input.SetKey(GInputManager::EI_S, true);
			break;
		case 'D':
			Input.SetKey(GInputManager::EI_D, true);
			break;
		}
		return 0;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'W':
			Input.SetKey(GInputManager::EI_W, false);
			break;
		case 'A':
			Input.SetKey(GInputManager::EI_A, false);
			break;
		case 'S':
			Input.SetKey(GInputManager::EI_S, false);
			break;
		case 'D':
			Input.SetKey(GInputManager::EI_D, false);
			break;
		}
		return 0;
		//mouse

	case WM_LBUTTONDOWN:
		Input.SetKey(GInputManager::EI_LMOUSE, true);
		break;
	case WM_RBUTTONDOWN:
		Input.SetKey(GInputManager::EI_RMOUSE, true);
		break;
	case WM_LBUTTONUP:
		Input.SetKey(GInputManager::EI_LMOUSE, false);
		break;
	case WM_RBUTTONUP:
		Input.SetKey(GInputManager::EI_RMOUSE, false);
		break;

	case WM_KILLFOCUS:
		Input.KillFocus();
		break;

	case WM_DESTROY:
		// Signal that the app should quit
		UE_LOG("!!! WM_DESTROY !!!\n");
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}