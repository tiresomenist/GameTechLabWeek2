#pragma once

#include <cmath>
#include <cassert>
#include <algorithm>
#include "Engine/UEngineStatics.h"

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


	float Dot(const FVector& rhs)const;
	FVector Cross(const FVector& rhs)const;


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
	float Dot(const FVector4& Other)const;
	float LengthSquared()const;
	float Length()const;
	float LengthSqured3()const;
	float Length3()const;
	FVector4(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 0.0f) : X(_x), Y(_y), Z(_z), W(_w) {}
};