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

	//template<typename T>
	//T* SpawnPrimitive();
	//T* SpawnActor()

protected:
	TArray<UPrimitiveComponent*> PrimitiveComponents {};
	UCameraComponent* MainCamera = nullptr;
};


////////////////
// UMainScene //
////////////////
class UMainScene : public UScene
{
public:
	virtual void Initialize() override;
	virtual void Update(float DeltaTime) override;

private:
	TArray<UPrimitiveComponent*> SelectedPrimitives; // Actor
};