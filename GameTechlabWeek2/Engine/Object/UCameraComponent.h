#pragma once

#include "Engine/Core.h"
#include "Engine/Object/USceneComponent.h"

class UCameraComponent : public USceneComponent
{
public:
    UCameraComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

    static UObject* CreateObject(uint32 UUID, uint32 InternalIndex, FClassType* InClassType);
    static FClassType* GetClass();
};

