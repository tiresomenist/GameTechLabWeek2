#include "FCameraController.h"
#include "Engine/InputManager/GInputManager.h"
#include "Engine/Object/UCameraComponent.h"
#include <algorithm>
#include <cmath>

#include <format>

void FCameraController::SetCamera(UCameraComponent* InCamera)
{
    Camera = InCamera;
    //이전 카메라의 물리량을 반영하면 안됨
    int32 DeltaX = 0, DeltaY = 0;
    GInputManager::GetInstance()->ConsumeRightDragDelta(DeltaX, DeltaY);
}

void FCameraController::Tick(float DeltaTime)
{
    if (!Camera) return;

    auto& Input = *GInputManager::GetInstance();
    int32 DeltaX = 0, DeltaY = 0;
    Input.ConsumeRightDragDelta(DeltaX, DeltaY);

    if (Input.GetKey(GInputManager::EI_RMOUSE) && (DeltaX != 0 || DeltaY != 0))
    {
        constexpr float Pi = static_cast<float>(PI);
        //constexpr float PitchLimit = 180.0f * Pi / 180.0f;
        const float RadiansPerPixel = RotationSensitivity * Pi / 180.0f;
        FVector Rotation = Camera->GetRelativeRotation();
        Rotation.Z = std::remainder(Rotation.Z + DeltaX * RadiansPerPixel, 2.0f * Pi);
        Rotation.Y = std::remainder(Rotation.Y + DeltaY * RadiansPerPixel, 2.0f * Pi);
        Rotation.X = 0.0f;
        Camera->SetRelativeRotation(Rotation);
        UE_LOG(std::format("현재 Forward Vector ({}, {}, {}) ",Rotation.X, Rotation.Y, Rotation.Z));
    }

    const float Forward = float(Input.GetKey(GInputManager::EI_W)) - float(Input.GetKey(GInputManager::EI_S));
    const float Right = float(Input.GetKey(GInputManager::EI_D)) - float(Input.GetKey(GInputManager::EI_A));
    Camera->MoveCamera(Forward, Right, DeltaTime);
}
