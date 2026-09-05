#pragma once
#include "../../Container/TArray.h"
#include "../Core.h"

// 전방 선언
class UObject;

class GObjects
{
public:
	inline static TArray<UObject*> GUObjectArray;

	inline static uint32 TotalAllocationBytes;
	inline static uint32 TotalAllocationCount;

	static void AddObject(UObject* Object);
	static void DestoryObject(uint32 InternalIndex);
	static uint32 GetNextIndex();
};

