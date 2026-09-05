#pragma once

#include "Engine/Object/UObject.h"
#include "Engine/Core.h"
#include "FVector.h"
#include "../../Matrix.h"
#include "FClassType.h"

class USceneComponent : public UObject
{
public:
    static FClassType* GetClass();

    FVector& GetRelativeLocation() { return RelativeLocation; };
    FVector& GetRelativeRotation() { return RelativeRotation; };
    FVector& GetRelativeScale3D() { return RelativeScale3D; };

    void SetRelativeLocation(const FVector& Location);
    void SetRelativeRotation(const FVector& Rotation);
    void SetRelativeScale3D(const FVector& Scale3D);

    const FMatrix& GetWorldMatrix() const;

protected:
    USceneComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

    // 로컬 트랜스폼
    FVector RelativeLocation;
    FVector RelativeRotation;
    // Transform의 기본 스케일은 단위 스케일이어야 한다. FVector의 기본값은
    // (0, 0, 0)이므로 명시하지 않으면 메시 정점이 원점으로 붕괴한다.
    FVector RelativeScale3D{ 1.0f, 1.0f, 1.0f };

    // 계층 구조(구현X)
    USceneComponent* AttachParent = nullptr;
    std::vector<USceneComponent*> AttachChildren;

    // 최종 월드 행렬 캐싱 & 더티 플래그(구현X)
    mutable FMatrix CachedWorldMatrix;
    mutable bool bWorldMatrixDirty = true;

    void UpdateWorldTransform() const;
};

