#include "USphereComp.h"
#include "../../../Container/TArray.h"
#include "../../../FVertexSimple.h"
#include "../../GResourceManager.h"
#include "../FObjectFactory.h"

FClassType* USpherePrimitive::GetClass()
{
	static auto CreateObject = [](uint32 UUID, uint32 InternalIndex, FClassType* InClassType)
		{
			return new USpherePrimitive(UUID, InternalIndex, InClassType);
		};

	static FClassType Type{ "USpherePrimitive", CreateObject, UPrimitiveComponent::GetClass() };
	return &Type;
}
