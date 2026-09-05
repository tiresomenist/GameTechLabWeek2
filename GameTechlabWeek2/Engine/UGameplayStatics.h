#pragma once

#include "Engine/Object/UObject.h"
#include "Engine/Object/FClassType.h"
#include "Engine/Object/FObjectFactory.h"

template <typename T>
T SpawnObject(FClassType* Type)
{
	return Cast<T>(FObjectFactory::ConstructObject(Type));
}

template <typename T>
T Cast(UObject* Object)
{
	T Ptr = static_cast<T>(Object);
	return Ptr;
}

