#include "RenderUtil.h"
#include "Engine/Renderer/FPrimitiveRenderData.h"
#include "Engine/Object/Primitive/UPrimitiveComponent.h"
#include "Engine/Scene/UScene.h"

TArray<FPrimitiveRenderData> RenderUtil::GetRenderList(UScene* Scene)
{
	TArray<FPrimitiveRenderData> RenderList;

	for (auto Item : Scene->Objects)
	{
		if (Item->IsA(UPrimitiveComponent::GetClass()))
		{
			UPrimitiveComponent* Primitive = static_cast<UPrimitiveComponent*>(Item);
			RenderList.Add(Primitive->GetRenderData());
		}
	}

	return RenderList;
}
