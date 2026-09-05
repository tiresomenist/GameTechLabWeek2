#include "UScene.h"
#include "Primitive/UPrimitiveComponent.h"

void UScene::Update(float DeltaTime)
{
    //for (AActor* Actor : ActiveActors)
    //{
    //    if (Actor) Actor->Tick(DeltaTime);
    //}
}

const std::vector<UPrimitiveComponent*>& UScene::GetPrimitiveComponents() const
{
    return PrimitiveComponents;
}
