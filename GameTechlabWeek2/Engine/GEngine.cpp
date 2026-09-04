#include "GEngine.h"
#include "Windows.h"
#include "Object/FObjectFactory.h"
#include "Object/UObject.h"
#include "Object/USceneComponent.h"
#include "FRenderer.h"

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

void GEngine::Initialize(HWND d)
{
	LastTickTime = GetTime();

	UObject* Object = FObjectFactory::ConstructObject(UObject::GetClass());
	UObject* SceneObject = FObjectFactory::ConstructObject(USceneComponent::GetClass());

	USceneComponent* SceneComponent = reinterpret_cast<USceneComponent*>(SceneObject);
	SceneComponent->RelativeLocation = FVector{ 1.0f, 2.0f, 3.0f };
	SceneComponent->RelativeRotation = FVector{ 1.0f, 2.0f, 3.0f };
	SceneComponent->RelativeScale3D = FVector{ 1.0f, 1.0f, 1.0f };

	MessageBox(nullptr, std::format(L"테스트입니다 {} {} {}",
		SceneComponent->RelativeLocation.X,
		SceneComponent->RelativeLocation.Y,
		SceneComponent->RelativeLocation.Z).c_str(), L"", 0);

	r.Create(d, 1024, 1024);

}

void GEngine::Tick()
{
	float DeltaTime = GetTime() - LastTickTime;
	r.Render();
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
