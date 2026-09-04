#pragma once

#include "Core.h"
#include "Object/UObject.h"

class UEngineStatics
{
public:
	static constexpr float Epsilon = 1.0e-7f;

	inline static unsigned int NextUUID = 1;
	static uint32 GenUUID();
};
