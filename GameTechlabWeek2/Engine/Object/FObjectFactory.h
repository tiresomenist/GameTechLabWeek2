#pragma once

#include <stdexcept>

#include "Engine/Object/FClassType.h"
#include "Engine/Object/UObject.h"
#include "Engine/Object/GObjects.h"
#include "Engine/UEngineStatics.h"

class FObjectFactory
{

public:

	static UObject* ConstructObject(FClassType* Type)
	{
		if (Type == nullptr)
		{
			throw std::logic_error("ConstructObject: Type is nullptr");
		}

		uint32 UUID = UEngineStatics::GenUUID();
		uint32 InternalIndex = GObjects::GetNextIndex();

		UObject* Object = Type->ClassConstructor(UUID, InternalIndex, Type);
		GObjects::AddObject(Object);

		return Object;
	}
};