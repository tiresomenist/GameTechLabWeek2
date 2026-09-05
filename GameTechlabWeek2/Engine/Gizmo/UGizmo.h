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
protected:
	UGizmo(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);
public:
	virtual ~UGizmo() = default;
	static FClassType* GetClass();

	virtual void Create(FRenderer& renderer) = 0;
	virtual void Render(FRenderer& renderer) = 0;
	virtual void Release() = 0;
};