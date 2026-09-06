#include "UGizmo.h"
#include "FVertexSimple.h"
#include "Engine/Object/UObject.h"

void UGizmo::Create(FRenderer& renderer)
{
}

UGizmo::~UGizmo()
{
    Release();
}

void UGizmo::Render(FRenderer& Renderer)
{
    if (!bVisible) return;
    if (!vertexBuffer) Create(Renderer);
    if (!vertexBuffer || VertexCount == 0) return;

    const UINT Stride = sizeof(FVertexSimple);
    const UINT Offset = 0;
    Renderer.DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &Stride, &Offset);
    Renderer.DeviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0);
    Renderer.DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    Renderer.DeviceContext->Draw(VertexCount, 0);
}

void UGizmo::Release()
{
    if (vertexBuffer) vertexBuffer->Release();
    vertexBuffer = nullptr;
    VertexCount = 0;
}

void UGizmo::SetVisible(bool InVisible)
{
    bVisible = InVisible;
}

bool UGizmo::IsVisible()
{
    return bVisible;
}
