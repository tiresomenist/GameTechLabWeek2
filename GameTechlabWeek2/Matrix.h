#pragma once

#include <cmath>
#include <cassert>
#include <algorithm>
#include "UEngineStatics.h"

//벡터, 행렬 구조체 선언

struct FVector
{
	//거의 동일한 값 비교, 디비전 바이 제로 처리 안됨
	float X;
	float Y;
	float Z;

	static const FVector Zero;
	static const FVector Forward;
	static const FVector Right;
	static const FVector Up;

	FVector operator+(const FVector& rhs) const;
	FVector operator-(const FVector& rhs) const;
	FVector operator*(float scalar) const;
	FVector operator/(float scalar) const;

	FVector& operator+=(const FVector& rhs);
	FVector& operator-=(const FVector& rhs);
	FVector& operator*=(float scalar);
	FVector& operator/=(float scalar);


	float Dot(const FVector& rhs);
	FVector Cross(const FVector& rhs);


	float Length() const;
	float LengthSquared() const;

	float Distance(const FVector& rhs) const;

	FVector GetNormalized() const;
	void Normalize();
	FVector(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : X(_x), Y(_y), Z(_z) {}

};

struct FVector4
{
	float X;
	float Y;
	float Z;
	float W;
	float Dot(const FVector4& Other);
	float LengthSquared();
	float Length();
	float LengthSqured3();
	float Length3();
	FVector4(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f) : X(_x), Y(_y), Z(_z), W(_w) {}
};

struct FMatrix
{
	//==================
	//문서에는 직교행렬, 정규 직교행렬 등을 구현하라고 하는데..
	//==================
	//M[행][열]
	float M[4][4];

	// 단위행렬
	static const FMatrix Identity;

	//행렬곱
	FMatrix operator*(const FMatrix& Rhs) const;
	//벡터*행렬
	FVector4 TransformVector4(const FVector4& V) const;

	//전치행렬,역행렬,행렬식
	FMatrix Transpose() const;
	//역행렬 시도.
	bool TryInverse(FMatrix& OutInverse) const;
	FMatrix Inverse() const;
	float Determinant() const;

	// 축 위치 추출
	FVector GetAxis(int32 AxisIndex) const; // 0: X축, 1: Y축, 2: Z축
	FVector GetOrigin() const;
	// 정규 행렬
	FMatrix NormalMatrix() const;

	FMatrix(float m00 = 1.0f, float m01 = 0.0f, float m02 = 0.0f, float m03 = 0.0f,
		float m10 = 0.0f, float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f,
		float m20 = 0.0f, float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f,
		float m30 = 0.0f, float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f)
	{
		M[0][0] = m00; M[0][1] = m01; M[0][2] = m02; M[0][3] = m03;
		M[1][0] = m10; M[1][1] = m11; M[1][2] = m12; M[1][3] = m13;
		M[2][0] = m20; M[2][1] = m21; M[2][2] = m22; M[2][3] = m23;
		M[3][0] = m30; M[3][1] = m31; M[3][2] = m32; M[3][3] = m33;
	}


};

FVector4 operator*(
	//실제 연산은 FMatrix::TransformVector4에서 수행
	const FVector4& V,
	const FMatrix& Matrix);