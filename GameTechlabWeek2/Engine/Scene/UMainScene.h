#pragma once

#include "Engine/Scene/UScene.h"

////////////////
// UMainScene //
////////////////
class UMainScene : public UScene
{
    UCLASS(UMainScene, "MainScene", UScene)

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay() override;

};
