#include "GEngine.h"
#include "Windows.h"
#include "Object/FObjectFactory.h"
#include "Object/UObject.h"
#include "Object/USceneComponent.h"
#include "Object/UCameraComponent.h"

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
	LastTickTime = GetTime();

	UObject* Object = FObjectFactory::ConstructObject(UObject::GetClass());
	UObject* SceneObject = FObjectFactory::ConstructObject(USceneComponent::GetClass());

	if (SceneObject->IsA(UObject::GetClass()))
	{
		MessageBox(nullptr, std::format(L"[RTTI Test] SceneObject는 UObject입니다.").c_str(), L"", 0);
	}

	if (SceneObject->IsA(USceneComponent::GetClass()))
	{
		MessageBox(nullptr, std::format(L"[RTTI Test] SceneObject는 USceneComponent입니다.").c_str(), L"", 0);
	}

	if (SceneObject->IsA(UCameraComponent::GetClass()))
	{
		MessageBox(nullptr, std::format(L"[RTTI Test] SceneObject는 UCameraComponent입니다.").c_str(), L"", 0);
	}

}

void GEngine::Tick()
{
	float DeltaTime = GetTime() - LastTickTime;

	// 게임 로직을 수행합니다.
	// GSceneManager.Update(DeltaTime);

	// 게임 화면을 렌더링합니다.
	// UScene* CurrentScene = GSceneManager->GetScene();
	// FRenderer.Render(CurrentScene);
	Renderer.Render();
}

void GEngine::Destroy()
{
	// TODO: 정리 로직
	Renderer.Shutdown();
}
