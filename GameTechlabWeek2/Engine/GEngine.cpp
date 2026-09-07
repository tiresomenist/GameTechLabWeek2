#include "GEngine.h"
#include "Windows.h"

#include "Engine/Object/FObjectFactory.h"
#include "Engine/Object/GObjects.h"
#include "Engine/Object/UObject.h"
#include "Engine/Core.h"

#include "Engine/GSceneManager.h"
#include "Engine/FConsole.h"

#include "GDevice.h"
#include "GResourceManager.h"

#include <chrono>

#include "Editor/Window/UConsoleWindow.h"
#include "Editor/Window/UEditorWindow.h"
#include "Editor/Window/UPropertyWindow.h"
#include "Editor/Window/USceneWindow.h"

float GEngine::GetTime()
{
	static auto Start = std::chrono::steady_clock::now();
	auto Now = std::chrono::steady_clock::now();

	return std::chrono::duration<float>(Now - Start).count();
}

GEngine* GEngine::GetInstance()
{
	static GEngine* Engine = new GEngine();
	return Engine;
}

// 엔진을 초기 상태로 초기화합니다.
void GEngine::Initialize(HWND InHwnd)
{
	// 콘솔 초기화
	Console = new FConsole();
	Console->Initialize();

	// 씬 매니저 초기화
	GDevice::GetInstance()->Initialize(InHwnd, 1024, 1024);
	GResourceManager::GetInstance()->Initialize(GDevice::GetInstance());
	Renderer.Create(InHwnd, GDevice::GetInstance()); //FRenderer에서 ImGui 처리로직이 있음
	GSceneManager* SceneManager = GSceneManager::GetInstance();
	SceneManager->Initialize();

	StartTime = GetTime();
	LastTickTime = GetTime();

	Windows.Add(new UConsoleWindow());
	//Windows.Add(new UDetailsWindow());
	Windows.Add(new UPropertyWindow());
	Windows.Add(new USceneWindow());
}

// 엔진의 메인 게임 루프를 실행합니다.
void GEngine::Tick()
{
	float DeltaTime = GetTime() - LastTickTime;
	LastTickTime = GetTime();
	// 게임 로직을 수행합니다.
	GSceneManager* SceneManager = GSceneManager::GetInstance();
	SceneManager->Tick(DeltaTime);

	// 게임 화면을 렌더링합니다.
	UScene* CurrentScene = SceneManager->GetScene();
	Renderer.Render(CurrentScene, Windows);
}

// 엔진의 자원을 정리합니다.
void GEngine::Destroy()
{
	// ImGui와 엔진 자원이 살아 있을 때 에디터 창을 먼저 정리합니다.
	for (UEditorWindow* Window : Windows)
	{
		if (Window != nullptr)
		{
			Window->End();
			delete Window;
		}
	}
	Windows.Empty();

	// 씬 매니저 정리
	GSceneManager* SceneManager = GSceneManager::GetInstance();
	SceneManager->Release();
	
	// GObjects 정리 
	GObjects::Release();

	Renderer.Shutdown();
	
	// 콘솔 정리
	delete Console;
}
