#pragma once

#include "Engine/Object/UObject.h"
#include "Engine/Core.h"
#include "FVector.h"
#include "../../Matrix.h"


class USceneComponent : public UObject
{

    UCLASS(USceneComponent, "SceneComponent", UObject)

public:
    FVector& GetRelativeLocation() { return RelativeLocation; };
    FVector& GetRelativeRotation() { return RelativeRotation; };
    FVector& GetRelativeScale3D() { return RelativeScale3D; };

    void SetRelativeLocation(const FVector& Location);
    void SetRelativeRotation(const FVector& Rotation);
    void SetRelativeScale3D(const FVector& Scale3D);

    const FMatrix& GetWorldMatrix() const;

protected:
    // 로컬 트랜스폼
    FVector RelativeLocation;
    FVector RelativeRotation;
    FVector RelativeScale3D;

    // 계층 구조(구현X)
    USceneComponent* AttachParent = nullptr;
    std::vector<USceneComponent*> AttachChildren;

    // 최종 월드 행렬 캐싱 & 더티 플래그(구현X)
    mutable FMatrix CachedWorldMatrix;
    mutable bool bWorldMatrixDirty = true;

    void UpdateWorldTransform() const;
};

