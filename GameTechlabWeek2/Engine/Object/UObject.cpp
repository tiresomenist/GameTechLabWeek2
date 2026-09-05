#include "UObject.h"
#include "Engine/Object/GObjects.h"
#include "Engine/GAllocator.h"

FClassType* UObject::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new UObject(UUID, InternalIndex, InClassType);
		};

	static FClassType Type
	{
		.Name = "Object",
		.ClassConstructor = CreateObject,
	};

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

void* UObject::operator new(size_t Size)
{
	void* RawPtr = GAllocator::Allocate(Size);
	return RawPtr;
}

// TODO: delete에 Size를 0으로 두면 안됨
// 이 부분은 GAllocator의 구조를 다시 수정할 것
void UObject::operator delete(void* Ptr)
{
	GAllocator::Free(Ptr, 0);
}

UObject::~UObject()
{
	GObjects::DestoryObject(InternalIndex);
}
