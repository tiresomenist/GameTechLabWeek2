#pragma once

#include "Engine/GEngine.h"
#include "Container/TArray.h"

class USceneComponent;
class UGizmo;

class FEditor
{
private:
	// 현재 선택된 SceneComponent;
	USceneComponent* SelectedSceneComponent;
	TArray<UGizmo*> Gizmos;

public:

	void Initialize();

	void Tick();

	void Release();

	USceneComponent* GetSelectedSceneComponent() const { return SelectedSceneComponent; };
	void SetSelectedSceneComponent(USceneComponent* Component);

};