#include "WndProc.h"
#include "Engine/InputManager/GInputManager.h"
#include "Engine/Core.h"
#include "Engine/Log.h"

LRESULT HandleInput(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	GInputManager& Input = *GInputManager::GetInstance();
	RECT rc;
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
		case 'Q':
			Input.SetKey(GInputManager::EI_Q, true);
			break;
		case 'E':
			Input.SetKey(GInputManager::EI_E, true);
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
		case 'Q':
			Input.SetKey(GInputManager::EI_Q, false);
			break;
		case 'E':
			Input.SetKey(GInputManager::EI_E, false);
			break;
		}
		return 0;
		//mouse

	case WM_LBUTTONDOWN:
		GetClientRect(hWnd, &rc);
		Input.SetLeftCursorX(2.0f * GET_X_LPARAM(lParam) / (rc.right - rc.left) - 1.0f);
		Input.SetLeftCursorY(1.0f - 2.0f * GET_Y_LPARAM(lParam) / (rc.bottom - rc.top));
		Input.SetKey(GInputManager::EI_LMOUSE, true);
		break;
	case WM_LBUTTONUP:
		GetClientRect(hWnd, &rc);
		Input.SetLeftCursorX(2.0f * GET_X_LPARAM(lParam) / (rc.right - rc.left) - 1.0f);
		Input.SetLeftCursorY(1.0f - 2.0f * GET_Y_LPARAM(lParam) / (rc.bottom - rc.top));
		Input.SetKey(GInputManager::EI_LMOUSE, false);
		break;
	case WM_RBUTTONDOWN:
		GetClientRect(hWnd, &rc);
		Input.SetRightCursorX(2.0f * GET_X_LPARAM(lParam) / (rc.right - rc.left) - 1.0f);
		Input.SetRightCursorY(1.0f - 2.0f * GET_Y_LPARAM(lParam) / (rc.bottom - rc.top));
		Input.SetRightCursorPixelX(GET_X_LPARAM(lParam));
		Input.SetRightCursorPixelY(GET_Y_LPARAM(lParam));
		Input.BeginRightDrag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		if (GetCapture() != hWnd)
			SetCapture(hWnd);
		break;
	case WM_RBUTTONUP:
		GetClientRect(hWnd, &rc);
		Input.SetRightCursorX(2.0f * GET_X_LPARAM(lParam) / (rc.right - rc.left) - 1.0f);
		Input.SetRightCursorY(1.0f - 2.0f * GET_Y_LPARAM(lParam) / (rc.bottom - rc.top));
		Input.SetRightCursorPixelX(GET_X_LPARAM(lParam));
		Input.SetRightCursorPixelY(GET_Y_LPARAM(lParam));
		Input.EndRightDrag();
		if (GetCapture() == hWnd) ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		// 우클릭 드래그중
		if (Input.GetKey(GInputManager::EI_RMOUSE)) {
			GetClientRect(hWnd, &rc);
			Input.SetRightCursorX(2.0f * GET_X_LPARAM(lParam) / (rc.right - rc.left) - 1.0f);
			Input.SetRightCursorY(1.0f - 2.0f * GET_Y_LPARAM(lParam) / (rc.bottom - rc.top));
			Input.UpdateRightDrag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		}

		break;
	case WM_CAPTURECHANGED:
		Input.EndRightDrag();
		break;
	case WM_CANCELMODE:
	case WM_KILLFOCUS:
		Input.KillFocus();
		if (GetCapture() == hWnd) ReleaseCapture();
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