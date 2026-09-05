#pragma once
#include "../../Container/TArray.h"
#include "../Core.h"

// 전방 선언
class UObject;

class GObjects
{
public:
	inline static TArray<UObject*> GUObjectArray;

	static void AddObject(UObject* Object);
	static void DestoryObject(uint32 InternalIndex);
	static uint32 GetNextIndex();

	static void Release();
};

