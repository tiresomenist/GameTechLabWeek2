#include "UMainScene.h"
#include "Engine/Object/Primitive/USphereComponent.h"
#include "Engine/GEngine.h"
#include "Engine/Core.h"
#include "Engine/InputManager/GInputManager.h"
#include "../Object/Primitive/USphereComponent.h"
#include <format>

//////////////////
//  UMainScene  //
//////////////////
UMainScene::UMainScene(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
    : UScene{ InUUID, InInternalIndex, InClassType }
{
}

FClassType* UMainScene::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new UMainScene(UUID, InternalIndex, InClassType);
		};

	static FClassType Type
	{
		.Name = "MainScene",
		.ClassConstructor = CreateObject,
		.ParentClassType = UScene::GetClass(),
	};

	return &Type;
}


void UMainScene::BeginPlay()
{
    //UScene::BeginPlay();

	USphereComponent* SphereComponent = static_cast<USphereComponent*>(
		FObjectFactory::ConstructObject(USphereComponent::GetClass())
		);

	PrimitiveComponets.Add(SphereComponent);

    CreateMainCamera();
    TestPrimitive = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
}

void UMainScene::Tick(float DeltaTime)
{
    //UScene::Tick(DeltaTime);

	GEngine& Engine = *GEngine::GetInstance();
	GInputManager& Input = *GInputManager::GetInstance();

	float Time = Engine.GetTime();

	if (Input.GetKey(GInputManager::EI_W))
	{
		UE_LOG(std::format("[{}] W키 누름", Time));
	}
	if (Input.GetKey(GInputManager::EI_A))
	{
		UE_LOG(std::format("[{}] A키 누름", Time));
	}
	if (Input.GetKey(GInputManager::EI_S))
	{
		UE_LOG(std::format("[{}] S키 누름", Time));
	}
	if (Input.GetKey(GInputManager::EI_D))
	{
		UE_LOG(std::format("[{}] D키 누름", Time));
	}

    FVector Rotation = TestPrimitive->GetRelativeRotation();
    Rotation.Y += 0.5f * DeltaTime;
    TestPrimitive->SetRelativeRotation(Rotation);
}

void UMainScene::EndPlay()
{
	//UScene::EndPlay();
}
