#pragma once

#include "Core.h"

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
