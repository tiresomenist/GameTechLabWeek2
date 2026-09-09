#include "FConsole.h"
#include "windows.h"

const TDeque<FString>& FConsole::Get() const
{
	return MessageList;
}

void FConsole::Initialize()
{
}

void FConsole::Append(FStringView Message)
{
	FString Item = FString(Message);
	MessageList.PushLast(Item); 

	if (MessageList.Num() > MaxMessages)
	{
		MessageList.PopFirst();
	}
}

void FConsole::Clear()
{
	MessageList.Reset();
}

void FConsole::SetMaxMessages(int32 Num)
{
	MaxMessages = Num;

	while (MessageList.Num() > Num)
	{
		MessageList.PopFirst();
	}
}
