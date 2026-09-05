#pragma once

#include "Container/FString.h"
#include "Engine/Object/USceneComponent.h"
#include "Engine/Renderer/FPrimitiveRenderData.h"

class UPrimitiveComponent : public USceneComponent
{

    UCLASS(UPrimitiveComponent, "PrimitiveComponent", USceneComponent)

public:

    // 렌더러에게 전달할 렌더 정보
    virtual FPrimitiveRenderData GetRenderData(FStringView Type = "");

};

