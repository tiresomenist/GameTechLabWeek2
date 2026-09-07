#pragma once

#include "../../GEngine.h"
#include "../../FRenderer.h"
#include "../../../Container/TArray.h"
#include <Windows.h>


class UEditorWindow
{
public:
	UEditorWindow() = default;

	//virtual ~UEditorWindow() = 0;
	virtual void UpdateEditorWindow() = 0;
};