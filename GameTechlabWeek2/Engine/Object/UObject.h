#pragma once

#include "Engine/Object/FClassType.h"
#include "Engine/Core.h"
#include "Container/FString.h"

#include <cstdlib>
#include <string>

/// UUID는 Scene을 JSON 직렬화/역직렬화 하는 과정에서도 Scene 내부의 UObject 사이의 참조 관계가 유지되도록 하기 위한 값입니다.
/// InternalIndex는 Scene에서 다른 객체를 참조할 때 사용됩니다.


class UObject
{
public:
    static FClassType* GetClass();

    FClassType* GetClassType();

    UObject(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

    uint32 UUID;
    uint32 InternalIndex;

    bool IsA(FClassType* InClassType) const;

private:
    FClassType* ClassType;
};

