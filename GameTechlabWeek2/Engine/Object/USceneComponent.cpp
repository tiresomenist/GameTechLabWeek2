#include "USceneComponent.h"

UObject* USceneComponent::CreateObject(uint32 UUID, uint32 InternalIndex)
{
	return new USceneComponent(UUID, InternalIndex);
}

FClassType* USceneComponent::GetClass()
{
	static FClassType Type{ FString{"SceneComponent"}, USceneComponent::CreateObject, FClassType::ECT_USceneComponent };
	return &Type;
}

USceneComponent::USceneComponent(uint32 InUUID, uint32 InInternalIndex)
	: UObject{ InUUID, InInternalIndex }
{
}
