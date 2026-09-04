#pragma once

//벡터, 행렬 구조체 선언

typedef int int32;
typedef unsigned int uint32;

struct FVector
{
	float X;
	float Y;
	float Z;
	float Dot(const FVector& rhs);
	FVector Cross(const FVector& rhs);
	float Length() const;
	void Normalize();
	FVector(float _x = 0, float _y = 0, float _z = 0) : X(_x), Y(_y), Z(_z) {}

};

struct FVector4
{
	float X;
	float Y;
	float Z;
	float W;
	float Dot(const FVector4& Other);
	float Length();
	float Length3();
	//...
};

struct FMatrix
{
	float M[4][4];
	static const FMatrix Identity;

	FMatrix Transpose() const
	{
		FMatrix Result;
		for (int Row = 0; Row < 4; ++Row)
		{
			for (int Col = 0; Col < 4; ++Col)
			{
				Result.M[Row][Col] = M[Col][Row];
			}
		}
		return Result;
	}
};