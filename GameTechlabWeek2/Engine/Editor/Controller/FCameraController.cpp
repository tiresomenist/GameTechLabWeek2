#include "FCameraController.h"
#include "Engine/InputManager/GInputManager.h"
#include "Engine/Object/UCameraComponent.h"

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
        const float RadiansPerPixel = RotationSensitivity * Pi / 180.0f;
        const FQuaternion Yaw = FQuaternion::FromAxisAngle(
            FVector(0, 0, 1), DeltaX * RadiansPerPixel);
        const FQuaternion Pitch = FQuaternion::FromAxisAngle(
            FVector(0, 1, 0), DeltaY * RadiansPerPixel);
        // Local up, then the updated local right. Preserve roll and full turns.
        Camera->SetRelativeRotation(Camera->GetRelativeRotation() * Yaw * Pitch);
    }

    const float Forward = float(Input.GetKey(GInputManager::EI_W)) - float(Input.GetKey(GInputManager::EI_S));
    const float Right = float(Input.GetKey(GInputManager::EI_D)) - float(Input.GetKey(GInputManager::EI_A));
    Camera->MoveCamera(Forward, Right, DeltaTime);
}
