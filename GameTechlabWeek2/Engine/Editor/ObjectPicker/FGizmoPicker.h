#pragma once

#include "Engine/Object/UCameraComponent.h"
#include "Engine/GResourceManager.h"
#include "Engine/Gizmo/UGizmo.h"

class UScene;

struct FRay;

class FGizmoPicker
{
public:
	FGizmoPicker(UCameraComponent* InCamera);
	~FGizmoPicker();
	void Tick();
	bool RayTriangleIntersect(const FRay& Ray, FVector A, FVector B, FVector C, float& OutDistance);
	bool MakeWorldRay(FRay& OutRay);
	int Pick(UGizmo* InGizmos);
private:
	UCameraComponent* Camera;
};
