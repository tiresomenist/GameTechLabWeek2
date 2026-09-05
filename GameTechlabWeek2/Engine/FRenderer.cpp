#pragma once
#include "FRenderer.h"
#include "../Matrix.h"
#include "../FVertexSimple.h"
#include "Engine/Editor/Window/UEditorWindow.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

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

void FRenderer::Create(HWND hWindow, uint32 InWidth, uint32 InHeight)
{
    CreateDeviceAndSwapChain(hWindow);
    CreateFrameBuffer();
    CreateRasterizerState();
    CreateDepthStencilBuffer(static_cast<int32>(ViewportInfo.Width), static_cast<int32>(ViewportInfo.Height));

    // @TEST >>
    GenerateSphere(1.0f, 30, 30, SphereVertices, SphereIndices);
    CreateShader();
    CreateConstantBuffer();
    const UINT vertexByteWidth = static_cast<UINT>(SphereVertices.size() * sizeof(FVertexTest));
    SphereVertexBuffer = CreateVertexBuffer(SphereVertices.data(), vertexByteWidth);
    const UINT indexByteWidth = static_cast<UINT>(SphereIndices.size() * sizeof(uint32_t));
    SphereIndexBuffer = CreateIndexBuffer(SphereIndices.data(), indexByteWidth);
    // @TEST <<


    //////////////////////////
    /// 임시 테스트 코드    //
    //////////////////////////

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hWindow);
    ImGui_ImplDX11_Init(Device, DeviceContext);

    //////////////////////////
    /// 임시 테스트 코드    //
    //////////////////////////
}

void FRenderer::CreateDeviceAndSwapChain(HWND hWindow)
{
    // 지원하는 Direct3D 기능 레벨을 정의
    D3D_FEATURE_LEVEL featurelevels[] = { D3D_FEATURE_LEVEL_11_0 };

    // 스왑 체인 설정 구조체 초기화
    DXGI_SWAP_CHAIN_DESC swapchaindesc = {};
    swapchaindesc.BufferDesc.Width = 0;                             // 창 크기에 맞게 자동으로 설정
    swapchaindesc.BufferDesc.Height = 0;                            // 창 크기에 맞게 자동으로 설정
    swapchaindesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;   // 색상 포맷
    swapchaindesc.SampleDesc.Count = 1;                             // 멀티 샘플링 비활성화
    swapchaindesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;    // 렌더 타겟으로 사용
    swapchaindesc.BufferCount = 2;                                  // 더블 버퍼링
    swapchaindesc.OutputWindow = hWindow;                           // 렌더링할 창 핸들
    swapchaindesc.Windowed = TRUE;                                  // 창 모드
    swapchaindesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;       // 스왑 방식

    // Direct3D 장치와 스왑 체인을 생성
    D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,
        featurelevels, ARRAYSIZE(featurelevels), D3D11_SDK_VERSION,
        &swapchaindesc, &SwapChain, &Device, nullptr, &DeviceContext);

    // 생성된 스왑 체인의 정보 가져오기
    SwapChain->GetDesc(&swapchaindesc);

    // 뷰포트 정보 설정
    ViewportInfo = { 0.0f, 0.0f, (float)swapchaindesc.BufferDesc.Width, (float)swapchaindesc.BufferDesc.Height, 0.0f, 1.0f };
}

void FRenderer::ReleaseDeviceAndSwapChain()
{
    if (DeviceContext)
    {
        DeviceContext->Flush();
    }

    if (SwapChain)
    {
        SwapChain->Release();
        SwapChain = nullptr;
    }

    if (Device)
    {
        Device->Release();
        Device = nullptr;
    }

    if (DeviceContext)
    {
        DeviceContext->Release();
        DeviceContext = nullptr;
    }
}

void FRenderer::CreateFrameBuffer()
{
    // 스왑 체인으로부터 백 버퍼 텍스처 가져오기
    SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);

    // 렌더 타겟 뷰 생성
    D3D11_RENDER_TARGET_VIEW_DESC framebufferRTVdesc = {};
    framebufferRTVdesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;        // 색상 포맷
    framebufferRTVdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;   // 2D 텍스처

    Device->CreateRenderTargetView(FrameBuffer, &framebufferRTVdesc, &FrameBufferRTV);
}

void FRenderer::ReleaseFrameBuffer()
{
    if (FrameBuffer)
    {
        FrameBuffer->Release();
        FrameBuffer = nullptr;
    }

    if (FrameBufferRTV)
    {
        FrameBufferRTV->Release();
        FrameBufferRTV = nullptr;
    }
}

void FRenderer::CreateRasterizerState()
{
    D3D11_RASTERIZER_DESC rasterizerdesc = {};
    rasterizerdesc.FillMode = D3D11_FILL_SOLID; // 채우기 모드
    rasterizerdesc.CullMode = D3D11_CULL_BACK;  // 백 페이스 컬링

    Device->CreateRasterizerState(&rasterizerdesc, &RasterizerState);
}

void FRenderer::ReleaseRasterizerState()
{
    if (RasterizerState)
    {
        RasterizerState->Release();
        RasterizerState = nullptr;
    }
}

bool FRenderer::CreateDepthStencilBuffer(int32 InWidth, int32 inHeight)
{
    HRESULT hr;

    D3D11_TEXTURE2D_DESC DepthStencilDesc = {};
    DepthStencilDesc.Width = InWidth;
    DepthStencilDesc.Height = inHeight;
    DepthStencilDesc.MipLevels = 1;
    DepthStencilDesc.ArraySize = 1;
    DepthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;    // 24비트 깊이(Depth) + 8비트 스텐실(Stencil)
    DepthStencilDesc.SampleDesc.Count = 1;                      // MSAA - 스왑체인 생성 시의 SampleDesc
    DepthStencilDesc.SampleDesc.Quality = 0;
    DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    DepthStencilDesc.CPUAccessFlags = 0;
    DepthStencilDesc.MiscFlags = 0;

    // 텍스처 리소스 생성
    hr = Device->CreateTexture2D(&DepthStencilDesc, nullptr, &DepthStencilBuffer);
    if (FAILED(hr))
    {
        return false;
    }

    D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc = {};
    DSVDesc.Format = DepthStencilDesc.Format;
    DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    DSVDesc.Texture2D.MipSlice = 0;

    // 깊이/스텐실 뷰 생성
    hr = Device->CreateDepthStencilView(DepthStencilBuffer, &DSVDesc, &DepthStencilView);
    if (FAILED(hr))
    {
        return false;
    }

    return true;
}

void FRenderer::ReleaseDepthStencilBuffer()
{
    if (DepthStencilBuffer)
    {
        DepthStencilBuffer->Release();
        DepthStencilBuffer = nullptr;
    }
    if (DepthStencilView)
    {
        DepthStencilView->Release();
        DepthStencilView = nullptr;
    }
}

void FRenderer::Shutdown()
{
    ReleaseVertexBuffer(SphereVertexBuffer);
    SphereVertexBuffer = nullptr;
    if (SphereIndexBuffer)
    {
        SphereIndexBuffer->Release();
        SphereIndexBuffer = nullptr;
    }
    ReleaseConstantBuffer();
    ReleaseShader();
    ReleaseRasterizerState();

    // 테스트 코드
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    // 테스트 코드

    // 렌더 타겟을 초기화
    DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

    ReleaseDepthStencilBuffer();
    ReleaseFrameBuffer();
    ReleaseDeviceAndSwapChain();
}

void FRenderer::SwapBuffer()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    SwapChain->Present(1, 0); // 1: VSync 활성화
}

void FRenderer::CreateShader()
{
    ID3DBlob* vertexshaderCSO;
    ID3DBlob* pixelshaderCSO;

    D3DCompileFromFile(L"GameTechlabWeek2/ShaderW0.hlsl", nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &vertexshaderCSO, nullptr);

    Device->CreateVertexShader(vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), nullptr, &SimpleVertexShader);

    D3DCompileFromFile(L"GameTechlabWeek2/ShaderW0.hlsl", nullptr, nullptr, "mainPS", "ps_5_0", 0, 0, &pixelshaderCSO, nullptr);

    Device->CreatePixelShader(pixelshaderCSO->GetBufferPointer(), pixelshaderCSO->GetBufferSize(), nullptr, &SimplePixelShader);

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    Device->CreateInputLayout(layout, ARRAYSIZE(layout), vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), &SimpleInputLayout);

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
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    DeviceContext->ClearRenderTargetView(FrameBufferRTV, ClearColor);
    DeviceContext->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    DeviceContext->RSSetViewports(1, &ViewportInfo);
    DeviceContext->RSSetState(RasterizerState);

    DeviceContext->OMSetRenderTargets(1, &FrameBufferRTV, DepthStencilView);
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

    Device->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, &vertexBuffer);

    return vertexBuffer;
}

ID3D11Buffer* FRenderer::CreateVertexBuffer(FVertexTest* vertices, UINT byteWidth)
{
    D3D11_BUFFER_DESC vertexbufferdesc = {};
    vertexbufferdesc.ByteWidth = byteWidth;
    vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE; // will never be updated
    vertexbufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexbufferSRD = { vertices };

    ID3D11Buffer* vertexBuffer;

    Device->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, &vertexBuffer);

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

    Device->CreateBuffer(&constantbufferdesc, nullptr, &ConstantBuffer);
}

void FRenderer::ReleaseConstantBuffer()
{
    if (ConstantBuffer)
    {
        ConstantBuffer->Release();
        ConstantBuffer = nullptr;
    }
}

void FRenderer::BeginFrame()
{
    Prepare();
    PrepareShader();
}

void FRenderer::EndFrame()
{
    SwapBuffer();
}

// @TEST >>
//void FRenderer::Render(UScene* Scene)
//{
//    //BeginFrame();
//
//    UCameraComponent* Camera = Scene->GetCamera();
//    FMatrix ViewProjMatrix = Camera->GetViewMatrix() * Camera->GetProjectionMatrix();
//
//    for (UPrimitiveComponent* Prim : Scene->GetPrimitiveComponents())
//    {
//        FPrimitiveRenderData Data = Prim->GetRenderData();
//
//        FMatrix MVP = (*Data.WorldMatrix) * ViewProjMatrix;
//
//        UpdateConstantBuffer(MVP);
//        RenderPrimitive(Data);
//    }
//
//    //EndFrame();
//}

void FRenderer::Render(UScene* Scene)
{
}

void FRenderer::RenderUI(TArray<UEditorWindow*>& WindowArray)
{
    for (auto item : WindowArray)
    {
        item->UpdateEditorWindow();
    }

    ImGui::ShowDemoWindow();
}

// @TEST <<

ID3D11Buffer* FRenderer::CreateIndexBuffer(uint32_t* indices, UINT byteWidth)
{
    ID3D11Buffer* indexBuffer = nullptr;

    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = byteWidth;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;  // 인덱스 버퍼로 사용
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = indices;

    HRESULT hr = Device->CreateBuffer(&bd, &initData, &indexBuffer);
    if (FAILED(hr))
    {
        return nullptr;
    }

    return indexBuffer;
}

void FRenderer::Render()
{
    //BeginFrame();

    XMMATRIX View = XMMatrixLookAtLH({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
    const float AspectRatio = ViewportInfo.Width / ViewportInfo.Height;
    XMMATRIX Proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, AspectRatio, 0.1f, 100.0f);
    XMMATRIX WorldMat = XMMatrixIdentity();
    XMMATRIX MVP = WorldMat * View * Proj;

    FPrimitiveRenderData Data{};
    Data.VertexBuffer = SphereVertexBuffer;
    Data.IndexBuffer = SphereIndexBuffer;
    Data.IndexCount = static_cast<UINT>(SphereIndices.size());
    Data.Stride = sizeof(FVertexTest);
    Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    UpdateConstantBuffer(MVP);
    RenderPrimitive(Data);

    //EndFrame();
}

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
        FConstants* constants = (FConstants*)constantbufferMSR.pData;
        constants->MVP = MVP.Transpose();
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
