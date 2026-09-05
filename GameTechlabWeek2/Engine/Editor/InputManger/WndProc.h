#pragma once

#include <Windows.h>

//Apply Input at WindowScreen and Imgui
//ToDo : Check Error about Applying input at WindowScreen and Imgui at the same time.
LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);