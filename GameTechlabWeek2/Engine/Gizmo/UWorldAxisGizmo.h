#pragma once

#include "../Core.h"
#include "../FEditor.h"
#include "UGizmo.h"
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
public:
    UWorldAxisGizmo(uint32 InUUID,uint32 InInternalIndex,FClassType* InClassType);

    ~UWorldAxisGizmo() override = default;

    static FClassType* GetClass();

    void Create(FRenderer& renderer) override;
    void Render(FRenderer& renderer) override;
    void Release() override;
};

