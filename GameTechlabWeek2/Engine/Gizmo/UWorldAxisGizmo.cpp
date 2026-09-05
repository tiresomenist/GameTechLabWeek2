#include "../Core.h"
#include "UWorldAxisGizmo.h"
#include "Engine/Object/UObject.h"

FClassType* UWorldAxisGizmo::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new UWorldAxisGizmo(UUID, InternalIndex, InClassType);
		};

	static FClassType Type
	{
		.Name = "WorldAxisGizmo",
		.ClassConstructor = CreateObject,
		.ParentClassType = UGizmo::GetClass(),
	};

	return &Type;
}

UWorldAxisGizmo::UWorldAxisGizmo(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
	: UGizmo{ InUUID, InInternalIndex, InClassType }
{

}

void UWorldAxisGizmo::Create(FRenderer& renderer)
{

}
