#include "USphereComponent.h"

FClassType* USphereComponent::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new USphereComponent(UUID, InternalIndex, InClassType);
		};

	static FClassType Type
	{
		.Name = "USphereComponent",
		.ClassConstructor = CreateObject,
		.ParentClassType = UPrimitiveComponent::GetClass(),
	};

	return &Type;
}
