#include "UCameraComponent.h"
#include "Engine/Object/UObject.h"

UCameraComponent::UCameraComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
	: USceneComponent{ InUUID, InInternalIndex, InClassType }
{
}

FClassType* UCameraComponent::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new USceneComponent(UUID, InternalIndex, InClassType);
		};

	static FClassType Type{ "CameraComponent", CreateObject, UObject::GetClass() };
	return &Type;
}
