#include "../Core.h"
#include "UWorldAxisGizmo.h"
#include "Engine/Object/UObject.h"

FClassType* UWorldAxisGizmo::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new UGizmo(UUID, InternalIndex, InClassType);
		};

	static FClassType Type
	{
		.Name = "WorldAxisGizmo",
		.ClassConstructor = CreateObject,
		.ParentClassType = UObject::GetClass(),
	};

	return &Type;
}

UWorldAxisGizmo::UGizmo(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
	: UObject{ InUUID, InInternalIndex, InClassType }
{

}

void UWorldAxisUGizmo::Create(FRenderer& renderer)
{

}
