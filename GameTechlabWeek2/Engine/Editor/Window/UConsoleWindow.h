#pragma once

#include "UEditorWindow.h"
#include "../../../Container/FString.h"
#include "../../../Container/TArray.h"
#include "../../FConsole.h"
#include "../../Core.h"
#include "../../../Matrix.h"

class UConsoleWindow : public UEditorWindow
{
private:
	FString Filter;
	//FConsole Console;
	TArray<FString> logs; // Tick에서는 현재 UConsoleWindow에 저장된 logs 만 출력한다.
						  // 즉, FConsole에 디버그 메세지가 추가될 때마다 FEditor에서는 UConsoleWindow의 logs에 추가해줘야함
public:
	UConsoleWindow()
	{
		Begin();
	}
	~UConsoleWindow() = default;

	void AddDebugText(FString DebugText); //DebugText를 추가
	void AddDebugError(FString ErrorText); //ErrorText를 추가
	void Clear(); // logs에 있는 내용들을 지운다.
	void Copy();  // logs에 있는 내용을 클립보드에 복사한다.
	void Option();
	void Tick() override;
	void Begin() override;
	void End() override;
};

