#include "../Core.h"
#include "UWorldAxisGizmo.h"
#include "FVertexSimple.h"

void UWorldAxisGizmo::Create(FRenderer& Renderer)
{
    Release();
    // Temporary world axes: origin to +3 world units along each axis.
    FVertexSimple Vertices[] = {
        {0, 0, 0, 1, 0, 0, 1}, {2000, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 1, 0, 1}, {0, 2000, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 1, 1}, {0, 0, 2000, 0, 0, 1, 1}
    };
    D3D11_BUFFER_DESC Desc = {};
    Desc.ByteWidth = sizeof(Vertices);
    Desc.Usage = D3D11_USAGE_IMMUTABLE;
    Desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA Data = {};
    Data.pSysMem = Vertices;
    if (SUCCEEDED(Renderer.D3DDevice->CreateBuffer(&Desc, &Data, &vertexBuffer)))
        VertexCount = 6;
}

