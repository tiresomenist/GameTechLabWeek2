#include "UScene.h"
#include "Engine/Object/Primitive/UPrimitiveComponent.h"
#include "Engine/Object/UCameraComponent.h"
#include "../Object/Primitive/USphereComponent.h"

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

void UScene::Destroy(UObject* Object)
{
    for (int i = 0; i < Objects.Num(); i++)
    {
        if (Objects[i] == Object)
        {
            delete Object;
            Objects.RemoveAt(i);
            break;
        }
    }
}

UScene::~UScene()
{
    for (auto Item : Objects)
    {
        delete Item;
    }

    Objects.Empty();
}