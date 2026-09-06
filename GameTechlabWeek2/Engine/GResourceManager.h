#pragma once
#include <unordered_map>
#include <map>
#include <string>
#include "GDevice.h"

#include "Container/FString.h"

struct FMeshResource
{
	ID3D11Buffer* VertexBuffer = nullptr;
	ID3D11Buffer* IndexBuffer = nullptr;
	UINT VertexCount = 0;
	UINT IndexCount = 0;
	UINT Stride = 0;
};

struct FShaderResource
{
	ID3D11VertexShader* VertexShader = nullptr;
	ID3D11PixelShader* PixelShader = nullptr;
	ID3D11InputLayout* InputLayout = nullptr;
};

//enum class EPrimitiveType
//{
//	Sphere, Cube, Cylinder, Cone, Plane
//};

class GResourceManager
{
public:
	static GResourceManager* GetInstance();

	void Initialize(GDevice* InDevice);
	void Shutdown();

	// ---- Geometry ----
	FMeshResource* GetOrCreatePrimitive(const FString& Type);

	// ---- Shader ----
	FShaderResource* GetOrCreateShader(const std::wstring& FilePath,
		const std::string& VSEntry,
		const std::string& PSEntry,
		const D3D11_INPUT_ELEMENT_DESC* Layout,
		UINT LayoutCount);

private:
	GResourceManager() = default;
	~GResourceManager() = default;
	GResourceManager(const GResourceManager&) = delete;
	GResourceManager& operator=(const GResourceManager&) = delete;

	GDevice* Device = nullptr;

	std::unordered_map<std::string, FMeshResource*> PrimitiveCache;
	//std::unordered_map<std::string, FShaderResource*> ShaderCache;	// 일단 Renderer에서 - 셰이더 무조건 하나만 쓰니까..
	//std::map<std::pair<D3D11_FILL_MODE, D3D11_CULL_MODE>, ID3D11RasterizerState*> RasterizerStateCache;
};

