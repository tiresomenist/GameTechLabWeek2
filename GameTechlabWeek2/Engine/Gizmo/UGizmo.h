#pragma once

#include "../Core.h"
#include "../Object/FClassType.h"
#include "../FEditor.h"
#include "../../Matrix.h"
#include "../FRenderer.h"
#include "Engine/Object/UObject.h"

struct FGizmoVertex
{
	FVector Position;
	FVector4 Color;
};

class UGizmo : public UObject
{
    UCLASS(UGizmo, "Gizmo", UObject)

public:
	virtual ~UGizmo();

public:

	void SetVisible(bool bVisible);
	bool IsVisible();


protected:
	ID3D11Buffer* vertexBuffer = nullptr;
	uint32 VertexCount = 0;
	bool bVisible = true;
};
