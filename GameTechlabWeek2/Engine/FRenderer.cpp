#pragma once
#include "FRenderer.h"
#include "Matrix.h"
#include "FVertexSimple.h"
#include "Engine/GDevice.h"
#include "Engine/Scene/UScene.h"
#include "Engine/Renderer/RenderUtil.h"
#include "Engine/Core.h"
#include "Engine/Object/UCameraComponent.h"

#include <format>

void FRenderer::Create(GDevice* InDevice)
{
    Device = InDevice;
    DeviceContext = InDevice->GetContext();
    D3DDevice = InDevice->GetDevice();
    ViewportInfo = InDevice->GetViewport();
    CreateRasterizerState();
    CreateShader();
    CreateConstantBuffer();
}

void FRenderer::Shutdown()
{
    ReleaseConstantBuffer();
    ReleaseShader();
    ReleaseRasterizerState();

    // 렌더 타겟을 초기화
    DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
}

void FRenderer::CreateShader()
{
    ID3DBlob* vertexshaderCSO;
    ID3DBlob* pixelshaderCSO;

    D3DCompileFromFile(L"GameTechlabWeek2/ShaderW0.hlsl", nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &vertexshaderCSO, nullptr);

    D3DDevice->CreateVertexShader(vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), nullptr, &SimpleVertexShader);

    D3DCompileFromFile(L"GameTechlabWeek2/ShaderW0.hlsl", nullptr, nullptr, "mainPS", "ps_5_0", 0, 0, &pixelshaderCSO, nullptr);

    D3DDevice->CreatePixelShader(pixelshaderCSO->GetBufferPointer(), pixelshaderCSO->GetBufferSize(), nullptr, &SimplePixelShader);

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    D3DDevice->CreateInputLayout(layout, ARRAYSIZE(layout), vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), &SimpleInputLayout);

    Stride = sizeof(FVertexSimple);

    vertexshaderCSO->Release();
    pixelshaderCSO->Release();
}

void FRenderer::ReleaseShader()
{
    if (SimpleInputLayout)
    {
        SimpleInputLayout->Release();
        SimpleInputLayout = nullptr;
    }

    if (SimplePixelShader)
    {
        SimplePixelShader->Release();
        SimplePixelShader = nullptr;
    }

    if (SimpleVertexShader)
    {
        SimpleVertexShader->Release();
        SimpleVertexShader = nullptr;
    }
}

void FRenderer::Prepare()
{
    ID3D11RenderTargetView* RTV = Device->GetFrameBufferRTV();
    ID3D11DepthStencilView* DSV = Device->GetDepthStencilView();

    DeviceContext->ClearRenderTargetView(RTV, ClearColor);
    DeviceContext->ClearDepthStencilView(DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    DeviceContext->RSSetViewports(1, &ViewportInfo);
    DeviceContext->RSSetState(RasterizerState);

    DeviceContext->OMSetRenderTargets(1, &RTV, DSV);
    DeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void FRenderer::PrepareShader()
{
    DeviceContext->VSSetShader(SimpleVertexShader, nullptr, 0);
    DeviceContext->PSSetShader(SimplePixelShader, nullptr, 0);
    DeviceContext->IASetInputLayout(SimpleInputLayout);

    // 상수 버퍼 사용시 호출
    // 버텍스 쉐이더에 상수 버퍼를 설정합니다.
    if (ConstantBuffer)
    {
        DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);
    }
}

ID3D11Buffer* FRenderer::CreateVertexBuffer(FVertexSimple* vertices, UINT byteWidth)
{
    D3D11_BUFFER_DESC vertexbufferdesc = {};
    vertexbufferdesc.ByteWidth = byteWidth;
    vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertexbufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexbufferSRD = { vertices };

    ID3D11Buffer* vertexBuffer;

    D3DDevice->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, &vertexBuffer);

    return vertexBuffer;
}

void FRenderer::ReleaseVertexBuffer(ID3D11Buffer* vertexBuffer)
{
    if (vertexBuffer)
    {
        vertexBuffer->Release();
    }
}

void FRenderer::CreateConstantBuffer()
{
    D3D11_BUFFER_DESC constantbufferdesc = {};
    constantbufferdesc.ByteWidth = sizeof(FConstants) + 0xf & 0xfffffff0; // ensure constant buffer size is multiple of 16 bytes
    constantbufferdesc.Usage = D3D11_USAGE_DYNAMIC; // will be updated from CPU every frame
    constantbufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    constantbufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3DDevice->CreateBuffer(&constantbufferdesc, nullptr, &ConstantBuffer);
}

void FRenderer::ReleaseConstantBuffer()
{
    if (ConstantBuffer)
    {
        ConstantBuffer->Release();
        ConstantBuffer = nullptr;
    }
}

void FRenderer::CreateRasterizerState()
{
    D3D11_RASTERIZER_DESC rasterizerdesc = {};
    rasterizerdesc.FillMode = D3D11_FILL_SOLID; // 채우기 모드
    rasterizerdesc.CullMode = D3D11_CULL_BACK;  // 백 페이스 컬링
    rasterizerdesc.FrontCounterClockwise = TRUE;

    D3DDevice->CreateRasterizerState(&rasterizerdesc, &RasterizerState);
}

void FRenderer::ReleaseRasterizerState()
{
    if (RasterizerState)
    {
        RasterizerState->Release();
        RasterizerState = nullptr;
    }
}

void FRenderer::BeginFrame()
{
    Prepare();
    PrepareShader();
}

void FRenderer::EndFrame()
{
}

void FRenderer::Render(UScene* Scene)
{
    BeginFrame();

    UCameraComponent* Camera = Scene->GetMainCamera();
    FMatrix ViewProjMatrix = Camera->GetViewMatrix() * Camera->GetProjectionMatrix();
    TArray<FPrimitiveRenderData> RenderList = RenderUtil::GetRenderList(Scene);
    static float Angle = 0.0f;
    Angle += 0.11f;
    FMatrix Rotation = FMatrix::MakeRotationYMatrix(Angle);
    for (auto& Item: RenderList)
    {
        FMatrix MVP = (*Item.WorldMatrix)* Rotation* ViewProjMatrix;
        UpdateConstantBuffer(MVP);
        RenderPrimitive(Item);
    }

    // Gizmo vertices are already in world space (identity world transform).
    UpdateConstantBuffer(ViewProjMatrix);
    Scene->RenderGizmos(*this);

    GDevice::GetInstance()->SwapBuffer();
    EndFrame();
}

void FRenderer::UpdateConstantBuffer(const FMatrix& MVP)
{
    if (ConstantBuffer)
    {
        D3D11_MAPPED_SUBRESOURCE constantbufferMSR;

        DeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &constantbufferMSR);
        FConstants* constants = (FConstants*)constantbufferMSR.pData;
        constants->MVP = MVP;//.Transpose(); 그냥 Shader에서 row_major 키워드 넣기로 함
        DeviceContext->Unmap(ConstantBuffer, 0);
    }
}

void FRenderer::RenderPrimitive(const FPrimitiveRenderData& Data)
{
    DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);

    // 지오메트리 바인딩
    UINT Offset = 0;
    DeviceContext->IASetVertexBuffers(0, 1, &Data.VertexBuffer, &Data.Stride, &Offset);
    DeviceContext->IASetIndexBuffer(Data.IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    DeviceContext->IASetPrimitiveTopology(Data.Topology);

    // 머티리얼(셰이더/텍스처) 바인딩
    //BindMaterial(Data.Material);

    // Draw
    DeviceContext->DrawIndexed(Data.IndexCount, 0, 0);
}
