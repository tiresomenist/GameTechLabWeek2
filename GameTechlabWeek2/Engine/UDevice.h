#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include "Core.h"

struct FVertexSimple;
struct FVertexTest;

// Device 생성 → Renderer/ResourceManager 생성 → (역순으로) Renderer/ResourceManager 소멸 → Device 소멸

class UDevice
{
public:
    void Initialize(HWND hWnd, uint32 Width, uint32 Height);
    void Release();
    void OnResize(uint32 Width, uint32 Height);

    ID3D11Device* GetDevice() const { return Device; }
    ID3D11DeviceContext* GetContext() const { return DeviceContext; }

    void CreateDeviceAndSwapChain(HWND hWindow);    // Direct3D 장치 및 스왑 체인을 생성하는 함수
    void ReleaseDeviceAndSwapChain();               // Direct3D 장치 및 스왑 체인을 해제하는 함수
    void CreateFrameBuffer();                       // 프레임 버퍼를 생성하는 함수
    void ReleaseFrameBuffer();                      // 프레임 버퍼를 해제하는 함수
    void CreateRasterizerState();                   // 래스터라이저 상태를 생성하는 함수
    void ReleaseRasterizerState();                  // 래스터라이저 상태를 해제하는 함수
    bool CreateDepthStencilBuffer(int32 InWidth, int32 InHeight); // 깊이 스텐실 버퍼를 생성하는 함수
    void ReleaseDepthStencilBuffer();               // 깊이 스텐실 버퍼를 해제하는 함수

    ID3D11Buffer* CreateVertexBuffer(FVertexSimple* vertices, UINT byteWidth);
    ID3D11Buffer* CreateVertexBuffer(FVertexTest* vertices, UINT byteWidth);
    void ReleaseVertexBuffer(ID3D11Buffer* vertexBuffer);
    ID3D11Buffer* CreateIndexBuffer(uint32_t* indices, UINT byteWidth);

    void SwapBuffer();

    ID3D11DeviceContext* GetContext() const { return DeviceContext; };
    ID3D11RenderTargetView* GetFrameBufferRTV() const { return FrameBufferRTV; };
    ID3D11DepthStencilView* GetDepthStencilView() const { return DepthStencilView; };

private:
    ID3D11Device* Device;
    ID3D11DeviceContext* DeviceContext;

    IDXGISwapChain* SwapChain;

    ID3D11Texture2D* FrameBuffer;
    ID3D11RenderTargetView* FrameBufferRTV;

    ID3D11Texture2D* DepthStencilBuffer;
    ID3D11DepthStencilView* DepthStencilView;

    D3D11_VIEWPORT ViewportInfo;
};
