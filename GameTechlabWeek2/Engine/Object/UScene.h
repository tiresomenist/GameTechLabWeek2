#pragma once
#include "UObject.h"
#include "UCameraComponent.h"

class UPrimitiveComponent;

class UScene : public UObject
{
public:
    void Update(float DeltaTime);
	const std::vector<UPrimitiveComponent*>& GetPrimitiveComponents() const;

	UCameraComponent* GetCamera() const { return MainCamera; }
	void SetCamera(UCameraComponent* InCamera) { MainCamera = InCamera; }

private:
	std::vector<UPrimitiveComponent*> PrimitiveComponents;
	UCameraComponent* MainCamera = nullptr;
};
