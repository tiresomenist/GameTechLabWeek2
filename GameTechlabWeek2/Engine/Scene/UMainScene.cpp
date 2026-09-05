#include "UMainScene.h"
#include "Engine/Object/Primitive/USphereComponent.h"
#include "Engine/UGameplayStatics.h"

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
    TestPrimitive = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
}

void UMainScene::Tick(float DeltaTime)
{
    //UScene::Tick(DeltaTime);

    FVector Rotation = TestPrimitive->GetRelativeRotation();
    Rotation.Y += 0.5f * DeltaTime;
    TestPrimitive->SetRelativeRotation(Rotation);
}

void UMainScene::EndPlay()
{
	//UScene::EndPlay();
}
