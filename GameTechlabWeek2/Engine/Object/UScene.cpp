#include "UScene.h"
#include "Primitive/UPrimitiveComponent.h"

void UScene::Update(float DeltaTime)
{
    //for (AActor* Actor : ActiveActors)
    //{
    //    if (Actor) Actor->Tick(DeltaTime);
    //}
}

const TArray<UPrimitiveComponent*>& UScene::GetPrimitiveComponents() const
{
    return PrimitiveComponents;
}

template<typename T>
T* UScene::SpawnPrimitive()
{
    T* NewPrimitive = new T();
    PrimitiveComponents.Add(NewPrimitive);

    return NewPrimitive;
}


//////////////////
// UEditorScene //
//////////////////
