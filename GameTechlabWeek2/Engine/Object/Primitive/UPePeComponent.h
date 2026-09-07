#pragma once

#include "UPrimitiveComponent.h"
#include "../../GResourceManager.h"
#include "../FClassType.h"

class UPepeComponent : public UPrimitiveComponent
{

	UCLASS(UPepeComponent, "Pepe", UPrimitiveComponent)

public:

	virtual FPrimitiveRenderData GetRenderData(FStringView Type = "") override;

};
