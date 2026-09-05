#pragma once

#include "Engine/Scene/UScene.h"

////////////////
// UMainScene //
////////////////
class UMainScene : public UScene
{
protected:
	UMainScene(uint32 InUUID, uint32 InInternalIndex, FClassType* InClassType);

public:
	static FClassType* GetClass();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay() override;

private:
	UPrimitiveComponent* TestPrimitive = nullptr; // Actor
};
