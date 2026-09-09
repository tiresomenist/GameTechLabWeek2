#include "GObjectStatics.h"
#include "Engine/Object/UObject.h"

#include <iostream>

void GObjectStatics::AddObject(UObject* Object)
{
	GUObjectArray.Add(Object);
}

void GObjectStatics::DestoryObject(uint32 InternalIndex)
{
	GUObjectArray[InternalIndex] = nullptr;
}

uint32 GObjectStatics::GetNextIndex()
{
	return GUObjectArray.Num();
}

void GObjectStatics::Release()
{
	for (auto& Item : GUObjectArray)
	{
		if (Item != nullptr)
		{
			delete Item;
		}
	}

	GUObjectArray.Empty();
}
