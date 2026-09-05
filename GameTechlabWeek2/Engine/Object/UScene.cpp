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
void UMainScene::Initialize()
{
    UPrimitiveComponent* TestSphere = SpawnPrimitive<USphereComponent>();

    SelectedPrimitives.Add(TestSphere);
}

void UMainScene::Update(float DeltaTime)
{
    UScene::Update(DeltaTime);

    for (UPrimitiveComponent* Prim : SelectedPrimitives)
    {
        if (Prim)
        {
            FVector Rot = Prim->GetRelativeRotation();
            Rot.Y += 0.5f * DeltaTime;
            Prim->SetRelativeRotation(Rot);
        }
    }
}
