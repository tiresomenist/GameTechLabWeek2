#pragma once

#include "Engine/Editor/FEditor.h"
#include "Engine/Renderer/FPrimitiveRenderData.h"
#include "Engine/Object/UObject.h"

class UGrid : public UObject
{
    UCLASS(UGrid, "Grid", UObject)

private:
    FEditor* Editor = nullptr;

public:
    void Initialize(FEditor* InEditor);

    virtual TArray<FPrimitiveRenderData> GetRenderData();
};