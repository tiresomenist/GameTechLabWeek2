#pragma once

#include <cmath>
#include "Engine/Renderer/FVertexSimple.h"

namespace Mesh
{
    inline constexpr unsigned int CylinderSegmentCount = 32;
    inline FVertexSimple Cylinder[CylinderSegmentCount * 12]{};

    inline const bool CylinderInitialized = []
    {
        constexpr float Pi = 3.14159265358979323846f;
        constexpr float Radius = 0.5f;
        constexpr float HalfHeight = 0.5f;

        const auto MakeVertex = [](float x, float y, float z)
        {
            return FVertexSimple{ x, y, z, x + 0.5f, y + 0.5f, z + 0.5f, 1.0f };
        };

        unsigned int vertex = 0;
        for (unsigned int segment = 0; segment < CylinderSegmentCount; ++segment)
        {
            const float angle0 = 2.0f * Pi * segment / CylinderSegmentCount;
            const float angle1 = 2.0f * Pi * (segment + 1) / CylinderSegmentCount;
            const float x0 = Radius * std::cos(angle0);
            const float z0 = Radius * std::sin(angle0);
            const float x1 = Radius * std::cos(angle1);
            const float z1 = Radius * std::sin(angle1);

            const FVertexSimple bottom0 = MakeVertex(x0, -HalfHeight, z0);
            const FVertexSimple top0 = MakeVertex(x0, HalfHeight, z0);
            const FVertexSimple bottom1 = MakeVertex(x1, -HalfHeight, z1);
            const FVertexSimple top1 = MakeVertex(x1, HalfHeight, z1);

            // Side
            Cylinder[vertex++] = bottom0;
            Cylinder[vertex++] = top0;
            Cylinder[vertex++] = bottom1;
            Cylinder[vertex++] = top0;
            Cylinder[vertex++] = top1;
            Cylinder[vertex++] = bottom1;

            // Top cap (Y+)
            Cylinder[vertex++] = MakeVertex(0.0f, HalfHeight, 0.0f);
            Cylinder[vertex++] = top1;
            Cylinder[vertex++] = top0;

            // Bottom cap (Y-)
            Cylinder[vertex++] = MakeVertex(0.0f, -HalfHeight, 0.0f);
            Cylinder[vertex++] = bottom0;
            Cylinder[vertex++] = bottom1;
        }
        return true;
    }();
}
