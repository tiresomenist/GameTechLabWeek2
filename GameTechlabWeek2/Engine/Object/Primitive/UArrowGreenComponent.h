#pragma once

#include "UPrimitiveComponent.h"
#include "../../GResourceManager.h"
#include "../FClassType.h"

class UArrowGreenComponent : public UPrimitiveComponent
{

	UCLASS(UArrowGreenComponent, "ArrowGreen", UPrimitiveComponent)

public:

	virtual FPrimitiveRenderData GetRenderData(FStringView Type = "") override;

};