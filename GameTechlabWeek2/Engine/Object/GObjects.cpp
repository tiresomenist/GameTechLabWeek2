#include "GObjects.h"
#include <iostream>

void GObjects::AddObject(UObject* Object)
{
	GUObjectArray.Add(Object);
}

void GObjects::DestoryObject(uint32 InternalIndex)
{
	UObject* Object = GUObjectArray[InternalIndex];
	delete Object;

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
}
