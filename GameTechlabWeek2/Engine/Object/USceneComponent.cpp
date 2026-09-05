#include "USceneComponent.h"
#include "Engine/Object/UObject.h"

FClassType* USceneComponent::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new USceneComponent(UUID, InternalIndex, InClassType);
		};

	static FClassType Type
	{
		.Name = "SceneComponent",
		.ClassConstructor = CreateObject,
		.ParentClassType = UObject::GetClass(),
	};

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
