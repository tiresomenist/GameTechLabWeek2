#include "UMainScene.h"
#include "Engine/GEngine.h"
#include "Engine/Core.h"
#include "Engine/InputManager/GInputManager.h"
#include "Engine/Object/UCameraComponent.h"
#include "Engine/Gizmo/UWorldAxisGizmo.h"

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
    // Temporary world-axis display. Remove this spawn to disable it.
    SpawnObject<UWorldAxisGizmo*>(UWorldAxisGizmo::GetClass());
    CameraController.SetCamera(GetMainCamera());
	GetMainCamera()->SetRelativeLocation(FVector(-5.0f, 0.0f, 0.0f));

	USphereComponent* Sphere = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
	Sphere->SetRelativeLocation(FVector(0.0f, 0.5f, 0.0f));
	USphereComponent* Sphere1 = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
	Sphere1->SetRelativeLocation(FVector(0.0f, 0.5f, 1.0f));

	UCubeComponent* Cube = SpawnObject<UCubeComponent*>(UCubeComponent::GetClass());
	Cube->SetRelativeLocation(FVector(0.0f, -0.5f, 0.0f));

	UPlaneComponent* Plane = SpawnObject<UPlaneComponent*>(UPlaneComponent::GetClass());
	Plane->SetRelativeLocation(FVector(0.0f, -0.5f, 0.0f));
	USphereComponent* Sphere2 = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
	Sphere2->SetRelativeLocation(FVector(0.0f, -0.5f, 0.0f));

	USphereComponent* Sphere3 = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
	Sphere3->SetRelativeLocation(FVector(-5.0f, -0.5f, -6.0f));

	USphereComponent* Sphere4 = SpawnObject<USphereComponent*>(USphereComponent::GetClass());
	Sphere4->SetRelativeLocation(FVector(-10.0f, -0.5f, 0.0f));

}

void UMainScene::Tick(float DeltaTime)
{
    //UScene::Tick(DeltaTime);


	GEngine& Engine = *GEngine::GetInstance();
	GInputManager& Input = *GInputManager::GetInstance();

	float Time = Engine.GetTime();
	if (Input.GetKey(GInputManager::EI_LMOUSE)) {
		//UE_LOG(std::format("[{}] 좌클릭 좌표:{}, {}", Time,
		//	Input.GetLeftCursorX(),
		//	Input.GetLeftCursorY()));

	}
	if (Input.GetKey(GInputManager::EI_RMOUSE)) {
		//UE_LOG(std::format("[{}] 우클릭 좌표:{}, {}", Time,
		//	GInputManager::GetInstance()->GetRightCursorX(),
		//	GInputManager::GetInstance()->GetRightCursorY()));

	}
	CameraController.Tick(DeltaTime);

}

void UMainScene::EndPlay()
{
	//UScene::EndPlay();
	CameraController.SetCamera(nullptr);
}
