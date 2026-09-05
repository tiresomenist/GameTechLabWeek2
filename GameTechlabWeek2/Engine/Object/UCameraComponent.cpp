#include "UCameraComponent.h"
#include "Engine/Object/UObject.h"

UCameraComponent::UCameraComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
	: USceneComponent{ InUUID, InInternalIndex, InClassType }
{
}

UObject* UCameraComponent::CreateObject(uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
{
	return new UCameraComponent(UUID, InternalIndex, InClassType);
}

FClassType* UCameraComponent::GetClass()
{
	static FClassType Type{ FString{"CameraComponent"}, UCameraComponent::CreateObject, UObject::GetClass() };
	return &Type;
}
