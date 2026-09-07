#pragma once
#include "Engine/Editor/UEditorWindow.h"
#include "../../../Matrix.h"
#include "../../../FQuaternion.h"
#include "../../../Container/FString.h"

class UPropertyWindow : public UEditorWindow
{
public:
	void Render() override;
};