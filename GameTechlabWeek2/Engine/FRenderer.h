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

#include "../Engine/Editor/Window/UEditorWindow.h"

//struct FVertexSimple;
struct FConstants
{
	FMatrix MVP;
};
class UScene;
struct FPrimitiveRenderData;

#include <cmath>

// @TEST >>

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

    inline XMFLOAT4X4 Rotate(const FQuaternion& Rotation)
    {
        const FMatrix Matrix = Rotation.ToRotationMatrix();
        return XMFLOAT4X4(&Matrix.M[0][0]);
    }

    inline XMFLOAT4X4 RotateAxis(XMFLOAT3& Axis, float AngleDegrees)
    {
        return Rotate(FQuaternion::FromAxisAngle(FVector(Axis.x, Axis.y, Axis.z), XMConvertToRadians(AngleDegrees)));
    }

    inline XMFLOAT4X4 AffineTransformation(XMFLOAT3& Scaling, XMFLOAT3& RotateOrigin,
        const FQuaternion& Rotation, XMFLOAT3& Translation)
    {
        FQuaternion Q = Rotation;
        Q.Normalize();
        XMFLOAT4X4 Result;
        XMStoreFloat4x4(&Result, XMMatrixAffineTransformation(XMLoadFloat3(&Scaling),
            XMLoadFloat3(&RotateOrigin), XMVectorSet(Q.X, Q.Y, Q.Z, Q.W), XMLoadFloat3(&Translation)));
        return Result;
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
// @TEST <<

class FRenderer
{
public:
	GDevice* Device;
	ID3D11DeviceContext* DeviceContext;
	ID3D11Device* D3DDevice;

	ID3D11RasterizerState* RasterizerState = nullptr;   // 래스터라이저 상태(컬링, 채우기 모드 등 정의)
	ID3D11Buffer* ConstantBuffer = nullptr;             // 쉐이더에 데이터를 전달하기 위한 상수 버퍼
	FLOAT                   ClearColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
	D3D11_VIEWPORT          ViewportInfo;               // 렌더링 영역을 정의하는 뷰포트 정보

	ID3D11VertexShader* SimpleVertexShader = nullptr;
	ID3D11PixelShader* SimplePixelShader = nullptr;
	ID3D11InputLayout* SimpleInputLayout = nullptr;

    unsigned int Stride;

	//std::vector<FVertexTest> SphereVertices{};
	//std::vector<uint32_t> SphereIndices{};
	//ID3D11Buffer* SphereVertexBuffer = nullptr;
	//ID3D11Buffer* SphereIndexBuffer = nullptr;


    void Create(HWND hWindow, GDevice* InDevice);					// 렌더러 초기화 함수

    void Shutdown();                                // 렌더러에 사용된 모든 리소스를 해제하는 함수

    void CreateShader();
    void ReleaseShader();
    void Prepare();
    void PrepareShader();

    ID3D11Buffer* CreateVertexBuffer(FVertexSimple* vertices, UINT byteWidth);
    void ReleaseVertexBuffer(ID3D11Buffer* vertexBuffer);

	void CreateConstantBuffer();								// 상수 버퍼 생성 함수
	void ReleaseConstantBuffer();								// 상수 버퍼 소멸 함수
	void UpdateConstantBuffer(const FMatrix& WorldMatrix);      // 상수 버퍼 업데이트 함수

	void CreateRasterizerState();
	void ReleaseRasterizerState();

	void BeginFrame();
	void EndFrame();

	void Render(UScene* Scene);
	void RenderUI(TArray<UEditorWindow&>& WindowArray);
	void RenderPrimitive(const FPrimitiveRenderData& Data);

	//// @TEST >>
	//void Render();
	//ID3D11Buffer* CreateIndexBuffer(uint32_t* indices, UINT byteWidth);
	//ID3D11Buffer* CreateVertexBuffer(FVertexTest* vertices, UINT byteWidth);
	void UpdateConstantBuffer(const XMMATRIX& MVP);
	//// @TEST <<
};
