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
public:
	void AddDebugText(FString DebugText);
	void AddDebugError(FString ErrorText);
	void Clear();
	void Copy();
	void Option();

	void Render(float DeltaTime) override;
};

