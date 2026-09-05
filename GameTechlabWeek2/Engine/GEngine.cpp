#include "GEngine.h"
#include "Windows.h"

#include "Engine/Object/FObjectFactory.h"
#include "Engine/Object/GObjects.h"
#include "Engine/Object/UObject.h"
#include "Engine/Core.h"

#include "Engine/GSceneManager.h"
#include "Engine/FConsole.h"

#include <chrono>

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
	GSceneManager* SceneManager = GSceneManager::GetInstance();
	SceneManager->Initialize();

	Renderer.Create(InHwnd, 1024, 1024);

	StartTime = GetTime();
	LastTickTime = GetTime();
}

// 엔진의 메인 게임 루프를 실행합니다.
void GEngine::Tick()
{
	const float CurrentTime = GetTime();
	const float DeltaTime = CurrentTime - LastTickTime;
	LastTickTime = CurrentTime;
	// 게임 로직을 수행합니다.
	GSceneManager* SceneManager = GSceneManager::GetInstance();
	SceneManager->Tick(DeltaTime);

	// 게임 화면을 렌더링합니다.
	Renderer.Render(SceneManager->GetCurrentScene());
	
	//Renderer.Render();
}

// 엔진의 자원을 정리합니다.
void GEngine::Destroy()
{
	// 씬 매니저 정리
	GSceneManager* SceneManager = GSceneManager::GetInstance();
	SceneManager->Release();
	
	// GObjects 정리 
	GObjects::Release();

	//Renderer.Shutdown();
	
	// 콘솔 정리
	delete Console;
}
