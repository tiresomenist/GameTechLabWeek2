#pragma once

#include "UPrimitiveComponent.h"
#include "../../GResourceManager.h"
#include "../FClassType.h"

class UArrowBlueComponent : public UPrimitiveComponent
{

	UCLASS(UArrowBlueComponent, "ArrowBlue", UPrimitiveComponent)

public:

	virtual FPrimitiveRenderData GetRenderData(FStringView Type = "") override;

};