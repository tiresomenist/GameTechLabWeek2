#include "GSceneManager.h"
#include "Engine/Object/FObjectFactory.h"
#include "Engine/Scene/UMainScene.h"

GSceneManager* GSceneManager::GetInstance()
{
	static GSceneManager* SceneManager = new GSceneManager();
	return SceneManager;
}

void GSceneManager::Initialize()
{
	UObject* RawPtr = FObjectFactory::ConstructObject(UMainScene::GetClass());
	CurrentScene = static_cast<UScene*>(RawPtr);

	if (CurrentScene)
	{
		CurrentScene->BeginPlay();
	}
}

void GSceneManager::Release()
{
	if (CurrentScene)
	{
		CurrentScene->EndPlay();

		delete CurrentScene;
		CurrentScene = nullptr;
	}
}

void GSceneManager::Tick(float DeltaTime)
{
	if (CurrentScene)
	{
		CurrentScene->Tick(DeltaTime);
	}

	if (NextScene)
	{
		if (CurrentScene)
		{
			CurrentScene->EndPlay();

			delete CurrentScene;
			CurrentScene = nullptr;
		}

		CurrentScene = NextScene;
		NextScene = nullptr;

		CurrentScene->BeginPlay();
	}
}

void GSceneManager::ChangeLevel(UScene* InNextScene)
{
	NextScene = InNextScene;
}
