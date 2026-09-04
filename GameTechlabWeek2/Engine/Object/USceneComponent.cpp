#include "USceneComponent.h"

UObject* USceneComponent::CreateObject(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
{
	return new USceneComponent(InUUID, InInternalIndex, InClassType);
}

FClassType* USceneComponent::GetClass()
{
	static FClassType Type{ FString{"SceneComponent"}, USceneComponent::CreateObject, FClassType::ECT_USceneComponent };
	return &Type;
}

USceneComponent::USceneComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
	: UObject{ InUUID, InInternalIndex, InClassType }
{
}
