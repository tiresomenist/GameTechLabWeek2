#pragma once
#include "FRenderer.h"
#include "Matrix.h"
#include "Engine/Renderer/FVertexSimple.h"
#include "Engine/Editor/Window/UEditorWindow.h"
#include "Engine/GDevice.h"
#include "Engine/Scene/UScene.h"
#include "Engine/Editor/FEditor.h"
#include "Engine/Gizmo/UGizmo.h"
#include "Engine/Renderer/RenderUtil.h"
#include "Engine/Core.h"
#include "Engine/Object/UCameraComponent.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include <format>

void FRenderer::Create(HWND HWnd, GDevice* InDevice)
{
    Device = InDevice;
    DeviceContext = InDevice->GetContext();
    D3DDevice = InDevice->GetDevice();
    ViewportInfo = InDevice->GetViewport();
    CreateRasterizerState();
    CreateShaders();
    CreateConstantBuffer();
    CreateAlphaBlendState();

    // @TEST >>
    //GenerateSphere(1.0f, 30, 30, SphereVertices, SphereIndices);
    //const UINT vertexByteWidth = static_cast<UINT>(SphereVertices.size() * sizeof(FVertexTest));
    //SphereVertexBuffer = CreateVertexBuffer(SphereVertices.data(), vertexByteWidth);
    //const UINT indexByteWidth = static_cast<UINT>(SphereIndices.size() * sizeof(uint32_t));
    //SphereIndexBuffer = CreateIndexBuffer(SphereIndices.data(), indexByteWidth);
    // @TEST <<


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(HWnd);
    ImGui_ImplDX11_Init(D3DDevice, DeviceContext);
}

void FRenderer::Shutdown()
{
    ReleaseConstantBuffer();
    ReleaseShader();
    ReleaseRasterizerState();

    //TESTCODE//
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    ////////////

    // 렌더 타겟을 초기화
    DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
}

void FRenderer::CreateShaders()
{
    ID3DBlob* vertexshaderCSO;
    ID3DBlob* pixelshaderCSO;

    D3DCompileFromFile(L"GameTechlabWeek2/ShaderW0.hlsl", nullptr, nullptr, "mainVS", "vs_5_0", 0, 0, &vertexshaderCSO, nullptr);

    D3DDevice->CreateVertexShader(vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), nullptr, &SimpleVertexShader);

    D3DCompileFromFile(L"GameTechlabWeek2/ShaderW0.hlsl", nullptr, nullptr, "mainPS", "ps_5_0", 0, 0, &pixelshaderCSO, nullptr);

    D3DDevice->CreatePixelShader(pixelshaderCSO->GetBufferPointer(), pixelshaderCSO->GetBufferSize(), nullptr, &SimplePixelShader);

    D3DCompileFromFile(L"GameTechlabWeek2/ShaderW0.hlsl", nullptr, nullptr, "VS_Highlight", "vs_5_0", 0, 0, &vertexshaderCSO, nullptr);

    D3DDevice->CreateVertexShader(vertexshaderCSO->GetBufferPointer(), vertexshaderCSO->GetBufferSize(), nullptr, &HighlightVertexShader);

    D3DCompileFromFile(L"GameTechlabWeek2/ShaderW0.hlsl", nullptr, nullptr, "PS_Highlight", "ps_5_0", 0, 0, &pixelshaderCSO, nullptr);

    D3DDevice->CreatePixelShader(pixelshaderCSO->GetBufferPointer(), pixelshaderCSO->GetBufferSize(), nullptr, &HighlightPixelShader);

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

void FRenderer::PrepareRTVDSV()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    DeviceContext->ClearRenderTargetView(Device->GetFrameBufferRTV(), ClearColor);
    DeviceContext->ClearDepthStencilView(Device->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    ID3D11RenderTargetView* RTV = Device->GetFrameBufferRTV();
    ID3D11DepthStencilView* DSV = Device->GetDepthStencilView();

    DeviceContext->ClearRenderTargetView(RTV, ClearColor);
    DeviceContext->ClearDepthStencilView(DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    ViewportInfo = Device->GetViewport(); // 리사이징 된 현재 뷰포트 복사
    DeviceContext->RSSetViewports(1, &ViewportInfo);
    DeviceContext->RSSetState(DefaultRasterizerState);

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
    D3DDevice->CreateRasterizerState(&rasterizerdesc, &DefaultRasterizerState);

    D3D11_RASTERIZER_DESC rasterizerdescHighlight = {};
    rasterizerdescHighlight.FillMode = D3D11_FILL_SOLID; // 채우기 모드
    rasterizerdescHighlight.CullMode = D3D11_CULL_FRONT;  // 프론트 페이스 컬링
    D3DDevice->CreateRasterizerState(&rasterizerdescHighlight, &CullFrontRasterizerState);
}

void FRenderer::ReleaseRasterizerState()
{
    if (DefaultRasterizerState)
    {
        DefaultRasterizerState->Release();
        DefaultRasterizerState = nullptr;
    }
}

void FRenderer::CreateAlphaBlendState()
{
    D3D11_BLEND_DESC blendDesc = {};
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;

    // 0번째 렌더 타겟(우리의 메인 화면)에 대한 블렌딩 설정
    blendDesc.RenderTarget[0].BlendEnable = TRUE;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;       // 새로 그릴 픽셀의 알파값 비중
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;  // 이미 그려진 픽셀의 비중 (1 - SrcAlpha)
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;           // 두 색상을 더함

    // 알파 채널 자체를 섞는 공식 (보통 아래와 같이 고정)
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    // Device를 이용해 객체 생성
    D3DDevice->CreateBlendState(&blendDesc, &AlphaBlendState);
}

void FRenderer::ReleaseAlphaBlendState()
{

}

void FRenderer::BeginFrame()
{
    PrepareRTVDSV();
    PrepareShader();
}

void FRenderer::EndFrame()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    GDevice::GetInstance()->SwapBuffer();
}

void FRenderer::Render(FEditor* Editor, UScene* Scene)
{
    BeginFrame();

    UCameraComponent* Camera = Editor->GetEditorCamera();

    FMatrix ViewProjMatrix = Camera->GetViewMatrix() * Camera->GetProjectionMatrix();
    TArray<FPrimitiveRenderData> RenderList = RenderUtil::GetRenderList(Editor, Scene);
    static float Angle = 0.0f;
    Angle += 0.03f;
    FMatrix Rotation = FMatrix::MakeRotationZMatrix(Angle);
    Camera->SetAspectRatio(Device->GetViewport().Width / Device->GetViewport().Height); // 리사이징된 카메라 화면에 맞게 종횡비를 맞춥니다.
    for (auto& Item: RenderList)
    {
        FMatrix MVP = Rotation * (*Item.WorldMatrix) * ViewProjMatrix;
        UpdateConstantBuffer(MVP);
        if (Item.isSelected)
        {
            RenderHighlight(Item);
        }
        RenderPrimitive(Item);
    }

    // 2. Editor Window 렌더
    for (auto Item : Editor->GetWindows())
    {
        Item->Render();
    }

    // Gizmo vertices are already in world space (identity world transform).
    UpdateConstantBuffer(ViewProjMatrix);
    EndFrame();
}
////////////////

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
    DeviceContext->VSSetShader(SimpleVertexShader, nullptr, 0);
    DeviceContext->PSSetShader(SimplePixelShader, nullptr, 0);

    DeviceContext->RSSetState(DefaultRasterizerState);

    // Draw
    DeviceContext->DrawIndexed(Data.IndexCount, 0, 0);
}

void FRenderer::RenderHighlight(const FPrimitiveRenderData& Data)
{
    DeviceContext->VSSetConstantBuffers(0, 1, &ConstantBuffer);

    UINT Offset = 0;
    DeviceContext->IASetVertexBuffers(0, 1, &Data.VertexBuffer, &Data.Stride, &Offset);
    DeviceContext->IASetIndexBuffer(Data.IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    DeviceContext->IASetPrimitiveTopology(Data.Topology);

    DeviceContext->VSSetShader(HighlightVertexShader, nullptr, 0);
    DeviceContext->PSSetShader(HighlightPixelShader, nullptr, 0);

    DeviceContext->RSSetState(CullFrontRasterizerState);

    DeviceContext->DrawIndexed(Data.IndexCount, 0, 0);
}

void FRenderer::RenderGrid()
{
    // 알파 블렌딩 켜기 (OM: Output Merger 단계)
    float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    UINT sampleMask = 0xffffffff;

    DeviceContext->OMSetBlendState(AlphaBlendState, blendFactor, sampleMask);

    // DeviceContext->DrawIndexed(...);

    DeviceContext->OMSetBlendState(nullptr, blendFactor, sampleMask);
}
