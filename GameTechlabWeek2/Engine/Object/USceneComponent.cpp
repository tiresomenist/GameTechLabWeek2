#include "USceneComponent.h"
#include "Engine/Object/UObject.h"
#include "FObjectFactory.h"

void USceneComponent::SetRelativeLocation(const FVector& Location)
{
	RelativeLocation = Location;
    UpdateWorldTransform();
}

void USceneComponent::SetRelativeRotation(const FQuaternion& Rotation)
{
	RelativeRotation = Rotation;
    RelativeRotation.Normalize();
    UpdateWorldTransform();
}

void USceneComponent::AddLocalRotation(const FQuaternion& Delta)
{
    SetRelativeRotation(RelativeRotation * Delta);
}

void USceneComponent::AddWorldRotation(const FQuaternion& Delta)
{
    // Components currently have no implemented parent-transform composition.
    SetRelativeRotation(Delta * RelativeRotation);
}

void USceneComponent::SetRelativeScale3D(const FVector& Scale3D)
{
	RelativeScale3D = Scale3D;
    UpdateWorldTransform();
}

const FMatrix& USceneComponent::GetWorldMatrix() const
{
    //if (bWorldMatrixDirty)
    return CachedWorldMatrix;
}

void USceneComponent::UpdateWorldTransform() const
{
    FMatrix LocalSRTMatrix = FMatrix::MakeScaleMatrix(RelativeScale3D)
        * RelativeRotation.ToRotationMatrix()
        * FMatrix::MakeTranslationMatrix(RelativeLocation);

    CachedWorldMatrix = LocalSRTMatrix;

    // 부모가 있으면 부모의 월드 행렬과 곱함
    //if (AttachParent)
    //{
    //    CachedWorldMatrix = LocalSRTMatrix * AttachParent->GetWorldMatrix();
    //}
    //else
    //{
    //    CachedWorldMatrix = LocalSRTMatrix;
    //}

    //bWorldMatrixDirty = false;
}
