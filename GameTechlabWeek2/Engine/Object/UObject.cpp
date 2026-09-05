#include "UObject.h"
#include "Engine/Object/GObjects.h"

UObject* UObject::CreateObject(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
{
	return new UObject(InUUID, InInternalIndex, InClassType);
}

FClassType* UObject::GetClass()
{
	static FClassType Type{ FString{"Object"}, UObject::CreateObject };
    return &Type;
}

UObject::UObject(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
	: UUID{ InUUID }
	, InternalIndex{ InInternalIndex }
	, ClassType{ InClassType }
{
}

bool UObject::IsA(FClassType* InClassType) const
{
	// 두 포인터 비교
	return InClassType == ClassType;
}
