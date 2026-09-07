#include "GResourceManager.h"
#include "../FVertexSimple.h"
#include "Models/Sphere.h"
#include "Models/Cube.h"
#include "Models/Triangle.h"
#include "Models/PePe.h"
#include "Models/Octopus.h"
#include "Models/ArrowRed.h"
#include "Models/ArrowGreen.h"
#include "Models/ArrowBlue.h"

GResourceManager* GResourceManager::GetInstance()
{
	static GResourceManager Instance;
	return &Instance;
}

void GResourceManager::Initialize(GDevice* InDevice)
{
	Device = InDevice;

    CreateMesh("Sphere", arrow_green_vertices, arrow_green_indices);
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

FMeshResource* GResourceManager::GetPrimitive(const FString& Type)
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

FShaderResource* GResourceManager::GetShader(const std::wstring& FilePath, const std::string& VSEntry, const std::string& PSEntry, const D3D11_INPUT_ELEMENT_DESC* Layout, UINT LayoutCount)
{
	return nullptr;
}
