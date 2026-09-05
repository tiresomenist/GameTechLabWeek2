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
