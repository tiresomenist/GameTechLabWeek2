#include "GResourceManager.h"
#include "../FVertexSimple.h"
#include "../Sphere.h"

GResourceManager* GResourceManager::GetInstance()
{
	static GResourceManager Instance;
	return &Instance;
}

void GResourceManager::Initialize(GDevice* InDevice)
{
	Device = InDevice;

    std::vector<FVertexTest> Vertices;
    std::vector<uint32_t> Indices;

    FMeshResource* MeshResource = new FMeshResource;
    UINT VertexCount = sizeof(sphere_vertices) / sizeof(sphere_vertices[0]);
    MeshResource->VertexBuffer = Device->CreateVertexBuffer(sphere_vertices, sizeof(FVertexSimple) * VertexCount);
    MeshResource->IndexBuffer = nullptr;
    MeshResource->VertexCount = VertexCount;
    MeshResource->IndexCount = 0;
    MeshResource->Stride = sizeof(FVertexSimple);
    PrimitiveCache["Sphere"] = MeshResource;
}

void GResourceManager::Shutdown()
{
    for (auto& [type, mesh] : PrimitiveCache)
    {
        if (mesh->VertexBuffer) mesh->VertexBuffer->Release();
        if (mesh->IndexBuffer)  mesh->IndexBuffer->Release();
        delete mesh;
    }
    PrimitiveCache.clear();

    //for (auto& [path, shader] : ShaderCache)
    //{
    //    if (shader->VertexShader) shader->VertexShader->Release();
    //    if (shader->PixelShader)  shader->PixelShader->Release();
    //    if (shader->InputLayout)  shader->InputLayout->Release();
    //    delete shader;
    //}
    //ShaderCache.clear();

    //for (auto& [key, state] : RasterizerStateCache)
    //    state->Release();
    //RasterizerStateCache.clear();
}

FMeshResource* GResourceManager::GetOrCreatePrimitive(std::string Type)
{
    auto it = PrimitiveCache.find(Type);
    if (it != PrimitiveCache.end())
        return it->second;
}

FShaderResource* GResourceManager::GetOrCreateShader(const std::wstring& FilePath, const std::string& VSEntry, const std::string& PSEntry, const D3D11_INPUT_ELEMENT_DESC* Layout, UINT LayoutCount)
{
	return nullptr;
}