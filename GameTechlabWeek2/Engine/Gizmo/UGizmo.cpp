#include "UGizmo.h"
#include "Engine/Object/UObject.h"

UGizmo::UGizmo(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
	: UObject{ InUUID, InInternalIndex, InClassType }
{
}

UObject* UGizmo::CreateObject(uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
{
	return new UGizmo(UUID, InternalIndex, InClassType);
}

FClassType* UGizmo::GetClass()
{
	static FClassType Type{ FString{"Gizmo"}, UGizmo::CreateObject, UObject::GetClass()};
	return &Type;
}
