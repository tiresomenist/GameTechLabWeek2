#pragma once

#include "Engine/Core.h"

// 아주 간단한 Allocator
// 
// TODO: Linear Allocator, Pool Allocator, Stack Allocator 등
// 상황 및 메모리 생명주기에 맞는 다양한 Allocator 구현해보기.

class GAllocator
{
private:
	inline static uint32 TotalAllocationBytes;
	inline static uint32 TotalAllocationCount;

public:
	/// <summary>
	/// 새로운 메모리 공간을 할당
	/// </summary>
	/// <param name="Size">할당 받을 메모리 바이트</param>
	/// <returns>할당된 포인터 (초기화 필요)</returns>
	static void* Allocate(uint32 Size);
	
	/// <summary>
	/// 할당된 메모리 공간을 반환
	/// </summary>
	/// <param name="Ptr">반환할 메모리</param>
	/// <param name="Size">반환할 메모리의 크기</param>
	static void Free(void* Ptr, uint32 Size);

	static uint32 GetTotalAllocationBytes() { return TotalAllocationBytes; };
	static uint32 GetTotalAllocationCount() { return TotalAllocationCount; };
};