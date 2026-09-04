#pragma once

#include <functional>
#include "../Core.h"
#include "../../FString.h"

class UObject;
struct FClassType;

// UObject 생성자 타입
using Constructor = std::function<UObject* (uint32, uint32, FClassType*)>;

struct FClassType
{
    enum EType : int32
    {
        ECT_UObject = 0,

        ECT_USceneComponent = 100,
        ECT_UPrimitiveComponent = 110,
        ECT_UCubeComponent = 111,
        ECT_USphereComponent = 112,
        ECT_UPlaneComponent = 113,
        ECT_UCameraComponent = 120,

        ECT_UGizmo = 200,
        ECT_UObjectAxisGizmo = 201,
        ECT_UWorldAxisGizmo = 202,
        ECT_UWorldGridGizmo = 203,

        ECT_UEditorWindow = 300,
        ECT_UConsoleWindow = 301,
        ECT_USceneWindow = 302,
        ECT_UPropertyWindow = 303,
    };

    FClassType(const FString& InName, const Constructor InClassConstructor, const EType InType);
    
    const FString Name;
    const Constructor ClassConstructor;
    const EType Type;
};