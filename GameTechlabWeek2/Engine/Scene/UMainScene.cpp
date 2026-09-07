#include "UMainScene.h"
#include "Engine/GEngine.h"
#include "Engine/Core.h"
#include "Engine/InputManager/GInputManager.h"
#include "Engine/Object/Primitive/USphereComponent.h"
#include "Engine/Object/Primitive/UCubeComponent.h"
#include "Engine/Object/Primitive/UPepeComponent.h"
#include "Engine/Object/Primitive/UOctopusComponent.h"
#include "Engine/Object/Primitive/UArrowRedComponent.h"
#include "Engine/Object/Primitive/UArrowGreenComponent.h"
#include "Engine/Object/Primitive/UArrowBlueComponent.h"
#include "Engine/Object/UCameraComponent.h"
// TEMP(UI test): Gizmo implementation is currently excluded from the build.
// #include "Engine/Gizmo/UWorldAxisGizmo.h"

#include "Engine/Object/Primitive/USphereComponent.h"
#include "Engine/Object/Primitive/UCubeComponent.h"
#include "Engine/Object/Primitive/UPlaneComponent.h"

#include <format>

//////////////////
//  UMainScene  //
//////////////////
void UMainScene::BeginPlay()
{
    //UScene::BeginPlay();

    CreateMainCamera();

	USphereComponent* SphereComponent = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
	SphereComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	UCubeComponent* CubeComponent = SpawnObject<UCubeComponent*>(UCubeComponent::GetClass());
	CubeComponent->SetRelativeLocation(FVector(3.0f, 0.0f, 0.0f));

	UOctopusComponent* OctopusComponent = SpawnObject<UOctopusComponent*>(UOctopusComponent::GetClass());
	OctopusComponent->SetRelativeLocation(FVector(-3.0f, 0.0f, 0.0f));

	UArrowRedComponent* RedArrowComponent = SpawnObject<UArrowRedComponent*>(UArrowRedComponent::GetClass());
	RedArrowComponent->SetRelativeLocation(FVector(0.0f, 3.0f, 0.0f));

	UArrowGreenComponent* GreenArrowComponent = SpawnObject<UArrowGreenComponent*>(UArrowGreenComponent::GetClass());
	GreenArrowComponent->SetRelativeLocation(FVector(0.0f, -3.0f, 0.0f));

	UArrowBlueComponent* BlueArrowComponent = SpawnObject<UArrowBlueComponent*>(UArrowBlueComponent::GetClass());
	BlueArrowComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 3.0f));

	UPepeComponent* BPepeComponent = SpawnObject<UPepeComponent*>(UPepeComponent::GetClass());
	BPepeComponent->SetRelativeLocation(FVector(0.0f, 3.0f, 3.0f));
}

void UMainScene::Tick(float DeltaTime)
{
    //UScene::Tick(DeltaTime);

	//CameraController.Tick(DeltaTime);

}

void UMainScene::EndPlay()
{
	//UScene::EndPlay();
	//CameraController.SetCamera(nullptr);
}
