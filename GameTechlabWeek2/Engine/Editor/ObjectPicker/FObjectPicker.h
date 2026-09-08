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
	bool RayTriangleIntersect(const FRay& Ray, FVector A, FVector B, FVector C, float& OutDistance);
	UPrimitiveComponent* Pick();

private:
	FEditor* Editor;
};


