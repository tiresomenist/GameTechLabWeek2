#include <windows.h>

// ImGui 관련 헤더 삽입
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "imGui/imgui_impl_win32.h"

#include "Matrix.h"

// 구체 배열 헤더 파일
#include "FVertexSimple.h"
#include "Sphere.h"
#include "Cube.h"
#include "Triangle.h"

//렌더러 헤더파일
#include "Engine/FRenderer.h"
#include "Engine/GEngine.h"
#include "Engine/InputManager/WndProc.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 각종 메시지를 처리할 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // ImGUI 메세지는 ImGUI가 처리
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
    {
        return true;
    }

    switch (message)
    {
    case WM_DESTROY:
        // Signal that the app should quit
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        // Handle window size changes
        break;
    default:
        return HandleInput(hWnd, message, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // 윈도우 클래스 이름
    WCHAR WindowClass[] = L"JungleWindowClass";

    // 윈도우 타이틀바에 표시될 이름
    WCHAR Title[] = L"Game Tech Lab";

    // 각종 메시지를 처리할 함수인 WndProc의 함수 포인터를 WindowClass 구조체에 넣는다.
    WNDCLASSW wndclass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, WindowClass };

    // 윈도우 클래스 등록
    RegisterClassW(&wndclass);

    // 1024 x 1024 크기에 윈도우 생성
    HWND hWnd = CreateWindowExW(0, WindowClass, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1024, 1024,
        nullptr, nullptr, hInstance, nullptr);
    

    // 엔진을 초기화합니다.
    GEngine* Engine = GEngine::GetInstance();
    Engine->Initialize(hWnd);

    // Main Loop (Quit Message가 들어오기 전까지 아래 Loop를 무한히 실행하게 됨)
    bool bIsExit = false;
    while (bIsExit == false)
    {

        MSG msg;

        // 처리할 메시지가 더 이상 없을때 까지 수행
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 키 입력 메시지를 번역
            TranslateMessage(&msg);

            // 메시지를 적절한 윈도우 프로시저에 전달, 메시지가 위에서 등록한 WndProc 으로 전달됨
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
            {
                bIsExit = true;
                break;
            }
        }


        ////////////////////////////////////////////
        // 매번 실행되는 코드를 여기에 추가합니다.
        Engine->Tick();

    }


    // 엔진을 정리합니다.
    Engine->Destroy();
    Engine = nullptr;

    //Exit();
    return 0;
}
