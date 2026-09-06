#pragma once

#include "UGizmo.h"

class UWorldAxisGizmo : public UGizmo
{

	UCLASS(UWorldAxisGizmo, "WorldAxisGizmo", UGizmo)

public:
    void Create(FRenderer& Renderer) override;

};

