#pragma once

#include "Container/TArray.h"

class UScene;
struct FPrimitiveRenderData;

namespace RenderUtil
{
	TArray<FPrimitiveRenderData> GetRenderList(UScene* Scene);
};