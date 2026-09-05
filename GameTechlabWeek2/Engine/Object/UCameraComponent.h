#pragma once

#include "Engine/Core.h"
#include "Engine/Object/USceneComponent.h"

class UCameraComponent : public USceneComponent
{
private:
    UCameraComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

public:
    static FClassType* GetClass();
};

