#pragma once

#include "Core.h"

class UEngineStatics
{
public:
	static uint32 GenUUID()
	{
		return NextUUID++;
	};

	inline static uint32 NextUUID = 0;
};
