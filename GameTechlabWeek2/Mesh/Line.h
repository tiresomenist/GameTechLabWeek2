#pragma once
#pragma once

#include "Engine/Renderer/FVertexSimple.h"

// 삼각형을 하드 코딩
namespace Mesh
{
    inline FVertexSimple Line[] =
    {
        { -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f },
        {  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f },
    };
};