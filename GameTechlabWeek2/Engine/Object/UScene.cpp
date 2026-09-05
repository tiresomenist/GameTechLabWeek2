#include "UScene.h"
#include "Primitive/UPrimitiveComponent.h"
#include "Primitive/USphereComp.h"
#include "FObjectFactory.h"

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

//template<typename T>
//T* UScene::SpawnPrimitive()
//{
//    T* NewPrimitive = new T();
//    PrimitiveComponents.Add(NewPrimitive);
//
//    return NewPrimitive;
//}


//////////////////
// UEditorScene //
//////////////////
void UMainScene::Initialize()
{
//    UPrimitiveComponent* TestSphere = SpawnPrimitive<USpherePrimitive>();
    // @Check
    USpherePrimitive* SpherePrimitive = static_cast<USpherePrimitive*>(
        FObjectFactory::ConstructObject(USpherePrimitive::GetClass())
        );

    SelectedPrimitives.Add(SpherePrimitive);
    // Scene의 Primitive 목록에도 등록 (렌더링 순회 대상이 되려면 필요)
    PrimitiveComponents.Add(SpherePrimitive);
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
