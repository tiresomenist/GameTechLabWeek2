#pragma once

#include "Engine/Renderer/FVertexSimple.h"

// Unit plane on XZ, centered at the origin and facing Y+.
inline FVertexSimple plane_vertices[] =
{
    { -0.5f, 0.0f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f },
    { -0.5f, 0.0f,  0.5f, 0.0f, 0.5f, 1.0f, 1.0f },
    {  0.5f, 0.0f, -0.5f, 1.0f, 0.5f, 0.0f, 1.0f },
    { -0.5f, 0.0f,  0.5f, 0.0f, 0.5f, 1.0f, 1.0f },
    {  0.5f, 0.0f,  0.5f, 1.0f, 0.5f, 1.0f, 1.0f },
    {  0.5f, 0.0f, -0.5f, 1.0f, 0.5f, 0.0f, 1.0f },
};