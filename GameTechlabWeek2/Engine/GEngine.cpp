#include "GEngine.h"
#include "Windows.h"
#include "Object/FObjectFactory.h"
#include "Object/UObject.h"
#include "Object/USceneComponent.h"

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

void GEngine::Initialize()
{
	LastTickTime = GetTime();

	UObject* Object = FObjectFactory::ConstructObject(UObject::GetClass());
	UObject* SceneObject = FObjectFactory::ConstructObject(USceneComponent::GetClass());

	if (SceneObject->IsA(UObject::GetClass()))
	{
		USceneComponent* SceneComponent = reinterpret_cast<USceneComponent*>(SceneObject);
		SceneComponent->SetRelativeLocation(FVector{ 1.0f, 2.0f, 3.0f });
		SceneComponent->SetRelativeRotation(FVector{ 1.0f, 2.0f, 3.0f });
		SceneComponent->SetRelativeScale3D(FVector{ 1.0f, 1.0f, 1.0f });

		MessageBox(nullptr, std::format(L"테스트입니다 {} {} {}",
			SceneComponent->GetRelativeLocation().X,
			SceneComponent->GetRelativeLocation().Y,
			SceneComponent->GetRelativeLocation().Z).c_str(), L"", 0);
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
}

void GEngine::Destroy()
{
	// TODO: 정리 로직
}
