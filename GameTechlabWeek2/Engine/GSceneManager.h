#pragma once

class UScene;

// Singleton
class GSceneManager
{
public:
	static GSceneManager* GetInstance();

	void Initialize();

	void Start();
	void Tick();
	void End();

	void ChangeLevel();

private:

	UScene* CurrentScene = nullptr;

	// 싱글톤
	GSceneManager() = default;
	~GSceneManager() = default;
	GSceneManager(const GSceneManager&) = delete;
	GSceneManager& operator=(const GSceneManager&) = delete;
};

