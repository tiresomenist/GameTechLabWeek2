#pragma once

#include <stdexcept>

#include "Engine/Object/FClassType.h"
#include "Engine/Object/UObject.h"
#include "Engine/Object/GObjectStatics.h"

class FObjectFactory
{

public:

	static UObject* ConstructObject(FClassType* Type)
	{
		if (Type == nullptr)
		{
			throw std::logic_error("ConstructObject: Type is nullptr");
		}

		uint32 UUID = GObjectStatics::GenUUID();
		uint32 InternalIndex = GObjectStatics::GetNextIndex();

		UObject* Object = Type->ClassConstructor(UUID, InternalIndex, Type);

		Object->Initialize();

		GObjectStatics::AddObject(Object);
		
		return Object;
	}
};
