#pragma once

class FObjectFactory
{

public:
	template <UObject T>
	static T* CreateObject(/* RTTI type info argument */)
	{
		nullptr;
	}
};