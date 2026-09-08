#include "UObjectAxisGizmo.h"
#include "Engine/Object/USceneComponent.h"
#include "Engine/GResourceManager.h"

TArray<FPrimitiveRenderData> UObjectAxisGizmo::GetRenderData()
{
	TArray<FPrimitiveRenderData> Result;

	XAxisWorldMatrix = FMatrix::MakeRotationYMatrix(PI / 2);
	YAxisWorldMatrix = FMatrix::MakeRotationXMatrix(-PI / 2);
	ZAxisWorldMatrix = FMatrix::Identity;
	
	auto* SelectedObject = Editor->GetSelectedSceneComponent();
	if (SelectedObject == nullptr) {
		//선택된 오브젝트가 없으면 그려지지 않도록.
		return Result;
	}
	
	// 1. 선택 객체의 월드 위치 추출
	// 2. 기즈모 멤버인 X/Y/Z축 행렬 갱신
	FMatrix ObjectWorld = SelectedObject->GetWorldMatrix();
	FVector WorldLocation(ObjectWorld.M[3][0], ObjectWorld.M[3][1], ObjectWorld.M[3][2]);
	FMatrix GizmoScaleMatrix = FMatrix::MakeScaleMatrix(GizmoScale);
	FMatrix GizmoWorldMatrix =FMatrix::MakeTranslationMatrix(WorldLocation);

	XAxisWorldMatrix = GizmoScaleMatrix * XAxisWorldMatrix * GizmoWorldMatrix;
	YAxisWorldMatrix = GizmoScaleMatrix * YAxisWorldMatrix * GizmoWorldMatrix;
	ZAxisWorldMatrix = GizmoScaleMatrix * ZAxisWorldMatrix * GizmoWorldMatrix;
	
	
	// 3. 각 화살표 메시와 행렬로 렌더 데이터 생성
	// 4. Result에 3개 추가
	FMeshResource* Mesh;
	Mesh =GResourceManager::GetInstance()->GetPrimitive("ArrowRed");
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &XAxisWorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}
	Mesh = GResourceManager::GetInstance()->GetPrimitive("ArrowGreen");
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &YAxisWorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}
	Mesh =GResourceManager::GetInstance()->GetPrimitive("ArrowBlue");
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &ZAxisWorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}
	

	return Result;
}