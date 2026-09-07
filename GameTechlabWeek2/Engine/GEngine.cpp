#include "GEngine.h"
#include "Windows.h"

#include "Engine/Object/FObjectFactory.h"
#include "Engine/Object/GObjects.h"
#include "Engine/Object/UObject.h"
#include "Engine/Core.h"

#include "Engine/Editor/FEditor.h"
#include "Engine/GSceneManager.h"
#include "Engine/FConsole.h"

#include "Engine/Primitive/GPrimitive.h"

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

	// Device 초기화
	GDevice& Device = *GDevice::GetInstance();
	Device.Initialize(InHwnd, 1024, 1024);

	// 리소스 매니저 초기화
	GResourceManager& ResourceManager = *GResourceManager::GetInstance();
	GPrimitive::Initialize(&Device);
	ResourceManager.Initialize(&Device);
	
	// 렌더러 초기화
	Renderer.Create(InHwnd, &Device);
	
	// 씬 매니저 초기화
	GSceneManager* SceneManager = GSceneManager::GetInstance();
	SceneManager->Initialize();

	// 에디터 초기화
	Editor = new FEditor();
	Editor->Initialize();

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

	Editor->Tick(DeltaTime);

	// 게임 화면을 렌더링합니다.
	UScene* CurrentScene = SceneManager->GetScene();
	Renderer.Render(Editor, CurrentScene);
}

// 엔진의 자원을 정리합니다.
void GEngine::Destroy()
{
	// 에디터 정리
	Editor->Release();
	delete Editor;
	Editor = nullptr;

	// 씬 매니저 정리
	GSceneManager* SceneManager = GSceneManager::GetInstance();
	SceneManager->Release();
	
	// GObjects 정리 
	GObjects::Release();

	Renderer.Shutdown();
	
	// 콘솔 정리
	delete Console;
}
