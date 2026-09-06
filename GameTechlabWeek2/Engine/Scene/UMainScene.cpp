#include "UMainScene.h"
#include "Engine/GEngine.h"
#include "Engine/Core.h"
#include "Engine/InputManager/GInputManager.h"
#include "Engine/Object/Primitive/USphereComponent.h"
#include "Engine/Object/UCameraComponent.h"

#include <format>

//////////////////
//  UMainScene  //
//////////////////
void UMainScene::BeginPlay()
{
    //UScene::BeginPlay();

    CreateMainCamera();
	GetMainCamera()->SetRelativeLocation(FVector(-5.0f, 0.0f, 0.0f));

	USphereComponent* Sphere1 = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
	Sphere1->SetRelativeLocation(FVector(0.0f, 0.5f, 0.0f));

	USphereComponent* Sphere2 = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
	Sphere2->SetRelativeLocation(FVector(0.0f, -0.5f, 0.0f));
}

void UMainScene::Tick(float DeltaTime)
{
    //UScene::Tick(DeltaTime);

	GEngine& Engine = *GEngine::GetInstance();
	GInputManager& Input = *GInputManager::GetInstance();

	float Time = Engine.GetTime();

	UCameraComponent* Camera = GetMainCamera();
	FVector CameraLocation = Camera->GetRelativeLocation();

	if (Input.GetKey(GInputManager::EI_W))
	{
		UE_LOG(std::format("[{}] W키 누름", Time));
		CameraLocation.X += 0.05f * DeltaTime;
	}
	if (Input.GetKey(GInputManager::EI_A))
	{
		UE_LOG(std::format("[{}] A키 누름", Time));
		CameraLocation.Z += 0.05f * DeltaTime;
	}
	if (Input.GetKey(GInputManager::EI_S))
	{
		UE_LOG(std::format("[{}] S키 누름", Time));
		CameraLocation.X -= 0.05f * DeltaTime;
	}
	if (Input.GetKey(GInputManager::EI_D))
	{
		UE_LOG(std::format("[{}] D키 누름", Time));
		CameraLocation.Z -= 0.05f * DeltaTime;
	}

	GetMainCamera()->SetRelativeLocation(CameraLocation);
}

void UMainScene::EndPlay()
{
	//UScene::EndPlay();
}
