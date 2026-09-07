#include "GPrimitive.h"

#include "Engine/GDevice.h"
#include "Engine/Primitive/FMeshResource.h"
#include "Engine/Renderer/FVertexSimple.h"

#include "Engine/Core.h"
#include "Container/TArray.h"

#include "Mesh/Cube.h"
#include "Mesh/Sphere.h"
#include "Mesh/Triangle.h"
#include "Mesh/Cylinder.h"
#include "Mesh/Cone.h"
#include "Mesh/Plane.h"
#include "Mesh/Line.h"


template <uint32 N>
void SetFMeshResource(GDevice* Device, FMeshResource& Resource, FVertexSimple (&Vertex)[N])
{
    TArray<uint32> Indices;

    Resource.VertexCount = sizeof(Vertex) / sizeof(Vertex[0]);

    Indices.SetNum(Resource.VertexCount);
    for (uint32 i = 0; i < Resource.VertexCount; ++i)
    {
        Indices[i] = i;
    }

    Resource.VertexBuffer = Device->CreateVertexBuffer(Vertex, sizeof(FVertexSimple) * Resource.VertexCount);
    Resource.IndexBuffer = Device->CreateIndexBuffer(Indices.GetData(), sizeof(uint32) * Resource.VertexCount);
    Resource.VertexCount = Resource.VertexCount;
    Resource.IndexCount = Resource.VertexCount;
    Resource.Stride = sizeof(FVertexSimple);
}

void GPrimitive::Initialize(GDevice* Device)
{
    SetFMeshResource(Device, Cube, Mesh::Cube);
    SetFMeshResource(Device, Sphere, Mesh::Sphere);
    SetFMeshResource(Device, Plane, Mesh::Plane);
    SetFMeshResource(Device, Cylinder, Mesh::Cylinder);
    SetFMeshResource(Device, Cone, Mesh::Cone);
    SetFMeshResource(Device, Line, Mesh::Line);

    
}