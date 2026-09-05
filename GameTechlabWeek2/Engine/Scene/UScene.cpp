#include "UScene.h"
#include "Engine/Object/Primitive/UPrimitiveComponent.h"
#include "Engine/Object/UCameraComponent.h"

// UScene의 BeginPlay, Tick, EndPlay는 모든 Scene에 대한 공통 로직이 필요하면 작성
// But 아직 그런 용도가 없음 언젠가 생기면 쓰는걸로...
void UScene::BeginPlay() {}
void UScene::Tick(float DeltaTime) {}
void UScene::EndPlay() {}

void UScene::CreateMainCamera()
{
    MainCamera = SpawnObject<UCameraComponent*>(UCameraComponent::GetClass());
}