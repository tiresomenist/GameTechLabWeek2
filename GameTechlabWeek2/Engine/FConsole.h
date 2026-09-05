#pragma once

#include "Container/TArray.h"
#include "Container/FString.h"

#include "Core.h"

class FConsole
{
private:
	TArray<FString> MessageList;
	int32 MaxMessages = 100;

public:
	const TArray<FString> Get(FString Filter) const;

	void Initialize();

	void Append(FStringView Message);
	void Clear();

	void SetMaxMessages(int32 Num);

};
