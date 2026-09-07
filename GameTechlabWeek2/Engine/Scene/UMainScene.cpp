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

    //CreateMainCamera();
}

void UMainScene::Tick(float DeltaTime)
{
    //UScene::Tick(DeltaTime);

}

void UMainScene::EndPlay()
{
	//UScene::EndPlay();
}
