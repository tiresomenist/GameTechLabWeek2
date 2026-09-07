#include "FObjectPicker.h"
#include "../../InputManager/GInputManager.h"
#include "../../../FVector.h"
#include "../../../Matrix.h"
#include "../../../FVertexSimple.h"
#include "../../Scene/UScene.h"

bool FObjectPicker::MakeWorldRay(FRay& OutRay) {

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

bool RayTriangleIntersect(const FRay& Ray,FVector A, FVector B, FVector C ,float& OutDistance ) {
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

UPrimitiveComponent* FObjectPicker::Pick()
{
	FRay Ray;
	if (!MakeWorldRay(Ray)) return nullptr;	//Ray 계산 실패

	UPrimitiveComponent* SelectedObject = nullptr;
	float ClosestDistance = 100000.f;
	Scene->ForEachPrimitive(
		[&](UPrimitiveComponent* Primitive)
		{
			FMeshResource* Mesh = Primitive->GetMeshResource();
			if (Mesh == nullptr) {
				UE_LOG("클래스를 참조하지 못했습니다.");
				return;
			}
			for (uint32 Index = 0; Index + 2 < Mesh->IndexCount; Index += 3)
			{
				const uint32 I0 = Mesh->Indices[Index];
				const uint32 I1 = Mesh->Indices[Index + 1];
				const uint32 I2 = Mesh->Indices[Index + 2];

				const FVertexSimple& V0 = Mesh->Vertices[I0];
				const FVertexSimple& V1 = Mesh->Vertices[I1];
				const FVertexSimple& V2 = Mesh->Vertices[I2];

				FVector A(V0.x, V0.y, V0.z);
				FVector B(V1.x, V1.y, V1.z);
				FVector C(V2.x, V2.y, V2.z);


				// 현재 오브젝트의 WorldMatrix를 반영
				A = FVector(FVector4(A,1.0f) * Primitive->GetWorldMatrix());
				B = FVector(FVector4(B, 1.0f) * Primitive->GetWorldMatrix());
				C = FVector(FVector4(C, 1.0f) * Primitive->GetWorldMatrix());

				float T;
				
				if (RayTriangleIntersect(Ray, A, B, C, T))
				{
					if (T < ClosestDistance)
					{
						ClosestDistance = T;
						SelectedObject = Primitive;
					}
				}
			}
		}
	);
	return SelectedObject;
}

FObjectPicker::FObjectPicker(UCameraComponent* InCamera, UScene* InScene)
{
	Camera = InCamera;
	Scene = InScene;

}

FObjectPicker::~FObjectPicker()
{
}
