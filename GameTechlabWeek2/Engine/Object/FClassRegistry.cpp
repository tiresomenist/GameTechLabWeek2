#include "FClassRegistry.h"
#include "Engine/Object/FClassType.h"

#include <cassert>
#include <format>

void* FClassRegistry::__INTERNAL__Add(FClassType* Type)
{
	for (auto Item : ClassTypeList)
	{
		if (Item->Name == Type->Name)
		{
			assert(std::format("FClassType.Name이 중복되었습니다. 중복되는 이름: {}", Item->Name).c_str());
		}
	}

	ClassTypeList.Add(Type);
	return nullptr;
}

FClassType* FClassRegistry::FindClassType(FStringView TypeName)
{
	for (auto Item : ClassTypeList)
	{
		if (Item->Name == TypeName)
		{
			return Item;
		}
	}

	return nullptr;
}