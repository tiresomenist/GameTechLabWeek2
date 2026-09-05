#pragma once

#include "UPrimitiveComponent.h"

class UPlaneComponent : public UPrimitiveComponent
{

	UCLASS(UPlaneComponent, "Plane", UPrimitiveComponent)

public:

	virtual FPrimitiveRenderData GetRenderData(FStringView Type = "") override;

};

