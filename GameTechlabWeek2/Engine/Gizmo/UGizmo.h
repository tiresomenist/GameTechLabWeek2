#pragma once

#include "Engine/Object/UObject.h"

class UGizmo : public UObject
{
public:
    UGizmo(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

    static UObject* CreateObject(uint32 UUID, uint32 InternalIndex, FClassType* InClassType);
    static FClassType* GetClass();
};