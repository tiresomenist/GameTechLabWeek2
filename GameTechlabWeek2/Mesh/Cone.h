#pragma once

#include <cmath>
#include "Engine/Renderer/FVertexSimple.h"

namespace Mesh
{
    inline constexpr unsigned int ConeSegmentCount = 32;
    inline FVertexSimple Cone[ConeSegmentCount * 6]{};

    inline const bool ConeInitialized = []
    {
        constexpr float Pi = 3.14159265358979323846f;
        constexpr float Radius = 0.5f;
        constexpr float HalfHeight = 0.5f;

        const auto MakeVertex = [](float x, float y, float z)
        {
            return FVertexSimple{ x, y, z, x + 0.5f, y + 0.5f, z + 0.5f, 1.0f };
        };

        const FVertexSimple apex = MakeVertex(0.0f, HalfHeight, 0.0f);
        const FVertexSimple baseCenter = MakeVertex(0.0f, -HalfHeight, 0.0f);
        unsigned int vertex = 0;

        for (unsigned int segment = 0; segment < ConeSegmentCount; ++segment)
        {
            const float angle0 = 2.0f * Pi * segment / ConeSegmentCount;
            const float angle1 = 2.0f * Pi * (segment + 1) / ConeSegmentCount;
            const FVertexSimple bottom0 = MakeVertex(
                Radius * std::cos(angle0), -HalfHeight, Radius * std::sin(angle0));
            const FVertexSimple bottom1 = MakeVertex(
                Radius * std::cos(angle1), -HalfHeight, Radius * std::sin(angle1));

            // Side
            Cone[vertex++] = bottom0;
            Cone[vertex++] = apex;
            Cone[vertex++] = bottom1;

            // Bottom cap (Y-)
            Cone[vertex++] = baseCenter;
            Cone[vertex++] = bottom0;
            Cone[vertex++] = bottom1;
        }
        return true;
    }();
}
