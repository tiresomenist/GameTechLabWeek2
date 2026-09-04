#include "GObjects.h"
#include <iostream>

void GObjects::AddObject(UObject* Object)
{
	GUObjectArray.Add(Object);
}


void GObjects::DestoryObject(uint32 InternalIndex)
{
	GUObjectArray.RemoveAt(InternalIndex);
}

uint32 GObjects::GetNextIndex()
{
	return GUObjectArray.Num();
}
