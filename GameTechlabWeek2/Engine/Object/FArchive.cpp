#include "FArchive.h"

#include <utility>

FArchive::FArchive()
	: Object{}
{
}

FArchive::FArchive(json::JSON& InObject)
	: Object{ InObject }
{
}

int32 FArchive::GetInt32(const FString& Key)
{
	return Object[Key].ToInt();
}

void FArchive::SetInt32(const FString& Key, int32 Value)
{
	Object[Key] = Value;
}

float FArchive::GetFloat(const FString& Key)
{
	return static_cast<float>(Object[Key].ToFloat());
}

void FArchive::SetFloat(const FString& Key, float Value)
{
	Object[Key] = Value;
}

uint32 FArchive::GetUInt32(const FString& Key)
{
	return static_cast<uint32>(Object[Key].ToInt());
}

void FArchive::SetUInt32(const FString& Key, uint32 Value)
{
	Object[Key] = Value;
}

double FArchive::GetDouble(const FString& Key)
{
	return Object[Key].ToFloat();
}

void FArchive::SetDouble(const FString& Key, double Value)
{
	Object[Key] = Value;
}

bool FArchive::GetBool(const FString& Key)
{
	return Object[Key].ToBool();
}

void FArchive::SetBool(const FString& Key, bool Value)
{
	Object[Key] = Value;
}

FString FArchive::GetString(const FString& Key)
{
	return Object[Key].ToString();
}

void FArchive::SetString(const FString& Key, const FString& Value)
{
	Object[Key] = Value;
}