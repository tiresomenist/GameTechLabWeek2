#include "GAllocator.h"
#include "Core.h"
#include <format>
#include "Core.h"

void* GAllocator::Allocate(uint32 Size)
{
	// Note: 동적 할당에 실패하면 여기서 std::bad_alloc가 throw 될 수 있음.
	// ex) OutOfMemory
	void* ptr = ::operator new(Size);

	TotalAllocationBytes += Size;
	++TotalAllocationCount;

	return ptr;
}

void GAllocator::Free(void* Ptr, uint32 Size)
{
	TotalAllocationBytes -= Size;
	--TotalAllocationCount;

	::operator delete(Ptr);
}