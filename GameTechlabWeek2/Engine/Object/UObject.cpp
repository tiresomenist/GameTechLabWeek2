#include "UObject.h"
#include "GObjects.h"

UObject* UObject::CreateObject(uint32 UUID, uint32 InternalIndex)
{
	return new UObject(UUID, InternalIndex);
}

FClassType* UObject::GetClass()
{
	static FClassType Type{ FString{"Object"}, UObject::CreateObject, FClassType::ECT_UObject };
    return &Type;
}

UObject::UObject(uint32 InUUID, uint32 InInternalIndex)
	: UUID{ InUUID }
	, InternalIndex{ InInternalIndex }
{
}
