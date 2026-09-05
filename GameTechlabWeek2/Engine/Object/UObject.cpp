#include "UObject.h"
#include "GObjects.h"

UObject* UObject::CreateObject(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
{
	return new UObject(InUUID, InInternalIndex, InClassType);
}

FClassType* UObject::GetClass()
{
	static FClassType Type{ FString{"Object"}, UObject::CreateObject, FClassType::ECT_UObject };
    return &Type;
}

UObject::UObject(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
	: UUID{ InUUID }
	, InternalIndex{ InInternalIndex }
	, ClassType{ InClassType }
{
}
