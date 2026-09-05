#pragma once

#include "UPrimitiveComponent.h"

class USpherePrimitive : public UPrimitiveComponent
{
public:
    ~USpherePrimitive() {};

protected:
    USpherePrimitive(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
        : UPrimitiveComponent(InUUID, InInternalIndex, InClassType) {
    };
};
