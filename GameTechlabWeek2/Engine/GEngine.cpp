#include "GEngine.h"
#include "Windows.h"
#include "Object/FObjectFactory.h"
#include "Object/UObject.h"
#include "Object/USceneComponent.h"
#include "Object/UCameraComponent.h"

#include "Engine/FConsole.h"

#include <format>

float GetTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	return static_cast<float>(currentTime.QuadPart);
}

GEngine* GEngine::GetInstance()
{
	static GEngine* Engine = new GEngine();
	return Engine;
}

void GEngine::Initialize(HWND InHwnd)
{
	Console = new FConsole();
	Console->Initialize();

	UObject* Object = FObjectFactory::ConstructObject(UObject::GetClass());
	UObject* SceneObject = FObjectFactory::ConstructObject(USceneComponent::GetClass());
	LastTickTime = GetTime();
}

void GEngine::Tick()
{
	float DeltaTime = GetTime() - LastTickTime;

	//Renderer.Prepare();
	//Renderer.PrepareShader();
	//Renderer.Render();
	//Renderer.SwapBuffer();

	// 게임 로직을 수행합니다.
	// GSceneManager.Update(DeltaTime);

	// 게임 화면을 렌더링합니다.
	// UScene* CurrentScene = GSceneManager->GetScene();
	// FRenderer.Render(CurrentScene);
}

void GEngine::Destroy()
{
	// TODO: 정리 로직

	// TODO: GObjects의 모든 UObject를 정리할 것

	delete Console;

	//Renderer.Shutdown();
}
