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
#include "Engine/Gizmo/UWorldAxisGizmo.h"

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
