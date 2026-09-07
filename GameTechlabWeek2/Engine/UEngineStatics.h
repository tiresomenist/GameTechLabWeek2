#pragma once

#include "Engine/Core.h"
#include "Engine/Object/UObject.h"

#include "Container/TArray.h"

class UEngineStatics
{
public:

	inline static uint32 NextUUID = 0;
	static uint32 GenUUID()
	{
		return NextUUID++;
	};

	static constexpr float Epsilon = 1.0e-7f;
};
