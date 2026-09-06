#pragma once

#include "Engine/Core.h"
#include "Engine/FEditor.h"
#include "Engine/Gizmo/UGizmo.h"
#include "Engine/Object/UObject.h"

FGizmoVertex Vertices[] =
{
	//X
	{ FVector(0.0f, 0.0f, 0.0f), FVector4(1.0f, 0.0f, 0.0f, 1.0f)},
	{ FVector(1.0f, 0.0f, 0.0f), FVector4(1.0f, 0.0f, 0.0f, 1.0f)},
	//Y
	{ FVector(0.0f, 0.0f, 0.0f), FVector4(0.0f, 1.0f, 0.0f, 1.0f)},
	{ FVector(0.0f, 1.0f, 0.0f), FVector4(0.0f, 1.0f, 0.0f, 1.0f)},
	//Z
	{ FVector(0.0f, 0.0f, 0.0f), FVector4(0.0f, 0.0f, 1.0f, 1.0f)},
	{ FVector(0.0f, 0.0f, 1.0f), FVector4(0.0f, 0.0f, 1.0f, 1.0f)}
};

class UWorldAxisGizmo : public UGizmo
{

	UCLASS(UWorldAxisGizmo, "WorldAxisGizmo", UGizmo)

public:
    void Create(FRenderer& Renderer) override;

};

