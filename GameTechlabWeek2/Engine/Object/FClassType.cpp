#include "FClassType.h"

FClassType::FClassType(const FString& InName, const Constructor InClassConstructor, const EType InType)
	: Name{ InName }
	, ClassConstructor{ InClassConstructor }
	, Type{ InType }
{
}
