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
	uint32 prevLogIndex = 0;
	uint32 displayStartIndex = 0;
public:
	~UConsoleWindow() = default;

	void AddDebugText();
	void AddDebugError();
	void Clear(uint32 prevlogindex);
	void Copy();
	void Option();
	void UpdateEditorWindow(const FConsole& console);
};

