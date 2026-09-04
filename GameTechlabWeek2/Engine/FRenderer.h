#pragma once

// D3D11 librarys
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// D3D11 headers
#include <d3d11.h>
#include <d3dcompiler.h>

#include "../Matrix.h"

struct FVertexSimple;
struct FConstants
{
	FMatrix MVP;
};
class UScene;
struct FPrimitiveRenderData;

class FRenderer
{
public:
	// Direct3D 11 장치(Device)와 장치 컨텍스트(Device Context) 및 스왑 체인(Swap Chain)을 관리하기 위한 포인터들
	ID3D11Device* Device = nullptr;                     // GPU와 통신하기 위한 Direct3D 장치
	ID3D11DeviceContext* DeviceContext = nullptr;       // GPU 명령 실행을 담당하는 컨텍스트
	IDXGISwapChain* SwapChain = nullptr;                // 프레임 버퍼를 교체하는 데 사용되는 스왑 체인

	// 렌더링에 필요한 리소스 및 상태를 관리하기 위한 변수들
	ID3D11Texture2D* FrameBuffer = nullptr;             // 화면 출력용 텍스처
	ID3D11RenderTargetView* FrameBufferRTV = nullptr;   // 텍스처를 렌더 타겟으로 사용하는 뷰
	ID3D11RasterizerState* RasterizerState = nullptr;   // 래스터라이저 상태(컬링, 채우기 모드 등 정의)
	ID3D11Buffer* ConstantBuffer = nullptr;             // 쉐이더에 데이터를 전달하기 위한 상수 버퍼
	ID3D11Texture2D* DepthStencilBuffer = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;

	FLOAT                   ClearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	D3D11_VIEWPORT          ViewportInfo;               // 렌더링 영역을 정의하는 뷰포트 정보

	ID3D11VertexShader* SimpleVertexShader;
	ID3D11PixelShader* SimplePixelShader;
	ID3D11InputLayout* SimpleInputLayout;

	unsigned int Stride;

	std::vector<FVertex> SphereVertices;
	std::vector<uint32_t> SphereIndices;

public:
	void Create(HWND hWindow, uint32 InWidth, uint32 InHeight);  // 렌더러 초기화 함수

	void CreateDeviceAndSwapChain(HWND hWindow);    // Direct3D 장치 및 스왑 체인을 생성하는 함수
	void ReleaseDeviceAndSwapChain();               // Direct3D 장치 및 스왑 체인을 해제하는 함수
	void CreateFrameBuffer();                       // 프레임 버퍼를 생성하는 함수
	void ReleaseFrameBuffer();                      // 프레임 버퍼를 해제하는 함수
	void CreateRasterizerState();                   // 래스터라이저 상태를 생성하는 함수
	void ReleaseRasterizerState();                  // 래스터라이저 상태를 해제하는 함수
	bool CreateDepthStencilBuffer(int32 InWidth, int32 InHeight); // 깊이 스텐실 버퍼를 생성하는 함수
	void ReleaseDepthStencilBuffer();               // 깊이 스텐실 버퍼를 해제하는 함수

	void Shutdown();                                // 렌더러에 사용된 모든 리소스를 해제하는 함수
	void SwapBuffer();                              // 스왑 체인의 백 버퍼와 프론트 버퍼를 교체하여 화면에 출력

	void CreateShader();
	void ReleaseShader();
	void Prepare();
	void PrepareShader();

	ID3D11Buffer* CreateVertexBuffer(FVertexSimple* vertices, UINT byteWidth);
	void ReleaseVertexBuffer(ID3D11Buffer* vertexBuffer);


	void CreateConstantBuffer();                    // 상수 버퍼 생성 함수
	void ReleaseConstantBuffer();                   // 상수 버퍼 소멸 함수
	void UpdateConstantBuffer(const FMatrix& WorldMatrix);      // 상수 버퍼 업데이트 함수

	void Render(UScene* Scene);
	void Render();
	ID3D11Buffer* CreateIndexBuffer(uint32_t* indices, UINT byteWidth);
	void UpdateConstantBuffer(const XMMATRIX& MVP);
	ID3D11Buffer* CreateVertexBuffer(FVertex* vertices, UINT byteWidth);
	void RenderPrimitive(const FPrimitiveRenderData& Data);
};

#include <directxmath.h>
using namespace DirectX;
namespace Matrix4x4
{
	inline XMFLOAT4X4 Identity()
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixIdentity());
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 Zero()
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixSet(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMFLOAT4X4& xmmtx4x4Matrix1, XMFLOAT4X4& xmmtx4x4Matrix2)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixMultiply(XMLoadFloat4x4(&xmmtx4x4Matrix1), XMLoadFloat4x4(&xmmtx4x4Matrix2)));
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 Scale(XMFLOAT4X4& xmf4x4Matrix, float fScale)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMLoadFloat4x4(&xmf4x4Matrix) * fScale);
		/*
				XMVECTOR S, R, T;
				XMMatrixDecompose(&S, &R, &T, XMLoadFloat4x4(&xmf4x4Matrix));
				S = XMVectorScale(S, fScale);
				T = XMVectorScale(T, fScale);
				R = XMVectorScale(R, fScale);
				//R = XMQuaternionMultiply(R, XMVectorSet(0, 0, 0, fScale));
				XMStoreFloat4x4(&xmf4x4Result, XMMatrixAffineTransformation(S, XMVectorZero(), R, T));
		*/
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 Add(XMFLOAT4X4& xmmtx4x4Matrix1, XMFLOAT4X4& xmmtx4x4Matrix2)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMLoadFloat4x4(&xmmtx4x4Matrix1) + XMLoadFloat4x4(&xmmtx4x4Matrix2));
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMFLOAT4X4& xmmtx4x4Matrix1, XMMATRIX& xmmtxMatrix2)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMLoadFloat4x4(&xmmtx4x4Matrix1) * xmmtxMatrix2);
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 RotateAxis(XMFLOAT3& xmf3Axis, float fAngle)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixRotationAxis(XMLoadFloat3(&xmf3Axis), XMConvertToRadians(fAngle)));
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 Rotate(float x, float y, float z)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixRotationRollPitchYaw(XMConvertToRadians(x), XMConvertToRadians(y), XMConvertToRadians(z)));
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 AffineTransformation(XMFLOAT3& xmf3Scaling, XMFLOAT3& xmf3RotateOrigin, XMFLOAT3& xmf3Rotation, XMFLOAT3& xmf3Translation)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixAffineTransformation(XMLoadFloat3(&xmf3Scaling), XMLoadFloat3(&xmf3RotateOrigin), XMQuaternionRotationRollPitchYaw(XMConvertToRadians(xmf3Rotation.x), XMConvertToRadians(xmf3Rotation.y), XMConvertToRadians(xmf3Rotation.z)), XMLoadFloat3(&xmf3Translation)));
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMMATRIX& xmmtxMatrix1, XMFLOAT4X4& xmmtx4x4Matrix2)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, xmmtxMatrix1 * XMLoadFloat4x4(&xmmtx4x4Matrix2));
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 Interpolate(XMFLOAT4X4& xmf4x4Matrix1, XMFLOAT4X4& xmf4x4Matrix2, float t)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMVECTOR S0, R0, T0, S1, R1, T1;
		XMMatrixDecompose(&S0, &R0, &T0, XMLoadFloat4x4(&xmf4x4Matrix1));
		XMMatrixDecompose(&S1, &R1, &T1, XMLoadFloat4x4(&xmf4x4Matrix2));
		XMVECTOR S = XMVectorLerp(S0, S1, t);
		XMVECTOR T = XMVectorLerp(T0, T1, t);
		XMVECTOR R = XMQuaternionSlerp(R0, R1, t);
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixAffineTransformation(S, XMVectorZero(), R, T));
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 Inverse(XMFLOAT4X4& xmmtx4x4Matrix)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixInverse(NULL, XMLoadFloat4x4(&xmmtx4x4Matrix)));
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 Transpose(XMFLOAT4X4& xmmtx4x4Matrix)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixTranspose(XMLoadFloat4x4(&xmmtx4x4Matrix)));
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 PerspectiveFovLH(float FovAngleY, float AspectRatio, float NearZ, float FarZ)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixPerspectiveFovLH(FovAngleY, AspectRatio, NearZ, FarZ));
		return(xmf4x4Result);
	}

	inline XMFLOAT4X4 LookAtLH(XMFLOAT3& xmf3EyePosition, XMFLOAT3& xmf3LookAtPosition, XMFLOAT3& xmf3UpDirection)
	{
		XMFLOAT4X4 xmf4x4Result;
		XMStoreFloat4x4(&xmf4x4Result, XMMatrixLookAtLH(XMLoadFloat3(&xmf3EyePosition), XMLoadFloat3(&xmf3LookAtPosition), XMLoadFloat3(&xmf3UpDirection)));
		return(xmf4x4Result);
	}
}

#include <vector>
#include <cmath>

// 사용하시는 정점 구조체에 맞게 수정하세요.
struct FVertex
{
	float x, y, z;      // Position
	float nx, ny, nz;   // Normal (빛 테스트용)
	float u, v;         // UV (텍스처 테스트용)
};

void GenerateSphere(float Radius, int Slices, int Stacks, std::vector<FVertex>& OutVertices, std::vector<uint32_t>& OutIndices)
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

			FVertex vertex;
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

struct FPrimitiveRenderData
{
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	UINT                Stride;
	UINT                IndexCount;
	D3D11_PRIMITIVE_TOPOLOGY Topology;

	ID3D11ShaderResourceView* Material;       // VS/PS, 텍스처 SRV 등을 들고 있는 객체
	const FMatrix* WorldMatrix;    // 컴포넌트가 소유한 월드행렬 가리키기
};