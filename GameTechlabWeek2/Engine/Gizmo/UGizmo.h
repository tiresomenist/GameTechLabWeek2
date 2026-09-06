#pragma once

#include "../FEditor.h"
#include "../../Matrix.h"
#include "../FRenderer.h"


struct FGizmoVertex
{
	FVector Position;
	FVector4 Color;
};
#include "Engine/Object/UObject.h"

class UGizmo : public UObject
{
    UCLASS(UGizmo, "Gizmo", UObject)

public:
	virtual ~UGizmo() = default;

	virtual void Create(FRenderer& renderer);
	void Render(FRenderer& renderer);
	void Release();

public:

	void SetVisible(bool bVisible);
	bool IsVisible();


protected:
	ID3D11Buffer* vertexBuffer = nullptr;
	uint32 VertexCount = 0;
	bool bVisible = true;
};
