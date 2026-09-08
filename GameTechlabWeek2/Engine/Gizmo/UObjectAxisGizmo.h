#pragma once

#include "UGizmo.h"



class UObjectAxisGizmo : public UGizmo
{
	UCLASS(UObjectAxisGizmo, "ObjectAxisGizmo", UGizmo)

public:
	TArray<FPrimitiveRenderData> GetRenderData() override;

private:
	FVector GizmoScale = FVector(0.2f,0.2f,0.5f);
	FMatrix XAxisWorldMatrix = FMatrix::MakeRotationYMatrix(PI / 2);
	FMatrix YAxisWorldMatrix = FMatrix::MakeRotationXMatrix(-PI / 2);
	FMatrix ZAxisWorldMatrix = FMatrix::Identity;
};

