#pragma once
#include "FRenderer.h"
#include "GDevice.h"
#include "../Matrix.h"
#include "../FVertexSimple.h"
#include "Object/Primitive/UPrimitiveComponent.h"
#include "Object/UScene.h"

void GenerateSphere(float Radius, int Slices, int Stacks, std::vector<FVertexTest>& OutVertices, std::vector<uint32_t>& OutIndices)
{
    OutVertices.clear();
    OutIndices.clear();

    const float PI = 3.141592654f;

    // 1. 정점(Vertex) 데이터 생성
    for (int i = 0; i <= Stacks; ++i)
    {
        float V = (float)i / (float)Stacks;
        float phi = V * PI; // 0 ~ PI (위에서 아래로)

        for (int j = 0; j <= Slices; ++j)
        {
            float U = (float)j / (float)Slices;
            float theta = U * 2.0f * PI; // 0 ~ 2PI (한 바퀴)

            // 구면 좌표계를 직교 좌표계로 변환 (Left-Handed 기준)
            float x = Radius * sinf(phi) * cosf(theta);
            float y = Radius * cosf(phi);
            float z = Radius * sinf(phi) * sinf(theta);

            FVertexTest vertex;
            vertex.x = x; vertex.y = y; vertex.z = z;

            // 법선(Normal) 벡터는 위치 벡터를 정규화한 것과 동일 (원점 중심이므로)
            vertex.nx = x / Radius;
            vertex.ny = y / Radius;
            vertex.nz = z / Radius;

            vertex.u = U;
            vertex.v = V;

            OutVertices.push_back(vertex);
        }
    }

    // 2. 인덱스(Index) 데이터 생성
    for (int i = 0; i < Stacks; ++i)
    {
        for (int j = 0; j < Slices; ++j)
        {
            // 현재 사각형을 구성하는 4개의 정점 인덱스 계산
            uint32_t p0 = (i * (Slices + 1)) + j;
            uint32_t p1 = (i * (Slices + 1)) + (j + 1);
            uint32_t p2 = ((i + 1) * (Slices + 1)) + j;
            uint32_t p3 = ((i + 1) * (Slices + 1)) + (j + 1);

            // 첫 번째 삼각형 (시계 방향 - D3D 기본 전면)
            OutIndices.push_back(p0);
            OutIndices.push_back(p1);
            OutIndices.push_back(p2);

            // 두 번째 삼각형
            OutIndices.push_back(p2);
            OutIndices.push_back(p1);
            OutIndices.push_back(p3);
        }
    }
}

void FRenderer::Create(GDevice* InDevice)
{
    Device = InDevice;
    DeviceContext = InDevice->GetContext();
    D3DDevice = InDevice->GetDevice();
    CreateRasterizerState();
    CreateShader();
    CreateConstantBuffer();

    // @TEST >>
    //GenerateSphere(1.0f, 30, 30, SphereVertices, SphereIndices);
    //const UINT vertexByteWidth = static_cast<UINT>(SphereVertices.size() * sizeof(FVertexTest));
    //SphereVertexBuffer = CreateVertexBuffer(SphereVertices.data(), vertexByteWidth);
    //const UINT indexByteWidth = static_cast<UINT>(SphereIndices.size() * sizeof(uint32_t));
    //SphereIndexBuffer = CreateIndexBuffer(SphereIndices.data(), indexByteWidth);
    // @TEST <<
}

void FRenderer::Shutdown()
{
    //ReleaseVertexBuffer(SphereVertexBuffer);
    //SphereVertexBuffer = nullptr;
    //if (SphereIndexBuffer)
    //{
    //    SphereIndexBuffer->Release();
    //    SphereIndexBuffer = nullptr;
    //}
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
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    D3DDevice->CreateInputLayout(layout, ARRAYSIZE(layout), vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), &SimpleInputLayout);

    Stride = sizeof(FVertexTest);

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

//ID3D11Buffer* FRenderer::CreateVertexBuffer(FVertexTest* vertices, UINT byteWidth)
//{
//    D3D11_BUFFER_DESC vertexbufferdesc = {};
//    vertexbufferdesc.ByteWidth = byteWidth;
//    vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE; // will never be updated
//    vertexbufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//
//    D3D11_SUBRESOURCE_DATA vertexbufferSRD = { vertices };
//
//    ID3D11Buffer* vertexBuffer;
//
//    D3DDevice->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, &vertexBuffer);
//
//    return vertexBuffer;
//}

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
    //BeginFrame();

    //UCameraComponent* Camera = Scene->GetCamera();
    //FMatrix ViewProjMatrix = Camera->GetViewMatrix() * Camera->GetProjectionMatrix();
    const float AspectRatio = ViewportInfo.Width / ViewportInfo.Height;
    XMMATRIX View = XMMatrixLookAtLH({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
    XMMATRIX Proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, AspectRatio, 0.1f, 100.0f);
    XMMATRIX ViewProjMatrix = View * Proj;

    for (UPrimitiveComponent* Prim : Scene->GetPrimitiveComponents())
    {
        FPrimitiveRenderData Data = Prim->GetRenderData();

        //FMatrix MVP = (*Data.WorldMatrix) * ViewProjMatrix;
        XMMATRIX temp = XMMATRIX(&(Data.WorldMatrix->M[0][0]));
        XMMATRIX MVP = temp * ViewProjMatrix;

        UpdateConstantBuffer(MVP);
        RenderPrimitive(Data);
    }

    //EndFrame();
}

//void FRenderer::Render()
//{
//    BeginFrame();
//
//    XMMATRIX View = XMMatrixLookAtLH({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
//    const float AspectRatio = ViewportInfo.Width / ViewportInfo.Height;
//    XMMATRIX Proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, AspectRatio, 0.1f, 100.0f);
//    XMMATRIX WorldMat = XMMatrixIdentity();
//    XMMATRIX MVP = WorldMat * View * Proj;
//
//    FPrimitiveRenderData Data{};
//    Data.VertexBuffer = SphereVertexBuffer;
//    Data.IndexBuffer = SphereIndexBuffer;
//    Data.IndexCount = static_cast<UINT>(SphereIndices.size());
//    Data.VertexStride = sizeof(FVertexTest);
//    Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//
//    UpdateConstantBuffer(MVP);
//    RenderPrimitive(Data);
//
//    EndFrame();
//}

void FRenderer::UpdateConstantBuffer(const XMMATRIX& MVP)
{
    if (ConstantBuffer)
    {
        D3D11_MAPPED_SUBRESOURCE constantbufferMSR;

        DeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &constantbufferMSR);
        FConstants* constants = (FConstants*)constantbufferMSR.pData;
        XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&constants->MVP.M[0][0]), MVP);
        DeviceContext->Unmap(ConstantBuffer, 0);
    }
}

void FRenderer::UpdateConstantBuffer(const FMatrix& MVP)
{
    if (ConstantBuffer)
    {
        D3D11_MAPPED_SUBRESOURCE constantbufferMSR;

        DeviceContext->Map(ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &constantbufferMSR);
        //FConstants* constants = (FConstants*)constantbufferMSR.pData;
        //constants->MVP = MVP.Transpose(); 그냥 Shader에서 row_major 키워드 넣기로 함
        DeviceContext->Unmap(ConstantBuffer, 0);
    }
}

void FRenderer::RenderPrimitive(const FPrimitiveRenderData& Data)
{
    DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);

    // 지오메트리 바인딩
    UINT Offset = 0;
    DeviceContext->IASetVertexBuffers(0, 1, &Data.VertexBuffer, &Data.VertexStride, &Offset);
    DeviceContext->IASetIndexBuffer(Data.IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    DeviceContext->IASetPrimitiveTopology(Data.Topology);

    // 머티리얼(셰이더/텍스처) 바인딩
    //BindMaterial(Data.Material);

    // Draw
    DeviceContext->DrawIndexed(Data.IndexCount, 0, 0);
}
