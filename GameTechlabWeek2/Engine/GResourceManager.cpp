#include "GResourceManager.h"
#include "Engine/Renderer/FVertexSimple.h"
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
    CreateMesh("Sphere", sphere_vertices, sphere_indices);
    CreateMesh("Cube", cube_vertices, cube_indices);
    //CreateMesh("Triangle", triangle_vertices, triangle_indices);
    CreateMesh("Pepe", pepe_vertices, pepe_indices);
    CreateMesh("Octopus", octopus_vertices, octopus_indices);
    CreateMesh("ArrowRed", arrow_red_vertices, arrow_red_indices);
    CreateMesh("ArrowGreen", arrow_green_vertices, arrow_green_indices);
    CreateMesh("ArrowBlue", arrow_blue_vertices, arrow_blue_indices);
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
