#include "Core.h"
#include "Container/FString.h"
#include "Engine/GEngine.h"
#include "Engine/FConsole.h"

void UE_LOG(FStringView Message)
{
	GEngine& Engine = *GEngine::GetInstance();
	FConsole& Console = *Engine.GetConsole();

	Console.Append(Message);
}