#pragma once
#include "Windows.h"
#include "FRenderer.h"

#include "Core.h"

class GEngine
{
public:
	static GEngine* GetInstance();

	void Initialize(HWND d);

	void Tick();

	void Destroy();

private:
	float LastTickTime = 0;
	
	FRenderer r;

	// 싱글톤
	GEngine() = default;
	~GEngine() = default;
	GEngine(const GEngine&) = delete;
	GEngine& operator=(const GEngine&) = delete;

};

