#include "FConsole.h"
#include "windows.h"

// 18번 필터없애고 참조
const TArray<FString> FConsole::Get(FString Filter) const
{
	// 18번 최대개수 제한걸어야함
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
