#include "FClassType.h"

FClassType::FClassType(const FString& InName, const Constructor InClassConstructor, const FClassType* InParentClassType)
	: Name{ InName }
	, ClassConstructor{ InClassConstructor }
	, ParentClassType{ InParentClassType }
{
}
