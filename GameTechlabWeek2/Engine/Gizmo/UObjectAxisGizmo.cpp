#include "UObjectAxisGizmo.h"
#include "Engine/Object/USceneComponent.h"
#include "Engine/GResourceManager.h"

//UObjectAxisGizmo::UObjectAxisGizmo()

void UObjectAxisGizmo::Initialize()
{
	Handles = {
	{ 0, nullptr, FMatrix::MakeRotationYMatrix(PI / 2) },
	{ 1, nullptr, FMatrix::MakeRotationXMatrix(-PI / 2) },
	{ 2, nullptr, FMatrix::Identity }
	};
	Mode = EGizmoMode::Translate;
	SetMode(Mode);
}

bool UObjectAxisGizmo::UpdateTransform() {
	if (Editor == nullptr || Handles.Num() != 3) return false;

	auto* SelectedObject = Editor->GetSelectedSceneComponent();
	if (SelectedObject == nullptr) return false;

	const FMatrix& ObjectWorld = SelectedObject->GetWorldMatrix();

	const FVector WorldLocation(ObjectWorld.M[3][0],ObjectWorld.M[3][1],ObjectWorld.M[3][2]);

	const FMatrix ScaleMatrix =	FMatrix::MakeScaleMatrix(GizmoScale);
	
	const FMatrix TranslationMatrix = FMatrix::MakeTranslationMatrix(WorldLocation);

	FMatrix RotationMatirx;
	if (Mode == EGizmoMode::Scale) {
		RotationMatirx = SelectedObject->GetRelativeRotation().ToRotationMatrix();
	}
	else {
		RotationMatirx = FMatrix::Identity;
	}

	Handles[0].WorldMatrix = ScaleMatrix * FMatrix::MakeRotationYMatrix(PI / 2) * RotationMatirx * TranslationMatrix;
	Handles[1].WorldMatrix = ScaleMatrix * FMatrix::MakeRotationXMatrix(-PI / 2) * RotationMatirx * TranslationMatrix;
	Handles[2].WorldMatrix = ScaleMatrix * RotationMatirx * TranslationMatrix;

	return true;
}

TArray<FPrimitiveRenderData> UObjectAxisGizmo::GetRenderData()
{
	switch (Mode)
	{
	case EGizmoMode::Translate:
		return GetTranslateRenderData();

	case EGizmoMode::Rotate:
		return GetRotateRenderData();

	case EGizmoMode::Scale:
		return GetScaleRenderData();
	}

	return {};
}

TArray<FPrimitiveRenderData> UObjectAxisGizmo::GetTranslateRenderData()
{
	TArray<FPrimitiveRenderData> Result;

	if (!UpdateTransform()) {
		return Result;
	}
	FMeshResource* Mesh;
	Mesh = Handles[0].Mesh;
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &Handles[0].WorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}
	Mesh = Handles[1].Mesh;
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &Handles[1].WorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}
	Mesh = Handles[2].Mesh;
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;

		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &Handles[2].WorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}

	return Result;
}

TArray<FPrimitiveRenderData> UObjectAxisGizmo::GetRotateRenderData()
{
	TArray<FPrimitiveRenderData> Result;

	if (!UpdateTransform()) {
		return Result;
	}
	FMeshResource* Mesh;
	Mesh = Handles[0].Mesh;
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &Handles[0].WorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}
	Mesh = Handles[1].Mesh;
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &Handles[1].WorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}
	Mesh = Handles[2].Mesh;
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;

		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &Handles[2].WorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}
	return Result;

}

TArray<FPrimitiveRenderData> UObjectAxisGizmo::GetScaleRenderData()
{
	TArray<FPrimitiveRenderData> Result;

	if (!UpdateTransform()) {
		return Result;
	}
	FMeshResource* Mesh;
	Mesh = Handles[0].Mesh;
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &Handles[0].WorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}
	Mesh = Handles[1].Mesh;
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &Handles[1].WorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}
	Mesh = Handles[2].Mesh;
	if (Mesh != nullptr)
	{
		FPrimitiveRenderData Data;
		Data.VertexBuffer = Mesh->VertexBuffer;
		Data.IndexBuffer = Mesh->IndexBuffer;
		Data.Stride = Mesh->Stride;
		Data.IndexCount = Mesh->IndexCount;
		Data.Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;

		// UObjectAxisGizmo의 멤버 행렬
		Data.WorldMatrix = &Handles[2].WorldMatrix;
		Data.isSelected = false;

		Result.Add(Data);
	}
	return Result;

}

FMatrix UObjectAxisGizmo::GetXAxisWorldMatirx() const
{
	return Handles[0].WorldMatrix;
}

FMatrix UObjectAxisGizmo::GetYAxisWorldMatirx() const
{
	return Handles[1].WorldMatrix;
}

FMatrix UObjectAxisGizmo::GetZAxisWorldMatirx() const
{
	return Handles[2].WorldMatrix;
}

void UObjectAxisGizmo::SetMode(EGizmoMode InMode)
{
	Mode = InMode;
	TArray<FString> Names;
	switch (Mode)
	{
	case EGizmoMode::Translate: Names = { "MoveRed", "MoveGreen", "MoveBlue" }; break;
	case EGizmoMode::Rotate: Names = { "RotateRed", "RotateGreen", "RotateBlue" }; break;
	case EGizmoMode::Scale: Names = { "ScaleRed", "ScaleGreen", "ScaleBlue" }; break;
	}
	if (Names.Num() != 3 || Handles.Num() != 3) return;
	for (int32 Axis = 0; Axis < 3; ++Axis)
		Handles[Axis].Mesh = GResourceManager::GetInstance()->GetPrimitive(Names[Axis]);
}
