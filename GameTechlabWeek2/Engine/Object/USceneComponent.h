#pragma once

#include "UObject.h"
#include "../Core.h"

class USceneComponent : public UObject
{
public:
    static UObject* CreateObject(uint32 UUID, uint32 InternalIndex);
    static FClassType* GetClass();

    USceneComponent(uint32 InUUID, uint32 InInternalIndex);
};

