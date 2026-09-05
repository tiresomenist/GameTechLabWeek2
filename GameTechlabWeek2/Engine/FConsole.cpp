#include "FConsole.h"
#include "windows.h"

#include <iostream>

const TArray<FString> FConsole::Get(FString Filter) const
{
	return MessageList;
}

void FConsole::Initialize()
{
	if (!AllocConsole())
		return;

	FILE* stream = nullptr;

	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONOUT$", "w", stderr);
	freopen_s(&stream, "CONIN$", "r", stdin);

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	std::ios::sync_with_stdio(true);

	SetConsoleTitleW(L"Debug Console");
}

void FConsole::Append(FStringView Message)
{
	FString Item = FString(Message);
	MessageList.Add(Item);

	// 임시
	std::cout << Item << '\n';
}

void FConsole::Clear()
{
	MessageList.Empty();
}

void FConsole::SetMaxMessages(int32 Num)
{
	MaxMessages = Num;
}
