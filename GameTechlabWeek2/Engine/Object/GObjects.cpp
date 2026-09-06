#include "GObjects.h"
#include "Engine/Object/UObject.h"

#include <iostream>

void GObjects::AddObject(UObject* Object)
{
	GUObjectArray.Add(Object);
}

void GObjects::DestoryObject(uint32 InternalIndex)
{
	GUObjectArray[InternalIndex] = nullptr;
}

uint32 GObjects::GetNextIndex()
{
	return GUObjectArray.Num();
}

void GObjects::Release()
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
