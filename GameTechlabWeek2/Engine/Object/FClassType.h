#pragma once

#include <functional>
#include "../Core.h"
#include "../../Container/FString.h"

class UObject;
struct FClassType;

// UObject 생성자 타입
using Constructor = std::function<UObject* (uint32, uint32, FClassType*)>;

struct FClassType
{
    // 처음 생각했던건 게임 플레이 로직에서 enum을 기반으로 코드를 체크하는 것 이었음
    // 그러나 지금은 FClassType 포인터를 기반으로 타입 체크를 수행할 수 있고, enum 값이 불필요해졌기에 주석처리
   
    //enum EType : int32
    //{
    //    ECT_UObject = 0,

    //    ECT_USceneComponent = 100,
    //    ECT_UPrimitiveComponent = 110,
    //    ECT_UCubeComponent = 111,
    //    ECT_USphereComponent = 112,
    //    ECT_UPlaneComponent = 113,
    //    ECT_UCameraComponent = 120,

    //    ECT_UGizmo = 200,
    //    ECT_UObjectAxisGizmo = 201,
    //    ECT_UWorldAxisGizmo = 202,
    //    ECT_UWorldGridGizmo = 203,

    //    ECT_UEditorWindow = 300,
    //    ECT_UConsoleWindow = 301,
    //    ECT_USceneWindow = 302,
    //    ECT_UPropertyWindow = 303,
    //};

    FClassType(const FString& InName, const Constructor InClassConstructor, const FClassType* InParentClassType = nullptr);
    
    // 객체를 직렬화할때 사용할 수 있는 이름입니다.
    const FString Name;

    // TypeInfo로 객체를 생성할 때 사용되는 객체 생성 함수입니다.
    const Constructor ClassConstructor;

    // 객체의 상속 구조를 파악할 때 사용되는 부모 포인터입니다.
    const FClassType* ParentClassType;
};
