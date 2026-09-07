#pragma once
#pragma once

#include "Engine/Renderer/FVertexSimple.h"

// 삼각형을 하드 코딩
namespace Mesh
{
    inline FVertexSimple Triangle[] =
    {
        {  0.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f }, // Top vertex (red)
        {  1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f }, // Bottom-right vertex (green)
        { -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f }, // Bottom-left vertex (blue)
    };
};