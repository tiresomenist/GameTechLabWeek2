#pragma once

#include "Core.h"

class GEngine
{
public:
	static GEngine* GetInstance();

	void Initialize();

	void Tick();

	void Destroy();

private:
	float LastTickTime = 0;
	
	// 싱글톤
	GEngine() = default;
	~GEngine() = default;
	GEngine(const GEngine&) = delete;
	GEngine& operator=(const GEngine&) = delete;

};

