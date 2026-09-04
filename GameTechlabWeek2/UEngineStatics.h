#pragma once

//전역으로 쓸 스태틱 변수들 모아놓는 클래스/현재는 cpp없음.

typedef int int32;
typedef unsigned int uint32;



class UEngineStatics
{
public:
	static constexpr float Epsilon = 1.0e-7f;
	static uint32 GenUUID()
	{
		return NextUUID++;
	}
	static uint32 NextUUID;
};