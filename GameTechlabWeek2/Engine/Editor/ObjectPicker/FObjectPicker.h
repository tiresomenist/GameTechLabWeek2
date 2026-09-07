#pragma once
#include "../../Object/UCameraComponent.h"
#include "../../GResourceManager.h"
#include "../../Object/Primitive/UPrimitiveComponent.h"

class UScene;

struct FRay {
	FVector Origin;
	FVector Direction;
};

class FObjectPicker
{
public:
	FObjectPicker(UCameraComponent* InCamera, UScene* InScene);
	~FObjectPicker();
	void Tick();
	bool MakeWorldRay(FRay& OutRay);
	UPrimitiveComponent* Pick();
private:
	UCameraComponent* Camera;
	UScene* Scene;
};


