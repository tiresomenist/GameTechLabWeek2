#pragma once

#include "Engine/Object/UObject.h"

class UGizmo : public UObject
{
protected:
    UGizmo(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

public:

    static FClassType* GetClass();
};