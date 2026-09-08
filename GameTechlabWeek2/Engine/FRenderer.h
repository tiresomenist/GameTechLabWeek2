#pragma once
#include <vector>
#include <directxmath.h>

// D3D11 librarys
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// D3D11 headers
#include <d3d11.h>
#include <d3dcompiler.h>

//#include "UEngine"
#include "Engine/Renderer/FPrimitiveRenderData.h"
#include "GDevice.h"
#include "../Matrix.h"
#include "../FQuaternion.h"
//#include "../FVertexSimple.h"
#include "Engine/Primitive/FMeshResource.h"
#include "Container/TArray.h"


//struct FVertexSimple;
struct FConstants
{
	FMatrix MVP;
};
struct FGridConstants
{
	FVector CameraPos;
	float Padding;
};
class UScene;
class FEditor;
struct FPrimitiveRenderData;

#include <cmath>


class FRenderer
{
public:
	GDevice* Device;
	ID3D11DeviceContext* DeviceContext;
	ID3D11Device* D3DDevice;

	ID3D11RasterizerState* DefaultRasterizerState = nullptr;   // 래스터라이저 상태(컬링, 채우기 모드 등 정의)
	ID3D11RasterizerState* CullFrontRasterizerState = nullptr;   // 래스터라이저 상태(컬링, 채우기 모드 등 정의)
	ID3D11BlendState* AlphaBlendState = nullptr;

	ID3D11Buffer* TransformConstantBuffer = nullptr;     
	ID3D11Buffer* GridConstantBuffer = nullptr;          


	FLOAT                   ClearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	D3D11_VIEWPORT          ViewportInfo;               // 렌더링 영역을 정의하는 뷰포트 정보

	ID3D11VertexShader* SimpleVertexShader = nullptr;
	ID3D11PixelShader* SimplePixelShader = nullptr;
	ID3D11InputLayout* SimpleInputLayout = nullptr;
	ID3D11VertexShader* HighlightVertexShader = nullptr;
	ID3D11PixelShader* HighlightPixelShader = nullptr;
	ID3D11VertexShader* GridVertexShader = nullptr;
	ID3D11PixelShader* GridPixelShader = nullptr;
	
	unsigned int Stride;

	void Create(HWND HWnd, GDevice* InDevice);					// 렌더러 초기화 함수

	void Shutdown();                                // 렌더러에 사용된 모든 리소스를 해제하는 함수

	void CreateShaders();
	void ReleaseShader();
	void PrepareRTVDSV();
	void PrepareShader();

	ID3D11Buffer* CreateVertexBuffer(FVertexSimple* vertices, UINT byteWidth);
	void ReleaseVertexBuffer(ID3D11Buffer* vertexBuffer);

	void CreateConstantBuffer();								// 상수 버퍼 생성 함수
	void ReleaseConstantBuffer();								// 상수 버퍼 소멸 함수
	void UpdateTransformConstantBuffer(const FMatrix& WorldMatrix);      // 상수 버퍼 업데이트 함수
	void UpdateGridConstantBuffer(const FVector& CameraPos);

	void CreateRasterizerState();
	void ReleaseRasterizerState();

	void CreateAlphaBlendState();
	void ReleaseAlphaBlendState();

	void BeginFrame();
	void EndFrame();

	void Render(FEditor* Editor, UScene* Scene);
	void RenderPrimitive(const FPrimitiveRenderData& Data);
	void RenderHighlight(const FPrimitiveRenderData& Data);
	void RenderGrid(FMeshResource* Data);
};
