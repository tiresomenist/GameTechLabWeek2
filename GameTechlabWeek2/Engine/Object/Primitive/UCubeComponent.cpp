#include "UCubeComponent.h"

FClassType* UCubeComponent::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new UCubeComponent(UUID, InternalIndex, InClassType);
		};

	static FClassType Type
	{
		.Name = "UCubeComponent",
		.ClassConstructor = CreateObject,
		.ParentClassType = UPrimitiveComponent::GetClass(),
	};

	return &Type;
}