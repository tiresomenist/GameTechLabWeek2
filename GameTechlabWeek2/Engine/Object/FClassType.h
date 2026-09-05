#pragma once

#include <functional>
#include "Engine/Core.h"
#include "Container/FString.h"

class UObject;
struct FClassType;

// UObject 생성자 타입
using Constructor = std::function<UObject* (uint32, uint32, FClassType*)>;

struct FClassType
{
    FClassType(const FString& InName, const Constructor InClassConstructor, const FClassType* InParentClassType = nullptr);
    
    // 객체를 직렬화할때 사용할 수 있는 이름입니다.
    const FString Name;

    // TypeInfo로 객체를 생성할 때 사용되는 객체 생성 함수입니다.
    const Constructor ClassConstructor;

    // 객체의 상속 구조를 파악할 때 사용되는 부모 포인터입니다.
    const FClassType* ParentClassType;
};
