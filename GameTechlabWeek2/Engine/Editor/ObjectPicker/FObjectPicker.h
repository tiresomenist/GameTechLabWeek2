#pragma once

#include "FVector.h"

class UScene;
class FEditor;
class UPrimitiveComponent;

struct FRay {
	FVector Origin;
	FVector Direction;
};

class FObjectPicker
{
public:
	FObjectPicker(FEditor* InEditor);
	void Tick();
	bool MakeWorldRay(FRay& OutRay);
	UPrimitiveComponent* Pick();

private:
	FEditor* Editor;
};


