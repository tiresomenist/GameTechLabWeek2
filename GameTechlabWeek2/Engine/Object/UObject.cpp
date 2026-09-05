#include "UObject.h"
#include "Engine/Object/GObjects.h"
#include "FObjectFactory.h"

FClassType* UObject::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new UObject(UUID, InternalIndex, InClassType);
		};

	static FClassType Type{ "Object", CreateObject };
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
	const FClassType* CurrentType = ClassType;

	// 포인터 노드를 순회하며 타입을 검색합니다.
	while (CurrentType != nullptr)
	{
		if (CurrentType == InClassType)
		{
			return true;
		}

		CurrentType = CurrentType->ParentClassType;
	}

	return false;
}
