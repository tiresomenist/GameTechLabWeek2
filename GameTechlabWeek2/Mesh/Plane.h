#pragma once

#include "Engine/Renderer/FVertexSimple.h"

namespace Mesh
{
    // Unit plane on XZ, centered at the origin and facing Y+.
    inline FVertexSimple Plane[] =
    {
        { -0.5f, 0.0f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f },
        { -0.5f, 0.0f,  0.5f, 0.0f, 0.5f, 1.0f, 1.0f },
        {  0.5f, 0.0f, -0.5f, 1.0f, 0.5f, 0.0f, 1.0f },
        { -0.5f, 0.0f,  0.5f, 0.0f, 0.5f, 1.0f, 1.0f },
        {  0.5f, 0.0f,  0.5f, 1.0f, 0.5f, 1.0f, 1.0f },
        {  0.5f, 0.0f, -0.5f, 1.0f, 0.5f, 0.0f, 1.0f },
    };
}
