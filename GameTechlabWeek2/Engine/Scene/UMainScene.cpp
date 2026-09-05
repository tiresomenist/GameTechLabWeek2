#include "UMainScene.h"
#include "Engine/Object/Primitive/USphereComponent.h"
#include "Engine/GEngine.h"
#include "Engine/Core.h"
#include "Engine/InputManager/GInputManager.h"
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

    CreateMainCamera();
    MainCamera->SetRelativeLocation(FVector(-5.0f, 0.0f, 0.0f));
    TestPrimitive = SpawnObject<USphereComponent*>(USphereComponent::GetClass());

}

void UMainScene::Tick(float DeltaTime)
{
    //UScene::Tick(DeltaTime);

	GEngine& Engine = *GEngine::GetInstance();
	GInputManager& Input = *GInputManager::GetInstance();

	float Time = Engine.GetTime();
	float ForwardInput = 0.0f;
	float RightInput = 0.0f;
	if (Input.GetKey(GInputManager::EI_W))
	{
		UE_LOG(std::format("[{}] W키 누름", Time));
		ForwardInput += 1.0f;
	}
	if (Input.GetKey(GInputManager::EI_A))
	{
		UE_LOG(std::format("[{}] A키 누름", Time));
		RightInput -= 1.0f;
	}
	if (Input.GetKey(GInputManager::EI_S))
	{
		UE_LOG(std::format("[{}] S키 누름", Time));
		ForwardInput -= 1.0f;
	}
	if (Input.GetKey(GInputManager::EI_D))
	{
		UE_LOG(std::format("[{}] D키 누름", Time));
		RightInput += 1.0f;
	}
	MainCamera->MoveCamera(ForwardInput,RightInput,DeltaTime);
    FVector Rotation = TestPrimitive->GetRelativeRotation();
    Rotation.Y += 0.5f * DeltaTime;
    TestPrimitive->SetRelativeRotation(Rotation);
}

void UMainScene::EndPlay()
{
	//UScene::EndPlay();
}
