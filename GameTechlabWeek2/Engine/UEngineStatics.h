#pragma once

#include "Core.h"
#include "Object/UObject.h"

class UEngineStatics
{
	static uint32 GenUUID()
	{
		return NextUUID++;
	}

	static uint32 NextUUID;
};
