#include "USceneComponent.h"
#include "Engine/Object/UObject.h"

UObject* USceneComponent::CreateObject(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
{
	return new USceneComponent(InUUID, InInternalIndex, InClassType);
}

FClassType* USceneComponent::GetClass()
{
	static FClassType Type{ FString{"SceneComponent"}, USceneComponent::CreateObject, UObject::GetClass() };
	return &Type;
}

void USceneComponent::SetRelativeLocation(const FVector& Location)
{
	RelativeLocation = Location;
}

void USceneComponent::SetRelativeRotation(const FVector& Rotation)
{
	RelativeRotation = Rotation;
}

void USceneComponent::SetRelativeScale3D(const FVector& Scale3D)
{
	RelativeScale3D = Scale3D;
}

USceneComponent::USceneComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
	: UObject{ InUUID, InInternalIndex, InClassType }
{
}
