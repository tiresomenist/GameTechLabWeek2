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
protected:
    UWorldAxisGizmo(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

public:
    static FClassType* GetClass();


    void Create(FRenderer& renderer);
    //void Render(FRenderer& renderer);
    //void Release();
};

