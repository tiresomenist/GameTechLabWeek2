#pragma once
#include "../../TArray.h"
#include "../Core.h"

// 전방 선언
class UObject;

class GObjects
{
public:
	static TArray<UObject*> GUObjectArray;

	static uint32 TotalAllocationBytes;
	static uint32 TotalAllocationCount;
};

