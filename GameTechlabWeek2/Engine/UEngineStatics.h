#pragma once

#include "Core.h"
#include "Engine/Object/UObject.h"

class UEngineStatics
{
public:
	static uint32 GenUUID()
	{
		return NextUUID++;
	};

	static constexpr float Epsilon = 1.0e-7f;

	inline static uint32 NextUUID = 0;
};
