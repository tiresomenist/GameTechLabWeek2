#include "EnGine/Editor/ObjectPicker/FGizmoPicker.h"
#include "Engine/InputManager/GInputManager.h"
#include "Engine/Log.h"
#include "Engine/GDevice.h"
#include "Engine/Scene/UScene.h"
#include "Engine/Gizmo/UObjectAxisGizmo.h"
#include "Engine/Editor/ObjectPicker/FObjectPicker.h"


namespace
{	//VP행렬->에디터의카메라참조 Viewport->GDevice 참조
	bool WorldToPixel(const FVector& Position, const FMatrix& ViewProjection, const D3D11_VIEWPORT& Viewport, FVector& OutPixel)
	{
		const FVector4 Clip = FVector4(Position, 1.0f) * ViewProjection;

		if (!std::isfinite(Clip.W) || Clip.W <= 1.0e-6f)
			return false;

		const float NDCX = Clip.X / Clip.W;
		const float NDCY = Clip.Y / Clip.W;

		OutPixel = FVector(
			Viewport.TopLeftX + (NDCX + 1.0f) * 0.5f * Viewport.Width,
			Viewport.TopLeftY + (1.0f - NDCY) * 0.5f * Viewport.Height, 0.0f
		);

		return std::isfinite(OutPixel.X) && std::isfinite(OutPixel.Y);
	}
}


FGizmoPicker::FGizmoPicker(FEditor* InEditor)
	: Editor{ InEditor }
{

}

FGizmoPicker::~FGizmoPicker()
{
}

void FGizmoPicker::Tick()
{
}

int FGizmoPicker::Pick(UGizmo* InGizmos)
{
    auto* Gizmo = dynamic_cast<UObjectAxisGizmo*>(InGizmos);
    if (!Editor || !Editor->GetEditorCamera() || !Gizmo || !Gizmo->UpdateTransform()) return -1;    //뭔가 잘못되었으면

    const auto& Viewport = GDevice::GetInstance()->GetViewport();
    if (Viewport.Width <= 0 || Viewport.Height <= 0) return -1; //창 크기가 0보다 작으면

    //현재 종횡비를 갱신하고, VP행렬을 가져온다
    auto* Camera = Editor->GetEditorCamera();
    Camera->SetAspectRatio(Viewport.Width / Viewport.Height);
    const FMatrix VP = Camera->GetViewMatrix() * Camera->GetProjectionMatrix();
    
    auto& Input = *GInputManager::GetInstance();
    //NDC좌표에서 PIXEL좌표로
    const FVector Click(
        Viewport.TopLeftX + (Input.GetLeftCursorX() + 1) * 0.5f * Viewport.Width,
        Viewport.TopLeftY + (1 - Input.GetLeftCursorY()) * 0.5f * Viewport.Height, 0);
    
    // 클릭 허용 픽셀
    constexpr float PickRadiusPixels = 8.0f;
    float BestDistanceSquared = PickRadiusPixels * PickRadiusPixels;

    int32 SelectedAxis = -1;

    for (const FGizmoHandle& Handle : Gizmo->GetHandles())
    {
        const FMeshResource* Mesh = Handle.Mesh;
        if (!Mesh || Handle.Axis < 0 || Handle.Axis > 2) continue;

        const uint32 Count = (std::min)(Mesh->IndexCount, uint32(Mesh->indexes.Num()));

        for (uint32 Index = 0; Index + 1 < Count; Index += 2)
        {
            const uint32 I0 = Mesh->indexes[Index], I1 = Mesh->indexes[Index + 1];
            if (I0 >= uint32(Mesh->vertexs.Num()) || I1 >= uint32(Mesh->vertexs.Num())) continue;
            const auto& V0 = Mesh->vertexs[I0];
            const auto& V1 = Mesh->vertexs[I1];

            //월드 좌표계에서 선분 정점 위치 계산
            FVector A(FVector4(V0.x, V0.y, V0.z, 1) * Handle.WorldMatrix);
            FVector B(FVector4(V1.x, V1.y, V1.z, 1) * Handle.WorldMatrix);

            // 클립좌표계로 변환
            const FVector4 CA = FVector4(A, 1) * VP;
            const FVector4 CB = FVector4(B, 1) * VP;
            
            //NearZ 평면과 비교해서 잘라내기
            if (!std::isfinite(CA.Z) || !std::isfinite(CB.Z) || (CA.Z < 0 && CB.Z < 0)) continue;
            
            if (CA.Z < 0) A = A + (B - A) * (CA.Z / (CA.Z - CB.Z));
            else if (CB.Z < 0) B = A + (B - A) * (CA.Z / (CA.Z - CB.Z));
            
            //정점을 픽셀로 변환
            FVector PA, PB;
            if (!WorldToPixel(A, VP, Viewport, PA) || !WorldToPixel(B, VP, Viewport, PB)) continue;
            
            //픽셀로 변환된 최종 선분
            const FVector Edge = PB - PA;
            const float LengthSquared = Edge.LengthSquared();
            //클릭 지점을 선분에 사영시켰을때의 비율
            const float T = LengthSquared > 1.0e-8f ? std::clamp((Click - PA).Dot(Edge) / LengthSquared, 0.0f, 1.0f) : 0.0f;
            const float DistanceSquared = (Click - (PA + Edge * T)).LengthSquared();
            if (DistanceSquared < BestDistanceSquared)
            {
                BestDistanceSquared = DistanceSquared;
                SelectedAxis = Handle.Axis;
            }
        }
    }
    return SelectedAxis;
}
