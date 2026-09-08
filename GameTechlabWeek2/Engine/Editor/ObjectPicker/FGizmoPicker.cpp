#include "FGizmoPicker.h"
#include "Engine/InputManager/GInputManager.h"
#include "Engine/Log.h"
#include "Engine/Scene/UScene.h"
#include "Engine/Gizmo/UObjectAxisGizmo.h"
#include "Engine/Editor/ObjectPicker/FObjectPicker.h"

FGizmoPicker::FGizmoPicker(UCameraComponent* InCamera)
{
	Camera = InCamera;
}

FGizmoPicker::~FGizmoPicker()
{
}

void FGizmoPicker::Tick()
{
}

bool FGizmoPicker::RayTriangleIntersect(const FRay& Ray, FVector A, FVector B, FVector C, float& OutDistance) {
	const FVector Edge1 = B - A;
	const FVector Edge2 = C - A;

	const FVector P = Ray.Direction.Cross(Edge2);
	const float Determinant = Edge1.Dot(P);

	if (std::fabs(Determinant) < 1.0e-6f)
		return false; // 평행 또는 퇴화 삼각형

	const float InverseDeterminant = 1.0f / Determinant;

	const FVector T = Ray.Origin - A;
	const float U = T.Dot(P) * InverseDeterminant;
	if (U < 0.0f || U > 1.0f)
		return false;

	const FVector Q = T.Cross(Edge1);
	const float V = Ray.Direction.Dot(Q) * InverseDeterminant;
	if (V < 0.0f || U + V > 1.0f)
		return false;

	OutDistance = Edge2.Dot(Q) * InverseDeterminant;
	return OutDistance > 1.0e-6f;
}

bool FGizmoPicker::MakeWorldRay(FRay& OutRay) {

	auto& Input = *GInputManager::GetInstance();
	float NDCX = Input.GetLeftCursorX();
	float NDCY = Input.GetLeftCursorY();

	FVector4 Near(NDCX, NDCY, 0.0f, 1.0f);
	FVector4 Far(NDCX, NDCY, 1.0f, 1.0f);
	FMatrix Projection = Camera->GetProjectionMatrix();
	FMatrix View = Camera->GetViewMatrix();

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
	//-1:선택 실패 0:X 1:Y 2:Z
	FRay Ray;
	
	if (InGizmos==nullptr||!InGizmos->IsA(UObjectAxisGizmo::GetClass())) return -1;	// 들어온 기즈모가 오브젝트 액시스 기즈모가 아님
	if (!MakeWorldRay(Ray)) return -1;	//Ray 계산 실패
	UObjectAxisGizmo* InObjectAxisGizmo = dynamic_cast<UObjectAxisGizmo*>(InGizmos);
	if (InObjectAxisGizmo==nullptr) return -1;	//다이나믹캐스팅 실패
	int SelectedGizmo = -1;
	float ClosestDistance = 100000.f;
	TArray<FMeshResource*> GizmoXYZ = InGizmos->GetMeshResources();
	TArray<FPrimitiveRenderData> GizmoRenderData =
		InObjectAxisGizmo->GetRenderData();

	if (GizmoXYZ.Num() != 3 || GizmoRenderData.Num() != 3) return -1;

	for (int32 Cursor = 0;Cursor < 3;Cursor++) {
		
		const FMatrix* World = GizmoRenderData[Cursor].WorldMatrix;

		for (uint32 Index = 0; Index + 2 < GizmoXYZ[Cursor]->IndexCount; Index += 3)
		{
			const uint32 I0 = GizmoXYZ[Cursor]->indexes[Index];
			const uint32 I1 = GizmoXYZ[Cursor]->indexes[Index + 1];
			const uint32 I2 = GizmoXYZ[Cursor]->indexes[Index + 2];

			const FVertexSimple& V0 = GizmoXYZ[Cursor]->vertexs[I0];
			const FVertexSimple& V1 = GizmoXYZ[Cursor]->vertexs[I1];
			const FVertexSimple& V2 = GizmoXYZ[Cursor]->vertexs[I2];

			FVector A(V0.x, V0.y, V0.z);
			FVector B(V1.x, V1.y, V1.z);
			FVector C(V2.x, V2.y, V2.z);

			
			// 현재 오브젝트의 WorldMatrix를 반영
			A = FVector(FVector4(A, 1.0f) * *World);
			B = FVector(FVector4(B, 1.0f) * *World);
			C = FVector(FVector4(C, 1.0f) * *World);

			float T;

			if (RayTriangleIntersect(Ray, A, B, C, T))
			{
				if (T < ClosestDistance)
				{
					ClosestDistance = T;
					//X,Y,Z축 중 어느걸 골랐는지 체크
					SelectedGizmo = Cursor;
				}
			}
		}
	}
	
	return SelectedGizmo;
}
