#include "UCameraComponent.h"

FVector UCameraComponent::GetForward() const
{
	FVector4 ForwardVector(1.0f, 0.0f, 0.0f, 0.0f);

	return FVector(ForwardVector * FMatrix::MakeRotationMatrix(FVector(0.0f, RelativeRotation.Y, RelativeRotation.Z)));
}

FVector UCameraComponent::GetRight() const
{
	FVector4 RightVector(0.0f, 1.0f, 0.0f, 0.0f);
	return FVector(RightVector * FMatrix::MakeRotationMatrix(FVector(0.0f, RelativeRotation.Y, RelativeRotation.Z)));
}

FVector UCameraComponent::GetUp() const
{
	FVector4 UpVector(0.0f, 0.0f, 1.0f, 0.0f);
	return FVector(UpVector * FMatrix::MakeRotationMatrix(FVector(0.0f, RelativeRotation.Y, RelativeRotation.Z)));
}

FMatrix UCameraComponent::GetViewMatrix() const
{
	FMatrix RotationMatrix = FMatrix::MakeRotationMatrix(FVector(0.0f, RelativeRotation.Y, RelativeRotation.Z));
	FMatrix InverseTranslationMatrix = FMatrix::MakeTranslationMatrix(RelativeLocation * -1.0f);
	return (InverseTranslationMatrix) * (RotationMatrix.Transpose());
}

FMatrix UCameraComponent::GetProjectionMatrix() const
{
	switch (ProjectionMode)
	{
	case EProjectionMode::Perspective:
		return GetPerspectiveProjectionMatrix();

	case EProjectionMode::Orthographic:
		return GetOrthographicProjectionMatrix();
	}
	assert(false && "Invalid projection mode.");
	return GetPerspectiveProjectionMatrix();
}



float UCameraComponent::GetFOV() const
{
	return FOV;
}

float UCameraComponent::GetAspectRatio() const
{
	return AspectRatio;
}

float UCameraComponent::GetNearZ() const
{
	return NearZ;
}

float UCameraComponent::GetFarZ() const
{
	return FarZ;
}

void UCameraComponent::SetFOVByRadian(const float& InRadian)
{
	FOV = InRadian;
}

void UCameraComponent::SetFOVByDegree(const float& InDegree)
{
	//도 단위의 각도를 라디안으로 자동으로 변환해서 세팅해줌.
	FOV = InDegree * PI / 180.f;
}

void UCameraComponent::SetAspectRatio(const float& InRatio)
{
	AspectRatio = InRatio;
}

void UCameraComponent::LookAt(const FVector& InTargetPosition)
{
	FVector Forward = (InTargetPosition - RelativeLocation);
	if (Forward.Length() <= UEngineStatics::Epsilon) {
		//카메라의 위치를 바라보는 경우
		return;
	}
	Forward.Normalize(); //Forward.X = cosZ*cosY,Forward.Y = sinZ,Forward.Z = -cosZ*sinY
	float CosZ = std::sqrtf(Forward.X * Forward.X + Forward.Z * Forward.Z);
	const float RotationZ = atan2(Forward.Y, CosZ);
	float RotationY = RelativeRotation.Y;
	if (CosZ > UEngineStatics::Epsilon) {
		RotationY = std::atan2(-Forward.Z, Forward.X);
	}	
	RelativeRotation.X = 0.0f;
	RelativeRotation.Y = RotationY;
	RelativeRotation.Z = RotationZ;

}

UCameraComponent::UCameraComponent(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType):USceneComponent(InUUID,InInternalIndex,InClassType)
{

}

float UCameraComponent::GetOrthoHeight() const
{
	return OrthoHeight;
}

void UCameraComponent::SetOrthoHeight(float InHeight)
{
	if (!std::isfinite(InHeight) || InHeight <= 0.0f)
	{
		return;
	}
	OrthoHeight = InHeight;
}

FMatrix UCameraComponent::GetOrthographicProjectionMatrix() const
{
	assert(std::isfinite(OrthoHeight) && OrthoHeight > 0.0f);
	assert(std::isfinite(AspectRatio) && AspectRatio > 0.0f);
	assert(std::isfinite(NearZ) && std::isfinite(FarZ) && FarZ > NearZ);

	const float VerticalScale = 2.0f / OrthoHeight;
	const float HorizontalScale = VerticalScale / AspectRatio;
	const float DepthScale = 1.0f / (FarZ - NearZ);

	// +X forward, +Y right, +Z up; row vectors, depth 0..1, W = 1.
	return FMatrix(
		0.0f, 0.0f, DepthScale, 0.0f,
		HorizontalScale, 0.0f, 0.0f, 0.0f,
		0.0f, VerticalScale, 0.0f, 0.0f,
		0.0f, 0.0f, -NearZ * DepthScale, 1.0f);
}

FMatrix UCameraComponent::GetPerspectiveProjectionMatrix() const
{
	//시야각, 가로세로 비율,  가시경계 범위 체크
	assert(std::isfinite(FOV) && FOV > 0.0f && FOV < PI);
	assert(std::isfinite(AspectRatio) && AspectRatio > 0.0f);
	assert(std::isfinite(NearZ) && std::isfinite(FarZ) && NearZ > 0.0f && FarZ > NearZ);

	const float VerticalScale = 1.0f / std::tan(FOV * 0.5f);
	const float HorizontalScale = VerticalScale / AspectRatio;
	const float DepthScale = FarZ / (FarZ - NearZ);

	//일반적인 투영행렬과 다른이유 : 기준 축이 달라서 축변환 적용
	return FMatrix(
		0.0f, 0.0f, DepthScale, 1.0f,
		HorizontalScale, 0.0f, 0.0f, 0.0f,
		0.0f, VerticalScale, 0.0f, 0.0f,
		0.0f, 0.0f, -NearZ * DepthScale, 0.0f);
}
