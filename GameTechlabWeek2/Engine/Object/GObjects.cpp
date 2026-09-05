#include "GObjects.h"
#include <iostream>

void GObjects::AddObject(UObject* Object)
{
	GUObjectArray.Add(Object);
}

void GObjects::DestoryObject(uint32 InternalIndex)
{
	UObject* Object = GUObjectArray[InternalIndex];
	GUObjectArray.RemoveAt(InternalIndex);
	delete Object;
}

uint32 GObjects::GetNextIndex()
{
	return GUObjectArray.Num();
}

void GObjects::Release()
{
	
}
