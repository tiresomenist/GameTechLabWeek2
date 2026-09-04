#include "GEngine.h"
#include "Windows.h"
#include "Object/FObjectFactory.h"
#include "Object/UObject.h"
#include "Object/USceneComponent.h"

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

void GEngine::Initialize()
{
	LastTickTime = GetTime();

	UObject* Object = FObjectFactory::ConstructObject(UObject::GetClass());
	UObject* SceneObject = FObjectFactory::ConstructObject(USceneComponent::GetClass());
}

void GEngine::Tick()
{
	float DeltaTime = GetTime() - LastTickTime;

	// 게임 로직을 수행합니다.
	// GSceneManager.Update(DeltaTime);

	// 게임 화면을 렌더링합니다.
	// UScene* CurrentScene = GSceneManager->GetScene();
	// FRenderer.Render(CurrentScene);
}

void GEngine::Destroy()
{
	// TODO: 정리 로직
}
