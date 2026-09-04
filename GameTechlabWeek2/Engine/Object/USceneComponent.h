#pragma once

#include "UObject.h"
#include "../Core.h"
#include "../../FVector.h"

class USceneComponent : public UObject
{
private:
public:
    USceneComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

    static UObject* CreateObject(uint32 UUID, uint32 InternalIndex, FClassType* InClassType);
    static FClassType* GetClass();

    FVector RelativeLocation;
    FVector RelativeRotation;
    FVector RelativeScale3D;


};

