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

bool FGizmoPicker::RaySegmentIntersect(const FRay& Ray, FVector A, FVector B, float Radius, float&OutRayT,float& OutDistance) {
	OutRayT = 0.0f;
	OutDistance = std::numeric_limits<float>::infinity();

	if (!std::isfinite(Radius) || Radius < 0.0f)
		return false;

	const FVector D = Ray.Direction;
	const FVector E = B - A;
	const FVector W = Ray.Origin - A;

	const double a = D.Dot(D);
	const double b = D.Dot(E);
	const double c = E.Dot(E);
	const double d = D.Dot(W);
	const double e = E.Dot(W);

	if (!std::isfinite(a) || !std::isfinite(b) ||!std::isfinite(c) || !std::isfinite(d) ||!std::isfinite(e) || a <= 0.0)
	{
		return false;
	}

	double BestDistanceSquared =std::numeric_limits<double>::infinity();

	double BestT = 0.0;

	auto Consider = [&](double t, double u)
		{
			// R(t) - S(u)
			const double DX = double(W.X) + t * D.X - u * E.X;
			const double DY = double(W.Y) + t * D.Y - u * E.Y;
			const double DZ = double(W.Z) + t * D.Z - u * E.Z;
			const double DistanceSquared =DX * DX + DY * DY + DZ * DZ;
			if (DistanceSquared < BestDistanceSquared)
			{
				BestDistanceSquared = DistanceSquared;
				BestT = t;
			}
		};

	if (c <= 0.0)
	{
		// 길이가 0인 선분은 점 A로 처리
		Consider((std::max)(0.0, -d / a), 0.0);
	}
	else
	{
		const double Denominator = a * c - b * b;

		// 평행하지 않은 경우, 두 무한 직선의 최근접점
		if (Denominator > 1.0e-12 * a * c)
		{
			const double t = (b * e - c * d) / Denominator;
			const double u = (a * e - b * d) / Denominator;

			if (t >= 0.0 && u >= 0.0 && u <= 1.0)
				Consider(t, u);
		}

		// 경계도 검사: 레이 시작점과 선분
		Consider(0.0, std::clamp(e / c, 0.0, 1.0));

		// 선분 시작점 A와 레이
		Consider((std::max)(0.0, -d / a), 0.0);

		// 선분 끝점 B와 레이
		Consider((std::max)(0.0, (b - d) / a), 1.0);
	}

	OutRayT = float(BestT);
	OutDistance = float(std::sqrt(BestDistanceSquared));

	return BestDistanceSquared <= double(Radius) * Radius;
}

bool FGizmoPicker::MakeWorldRay(FRay& OutRay) {

	auto& Input = *GInputManager::GetInstance();
	float NDCX = Input.GetLeftCursorX();
	float NDCY = Input.GetLeftCursorY();

	FVector4 Near(NDCX, NDCY, 0.0f, 1.0f);
	FVector4 Far(NDCX, NDCY, 1.0f, 1.0f);
	FMatrix Projection = Editor->GetEditorCamera()->GetProjectionMatrix();
	FMatrix View = Editor->GetEditorCamera()->GetViewMatrix();

	FMatrix VPInverse;
	if (!(View * Projection).TryInverse(VPInverse)) {
		return false;
	}

	FVector4 NearWorld = Near * VPInverse;	//World에서의 Ray 시작점
	FVector4 FarWorld = Far * VPInverse; //World에서의 Ray 끝점

	if (std::fabs(NearWorld.W) < 1.0e-6f || std::fabs(FarWorld.W) < 1.0e-6f) return false;

	NearWorld = FVector4(FVector(NearWorld) / NearWorld.W, 1.0f);
	FarWorld = FVector4(FVector(FarWorld) / FarWorld.W, 1.0f);

	FVector4 Direction = FVector4((FVector(FarWorld) - FVector(NearWorld)).GetNormalized(), 0.0f);	//Ray 방향

	OutRay.Origin = FVector(NearWorld);
	OutRay.Direction = FVector(Direction);
	return true;
}

int FGizmoPicker::Pick(UGizmo* InGizmos)
{
    auto* Gizmo = dynamic_cast<UObjectAxisGizmo*>(InGizmos);
    if (!Editor || !Editor->GetEditorCamera() || !Gizmo || !Gizmo->UpdateTransform()) return -1;
    const auto& Viewport = GDevice::GetInstance()->GetViewport();
    if (Viewport.Width <= 0 || Viewport.Height <= 0) return -1;
    auto* Camera = Editor->GetEditorCamera();
    Camera->SetAspectRatio(Viewport.Width / Viewport.Height);
    const FMatrix VP = Camera->GetViewMatrix() * Camera->GetProjectionMatrix();
    auto& Input = *GInputManager::GetInstance();
    // Use the mouse-down position, not the latest drag position.
    const FVector Click(
        Viewport.TopLeftX + (Input.GetLeftCursorX() + 1) * 0.5f * Viewport.Width,
        Viewport.TopLeftY + (1 - Input.GetLeftCursorY()) * 0.5f * Viewport.Height, 0);
    constexpr float PickRadiusPixels = 6.0f;
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
            FVector A(FVector4(V0.x, V0.y, V0.z, 1) * Handle.WorldMatrix);
            FVector B(FVector4(V1.x, V1.y, V1.z, 1) * Handle.WorldMatrix);
            // Clip against the D3D near plane before screen projection.
            const FVector4 CA = FVector4(A, 1) * VP;
            const FVector4 CB = FVector4(B, 1) * VP;
            if (!std::isfinite(CA.Z) || !std::isfinite(CB.Z) || (CA.Z < 0 && CB.Z < 0)) continue;
            if (CA.Z < 0) A = A + (B - A) * (CA.Z / (CA.Z - CB.Z));
            else if (CB.Z < 0) B = A + (B - A) * (CA.Z / (CA.Z - CB.Z));
            FVector PA, PB;
            if (!WorldToPixel(A, VP, Viewport, PA) || !WorldToPixel(B, VP, Viewport, PB)) continue;
            const FVector Edge = PB - PA;
            const float LengthSquared = Edge.LengthSquared();
            const float T = LengthSquared > 1.0e-8f
                ? std::clamp((Click - PA).Dot(Edge) / LengthSquared, 0.0f, 1.0f) : 0.0f;
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
