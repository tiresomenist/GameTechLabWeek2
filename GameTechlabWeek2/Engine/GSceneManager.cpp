#include "GSceneManager.h"
#include "Container/FString.h"
#include "Engine/Object/FArchive.h"
#include "Engine/Object/FObjectFactory.h"
#include "Engine/Scene/UMainScene.h"
#include "Engine/Util/File.h"
#include "SimpleJSON.hpp"

GSceneManager* GSceneManager::GetInstance()
{
	static GSceneManager* SceneManager = new GSceneManager();
	return SceneManager;
}

void GSceneManager::Initialize()
{
	LoadScene(UMainScene::GetClass(), "TestScene");
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

void GSceneManager::LoadScene(FClassType* SceneType, FStringView SerializedName)
{
	// UScene의 자식인지 체크
	if (!SceneType->IsA(UScene::GetClass())) { return; }

	UObject* RawPtr = FObjectFactory::ConstructObject(SceneType);
	UScene* Scene = static_cast<UScene*>(RawPtr);

	if (SerializedName != "")
	{
		// TODO: 적절한 예외처리가 없음
		FString FileName{ SerializedName };
		FileName += ".json";

		FString FileText = File::ReadText(FileName);
		json::JSON FileJSON = json::JSON::Load(FileText);

		TArray<FArchive> ObjectInfoList;

		json::JSON& List = FileJSON["Primitives"];
		for (auto& Item : List.ObjectRange())
		{
			uint32 UUID = std::stoi(Item.first);
			FArchive Archive{ Item.second };
			Archive.SetUInt32("UUID", UUID);

			ObjectInfoList.Add(Archive);
		}

		Scene->Deserialize(ObjectInfoList);
	}

	if (CurrentScene)
	{
		NextScene = Scene;
	}
	else
	{
		CurrentScene = Scene;
		CurrentScene->BeginPlay();
	}
}

void GSceneManager::SaveScene(FStringView SerializedName)
{
	if (CurrentScene == nullptr) { return; }
	if (SerializedName == "") { return; }

	// TODO: 적절한 예외처리가 없음
	TArray<FArchive> ObjectInfoList;
	CurrentScene->Serialize(ObjectInfoList);
	
	json::JSON ObjectArray;

	for (auto& Item : ObjectInfoList)
	{
		FString UUID = std::to_string(Item.GetUInt32("UUID"));
		ObjectArray[UUID] = Item.GetJSON();
	}

	json::JSON FileJSON;
	FileJSON["Version"] = 1;
	FileJSON["NextUUID"] = 100; // TODO: 수정!!!
	FileJSON["Primitives"] = ObjectArray;

	FString FileName{ SerializedName };
	FileName += ".json";

	FString FileText = FileJSON.dump();
	File::WriteText(FileName, FileText);
}
