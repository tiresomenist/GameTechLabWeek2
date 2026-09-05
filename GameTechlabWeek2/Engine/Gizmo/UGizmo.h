#pragma once

<<<<<<< HEAD
#include "../FEditor.h"
#include "../../Matrix.h"
#include "../../URenderer.h"


struct FGizmoVertex
{
	FVector Position;
	FVector4 Color;
};

class UGizmo : public FEditor
{
public :
	UGizmo() = default;
	virtual ~UGizmo() = default;

	void Create(URenderer& renderer);
	void Render(URenderer& renderer);
	void Release();

	void SetVisible(bool bVisible);
	bool IsVisible();
protected :
	ID3D11Buffer* vertexBuffer = nullptr;
	uint32 VertexCount = 0;
	bool bVisible = true;
=======
#include "../Object/UObject.h"

class UGizmo : public UObject
{

>>>>>>> main
};