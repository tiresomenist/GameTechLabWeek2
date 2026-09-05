#pragma once

#include "../FEditor.h"
#include "../../Matrix.h"
#include "../FRenderer.h"


struct FGizmoVertex
{
	FVector Position;
	FVector4 Color;
};

class UGizmo : public FEditor
{
public:
	UGizmo() = default;
	virtual ~UGizmo() = default;

	void Create(FRenderer& renderer);
	void Render(FRenderer& renderer);
	void Release();

	void SetVisible(bool bVisible);
	bool IsVisible();
protected:
	ID3D11Buffer* vertexBuffer = nullptr;
	uint32 VertexCount = 0;
	bool bVisible = true;
};
