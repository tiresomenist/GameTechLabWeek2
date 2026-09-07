#include "UMainScene.h"
#include "Engine/GEngine.h"
#include "Engine/Core.h"
#include "Engine/InputManager/GInputManager.h"
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

	//CameraController.SetCamera(GetMainCamera());
	//GetMainCamera()->SetRelativeLocation(FVector(-5.0f, 0.0f, 0.0f));

	USphereComponent* Sphere = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
	Sphere->SetRelativeLocation(FVector(0.0f, 0.5f, 0.0f));

	USphereComponent* Sphere1 = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
	Sphere1->SetRelativeLocation(FVector(0.0f, 0.5f, 1.0f));

	UCubeComponent* Cube = SpawnObject<UCubeComponent*>(UCubeComponent::GetClass());
	Cube->SetRelativeLocation(FVector(-2.0f, -0.5f, 1.0f));

	UPlaneComponent* Plane = SpawnObject<UPlaneComponent*>(UPlaneComponent::GetClass());
	Plane->SetRelativeLocation(FVector(3.0f, -0.5f, 0.0f));

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
