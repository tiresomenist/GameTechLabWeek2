#pragma once

#include "UPrimitiveComponent.h"
#include "../../GResourceManager.h"
#include "../FClassType.h"

class USphereComponent : public UPrimitiveComponent
{
public:
    static FClassType* GetClass();
    ~USphereComponent() {};

protected:
    USphereComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType)
        : UPrimitiveComponent(InUUID, InInternalIndex, InClassType) {
        Mesh = GResourceManager::GetInstance()->GetOrCreatePrimitive(type);

        VertexBuffer = Mesh->VertexBuffer;
        IndexBuffer = Mesh->IndexBuffer;
        VertexStride = Mesh->Stride;
        IndexCount = Mesh->IndexCount;
    };

    FMeshResource* Mesh = nullptr;
    std::string type = "Sphere";
};
