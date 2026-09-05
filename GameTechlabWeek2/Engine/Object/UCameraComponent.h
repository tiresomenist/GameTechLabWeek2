#pragma once

#include "Engine/Core.h"
#include "Engine/Object/USceneComponent.h"
#include "../../Matrix.h"
#include "USceneComponent.h"

enum class EProjectionMode
{
    Orthographic,
    Perspective
};

class UCameraComponent : public USceneComponent
{
protected:
    UCameraComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

public:
    static FClassType* GetClass();
    FVector GetForward() const;
    FVector GetRight() const;
    FVector GetUp() const;

    FMatrix GetViewMatrix() const;
    FMatrix GetProjectionMatrix() const;
    FMatrix GetOrthographicProjectionMatrix() const;
    FMatrix GetPerspectiveProjectionMatrix() const;
    float GetOrthoHeight() const;
    void SetOrthoHeight(float InHeight);

    float GetFOV()const;
    float GetAspectRatio()const;
    float GetNearZ()const;
    float GetFarZ()const;

    void SetFOVByRadian(const float& InRadian);
    void SetFOVByDegree(const float& InDegree);
    
    void SetAspectRatio(const float& InRatio);

    void MoveCamera(const float& InForward,const float& InRight, const float& InDeltaTime);

    //카메라가 원하는 지점을 바라보도록 하는 함수
    void LookAt(const FVector& InTargetPosition);
    EProjectionMode ProjectionMode = EProjectionMode::Perspective;
    

private:
    float MoveSpeed = 5.0f;            // 카메라 이동속력
    float FOV = 60.0f * PI / 180.0f;   //세로 시야각. 저장단위 라디안
    float AspectRatio = 1.0f;          //뷰포트 가로/세로 비율
    float NearZ = 0.1f;
    float OrthoHeight = 10.0f;         //직교 투영의 전체 세로 범위 (월드 단위)
    float FarZ = 1000.0f;

};
