#pragma once

#include "Engine/Object/Primitive/UPrimitiveComponent.h"

class UCubeComponent : public UPrimitiveComponent
{

	UCLASS(UCubeComponent, "Cube", UPrimitiveComponent)

public:

	virtual FPrimitiveRenderData GetRenderData(FStringView Type = "") override;

};
