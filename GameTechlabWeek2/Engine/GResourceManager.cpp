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

    FMeshResource* MeshResource = new FMeshResource;
    UINT VertexCount = sizeof(sphere_vertices) / sizeof(sphere_vertices[0]);
    std::vector<uint32_t> Indices(VertexCount);
    for (uint32_t Index = 0; Index < VertexCount; ++Index)
    {
        Indices[Index] = Index;
    }

    MeshResource->VertexBuffer = Device->CreateVertexBuffer(sphere_vertices, sizeof(FVertexSimple) * VertexCount);
    MeshResource->IndexBuffer = Device->CreateIndexBuffer(Indices.data(), sizeof(uint32_t) * VertexCount);
    MeshResource->VertexCount = VertexCount;
    MeshResource->IndexCount = VertexCount;
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

FMeshResource* GResourceManager::GetOrCreatePrimitive(const FString& Type)
{
    auto Item = PrimitiveCache.find(Type);

    if (Item != PrimitiveCache.end())
    {
        return Item->second;
    }
    else
    {
        return nullptr;
    }
}

FShaderResource* GResourceManager::GetOrCreateShader(const std::wstring& FilePath, const std::string& VSEntry, const std::string& PSEntry, const D3D11_INPUT_ELEMENT_DESC* Layout, UINT LayoutCount)
{
	return nullptr;
}
