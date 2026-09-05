#pragma once

#include "Engine/Object/UObject.h"
#include "Engine/Core.h"
#include "FVector.h"

class USceneComponent : public UObject
{
private:
    FVector RelativeLocation;
    FVector RelativeRotation;
    FVector RelativeScale3D;

public:
    USceneComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

    static UObject* CreateObject(uint32 UUID, uint32 InternalIndex, FClassType* InClassType);
    static FClassType* GetClass();

    FVector& GetRelativeLocation() { return RelativeLocation; };
    FVector& GetRelativeRotation() { return RelativeRotation; };
    FVector& GetRelativeScale3D() { return RelativeScale3D; };

    void SetRelativeLocation(const FVector& Location);
    void SetRelativeRotation(const FVector& Rotation);
    void SetRelativeScale3D(const FVector& Scale3D);
};

