#include "FConsole.h"
#include "windows.h"

const TArray<FString> FConsole::Get(FString Filter) const
{
	return MessageList;
}

void FConsole::Initialize()
{
}

void FConsole::Append(FStringView Message)
{
	FString Item = FString(Message);
	MessageList.Add(Item);
}

void FConsole::Clear()
{
	MessageList.Empty();
}

void FConsole::SetMaxMessages(int32 Num)
{
	MaxMessages = Num;
}
