#pragma once

#include "UGizmo.h"



class UObjectAxisGizmo : public UGizmo
{
	UCLASS(UObjectAxisGizmo, "ObjectAxisGizmo", UGizmo)

public:
	virtual void Initialize()override;
	bool UpdateTransform();
	UObjectAxisGizmo();
	TArray<FPrimitiveRenderData> GetRenderData() override;
	TArray<FPrimitiveRenderData> GetTranslateRenderData();
	TArray<FPrimitiveRenderData> GetRotateRenderData();
	TArray<FPrimitiveRenderData> GetScaleRenderData();
	FMatrix GetXAxisWorldMatirx()const;
	FMatrix GetYAxisWorldMatirx()const;
	FMatrix GetZAxisWorldMatirx()const;
	//void Set

	const TArray<FGizmoHandle>& GetHandles() const { return Handles; }
	void SetMode(EGizmoMode InMode);
private:
	// X,Y,Z 핸들
	FVector GizmoScale = FVector(1.0f,1.0f,2.5f);
};

