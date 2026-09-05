#pragma once
#include "Container/TArray.h"
#include "Engine/Object/UObject.h"
#include "Engine/Object/FObjectFactory.h"

class UCameraComponent;
class UPrimitiveComponent;

class UScene : public UObject
{
protected:
	UScene(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

public:
	static FClassType* GetClass();

	virtual void BeginPlay();

    virtual void Tick(float DeltaTime);

	virtual void EndPlay();

	UCameraComponent* GetMainCamera() const { return MainCamera; }
	void SetMainCamera(UCameraComponent* InCamera) { MainCamera = InCamera; }

	void CreateMainCamera();

	template <typename T>
	T SpawnObject(FClassType* Type)
	{
		return Cast<T>(FObjectFactory::ConstructObject(Type));
	}

	template <typename T>
	T Cast(UObject* Object)
	{
		T Ptr = static_cast<T>(Object);
		return Ptr;
	}

private:

	/// <summary>
	/// Scene에 종속된 "모든" UObject를 담는 멤버 변수
	/// </summary>
	TArray<UObject*> Objects {};
	
	/// <summary>
	/// Scene의 렌더링을 담당할 MainCamera를 담는 멤버 변수
	/// </summary>
	UCameraComponent* MainCamera = nullptr;
};
