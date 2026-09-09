#include "UObject.h"
#include "Engine/Object/GObjectStatics.h"
#include "Engine/GAllocator.h"
#include "Engine/Object/FArchive.h"
#include "Engine/Log.h"

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
	UE_LOG("Object Created: {}", InClassType->Name);
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

void UObject::Initialize()
{
}

void* UObject::operator new(size_t Size)
{
	return GAllocator::Allocate(Size);
}

void UObject::operator delete(void* Ptr)
{
	GAllocator::Free(Ptr);
}

UObject::~UObject()
{
	GObjectStatics::DestoryObject(InternalIndex);
}

void UObject::Serialize(FArchive& Archive)
{
	// FClassType의 Serialize 이름 지정
	Archive.SetString("Type", ClassType->Name);
}

void UObject::Deserialize(FArchive& Archive)
{
	
}
