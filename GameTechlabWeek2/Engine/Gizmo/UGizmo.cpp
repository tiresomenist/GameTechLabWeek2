#include "UGizmo.h"
#include "Engine/Object/UObject.h"

FClassType* UGizmo::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new UGizmo(UUID, InternalIndex, InClassType);
		};

	static FClassType Type{ "Gizmo", CreateObject, UObject::GetClass() };
	return &Type;
}


UGizmo::UGizmo(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
	: UObject{ InUUID, InInternalIndex, InClassType }
