#pragma once
#include "UObject.h"
#include "UCameraComponent.h"
#include "../../Container/TArray.h"

class UPrimitiveComponent;

class UScene : public UObject
{
public:
	virtual void Initialize() {};
    virtual void Update(float DeltaTime);

	const TArray<UPrimitiveComponent*>& GetPrimitiveComponents() const;

	UCameraComponent* GetCamera() const { return MainCamera; }
	void SetCamera(UCameraComponent* InCamera) { MainCamera = InCamera; }

	template<typename T>
	T* SpawnPrimitive();
	//T* SpawnActor()

private:
	TArray<UPrimitiveComponent*> PrimitiveComponents {};
	UCameraComponent* MainCamera = nullptr;
};


//////////////////
// UEditorScene //
//////////////////
class UEditorScene : public UScene
{
private:
	TArray<UPrimitiveComponent*> SelectedPrimitives; // Actor
};