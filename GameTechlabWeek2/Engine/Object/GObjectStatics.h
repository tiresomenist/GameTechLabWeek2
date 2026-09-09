#pragma once
#include "../../Container/TArray.h"
#include "../Core.h"

// 전방 선언
class UObject;

class GObjectStatics
{
public:
	inline static TArray<UObject*> GUObjectArray;
	inline static uint32 NextUUID = 0;

	static uint32 GenUUID()
	{
		return NextUUID++;
	}

	static void AddObject(UObject* Object);
	static void DestoryObject(uint32 InternalIndex);
	static uint32 GetNextIndex();

	static void SetNextIndex(uint32 Index);

	static void Release();
};

