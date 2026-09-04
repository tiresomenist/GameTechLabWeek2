#pragma once

#include <stdexcept>

#include <type_traits>

#include "FClassType.h"
#include "UObject.h"
#include "GObjects.h"
#include "../UEngineStatics.h"

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

		UObject* Object = Type->ClassConstructor(UUID, InternalIndex);
		GObjects::AddObject(Object);

		return Object;
	}
};