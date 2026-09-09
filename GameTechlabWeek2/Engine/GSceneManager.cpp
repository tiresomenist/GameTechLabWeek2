#include "GSceneManager.h"
#include "Container/FString.h"
#include "Engine/Object/FArchive.h"
#include "Engine/Object/FObjectFactory.h"
#include "Engine/Object/GObjectStatics.h"
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
	LoadScene(UMainScene::GetClass(), "");
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
		InternalLoadScene();
	}
}

void GSceneManager::LoadScene(FClassType* SceneType, FStringView SerializedName)
{
	NextScene = SceneType;
	NextSceneFile = SerializedName;

	if (!CurrentScene)
	{
		InternalLoadScene();
	}
}

void GSceneManager::InternalLoadScene()
{
	// UScene의 자식인지 체크
	if (!NextScene->IsA(UScene::GetClass())) { return; }

	// 기존 Scene Unload
	if (CurrentScene)
	{
		CurrentScene->EndPlay();
		delete CurrentScene;
		CurrentScene = nullptr;
	}

	TArray<FArchive> ObjectInfoList;
	GObjectStatics::SetNextUUID(EObjectDomain::EOT_Scene, 0);

	// 주어진 파일이 없다면 Deserialize 단계 생략
	if (NextSceneFile.empty())
	{
		UObject* RawPtr = FObjectFactory::ConstructEngineObject(NextScene);
		CurrentScene = static_cast<UScene*>(RawPtr);
	}
	else
	{
		// 직렬화된 파일 불러오기
		// TODO: 적절한 예외처리가 없음
		FString FileName{ NextSceneFile };
		FileName += ".json";

		FString FileText = File::ReadText(FileName);
		json::JSON FileJSON = json::JSON::Load(FileText);

		// GObjectStatics 초기화
		uint32 NextUUID = FileJSON["NextUUID"].ToInt();
		GObjectStatics::SetNextUUID(EObjectDomain::EOT_Scene, NextUUID);

		UObject* RawPtr = FObjectFactory::ConstructEngineObject(NextScene);
		CurrentScene = static_cast<UScene*>(RawPtr);

		json::JSON& List = FileJSON["Primitives"];
		for (auto& Item : List.ObjectRange())
		{
			uint32 UUID = std::stoi(Item.first);
			FArchive Archive{ Item.second };
			Archive.SetUInt32("UUID", UUID);

			ObjectInfoList.Add(Archive);
		}
	}

	CurrentScene->Deserialize(ObjectInfoList);
	CurrentScene->BeginPlay();


	NextScene = nullptr;
	NextSceneFile = "";
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

	uint32 NextUUID = GObjectStatics::GetNextUUID(EObjectDomain::EOT_Scene);

	json::JSON FileJSON;
	FileJSON["Version"] = 1;
	FileJSON["NextUUID"] = NextUUID;
	FileJSON["Primitives"] = ObjectArray;

	FString FileName{ SerializedName };
	FileName += ".json";

	FString FileText = FileJSON.dump();
	File::WriteText(FileName, FileText);
}
