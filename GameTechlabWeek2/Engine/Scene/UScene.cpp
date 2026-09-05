#include "UScene.h"
#include "Engine/Object/Primitive/UPrimitiveComponent.h"
#include "Engine/Object/UCameraComponent.h"
#include "../Object/Primitive/USphereComponent.h"

UScene::UScene(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
    : UObject{ InUUID, InInternalIndex, InClassType }
{
}

FClassType* UScene::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new UScene(UUID, InternalIndex, InClassType);
		};

	static FClassType Type
	{
		.Name = "Scene",
		.ClassConstructor = CreateObject,
		.ParentClassType = UObject::GetClass(),
	};

	return &Type;
}

// UScene의 BeginPlay, Tick, EndPlay는 모든 Scene에 대한 공통 로직이 필요하면 작성
// But 아직 그런 용도가 없음 언젠가 생기면 쓰는걸로...
void UScene::BeginPlay() {
	USphereComponent* SphereComponent = static_cast<USphereComponent*>(
		FObjectFactory::ConstructObject(USphereComponent::GetClass())
		);

	PrimitiveComponets.Add(SphereComponent);
}
void UScene::Tick(float DeltaTime) {}
void UScene::EndPlay() {}

void UScene::CreateMainCamera()
{
    MainCamera = SpawnObject<UCameraComponent*>(UCameraComponent::GetClass());
}

TArray<UPrimitiveComponent*> UScene::GetPrimitiveComponents() const
{
	return PrimitiveComponets;
}