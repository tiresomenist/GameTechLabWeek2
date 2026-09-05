#pragma once
#include "Windows.h"
#include "FRenderer.h"

#include "Core.h"

class FConsole;

class GEngine
{
public:
	static GEngine* GetInstance();

	void Initialize(HWND InHwnd);

	void Tick();

	void Destroy();

	FConsole* GetConsole() const { return Console; };

private:
	float LastTickTime = 0;

	FRenderer Renderer;
	FConsole* Console;

	// 싱글톤
	GEngine() = default;
	~GEngine() = default;
	GEngine(const GEngine&) = delete;
	GEngine& operator=(const GEngine&) = delete;
};
