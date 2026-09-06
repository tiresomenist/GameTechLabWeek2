#pragma once

#include "UPrimitiveComponent.h"
#include "../../GResourceManager.h"
#include "../FClassType.h"

class USphereComponent : public UPrimitiveComponent
{
    
	UCLASS(USphereComponent, "Sphere", UPrimitiveComponent)

public:

	virtual FPrimitiveRenderData GetRenderData(FStringView Type = "") override;

};
