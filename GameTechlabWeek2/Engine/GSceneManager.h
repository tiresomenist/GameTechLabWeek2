#pragma once

class UScene;

// Singleton
class GSceneManager
{
public:
	static GSceneManager* GetInstance();

	void Initialize();
	void Release();

	void Tick(float DeltaTime);

	void ChangeLevel(UScene* InNextScene);

private:

	UScene* CurrentScene = nullptr;
	UScene* NextScene = nullptr;

	// 싱글톤
	GSceneManager() = default;
	~GSceneManager() = default;
	GSceneManager(const GSceneManager&) = delete;
	GSceneManager& operator=(const GSceneManager&) = delete;
};

