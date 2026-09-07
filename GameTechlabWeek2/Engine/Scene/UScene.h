#pragma once
#include "Container/TArray.h"
#include "Engine/Object/UObject.h"
#include "Engine/Object/FObjectFactory.h"
#include "Engine/Renderer/RenderUtil.h"
#include "../Object/Primitive/UPrimitiveComponent.h"

struct FPrimitiveRenderData;
struct UCameraComponent;
class FRenderer;

class UScene : public UObject
{

	UCLASS(UScene, "Scene", UObject)

public:
	virtual void BeginPlay();

    virtual void Tick(float DeltaTime);

	virtual void EndPlay();

	UCameraComponent* GetMainCamera() const { return MainCamera; }
	void SetMainCamera(UCameraComponent* InCamera) { MainCamera = InCamera; }

	void CreateMainCamera();

	template <typename T>
	T SpawnObject(FClassType* Type)
	{
		UObject* Object = FObjectFactory::ConstructObject(Type);
		Objects.Add(Object);

		return Cast<T>(Object);
	}

	template <typename T>
	T Cast(UObject* Object)
	{
		T Ptr = static_cast<T>(Object);
		return Ptr;
	}

	void Destroy(UObject* Object);
    void RenderGizmos(FRenderer& Renderer);

	//외부에서 Primitive 접근 제공
	template <typename Func>
	void ForEachPrimitive(Func&& Function) const
	{
		for (UObject* Object : Objects)
		{
			if (Object->IsA(UPrimitiveComponent::GetClass()))
			{
				Function(
					static_cast<UPrimitiveComponent*>(Object)
				);
			}
		}
	}

	virtual ~UScene();

protected:

	/// <summary>
	/// Scene에 종속된 "모든" UObject를 담는 멤버 변수
	/// </summary>
	TArray<UObject*> Objects {};
	
	/// <summary>
	/// Scene의 렌더링을 담당할 MainCamera를 담는 멤버 변수
	/// </summary>
	UCameraComponent* MainCamera = nullptr;

public:
	friend TArray<FPrimitiveRenderData> RenderUtil::GetRenderList(UScene* Scene);
};
