#pragma once

#include "UPrimitiveComponent.h"
#include "../../GResourceManager.h"
#include "../FClassType.h"

class UArrowRedComponent : public UPrimitiveComponent
{

	UCLASS(UArrowRedComponent, "ArrowRed", UPrimitiveComponent)

public:

	virtual FPrimitiveRenderData GetRenderData(FStringView Type = "") override;

};