#include "FArchive.h"

#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

double FArchive::GetFixedDouble(double Value)
{
	constexpr double Scale = 1000000.0;

	// 오버플로우 방지
	if (std::abs(Value) > std::numeric_limits<double>::max() / Scale)
	{
		return Value;
	}

	double Rounded = std::round(Value * Scale) / Scale;
	return Rounded == 0.0 ? 0.0 : Rounded;
}

FArchive::FArchive()
	: Object()
{
}

FArchive::FArchive(const nlohmann::json& InObject)
	: Object(InObject)
{
}

int32 FArchive::GetInt32(const FString& Key)
{
	return Object.at(Key).get<int32>();
}

void FArchive::SetInt32(const FString& Key, int32 Value)
{
	Object[Key] = Value;
}

float FArchive::GetFloat(const FString& Key)
{
	return Object.at(Key).get<float>();
}

void FArchive::SetFloat(const FString& Key, float Value)
{
	Object[Key] = GetFixedDouble(static_cast<double>(Value));
}

uint32 FArchive::GetUInt32(const FString& Key)
{
	return Object.at(Key).get<uint32>();
}

void FArchive::SetUInt32(const FString& Key, uint32 Value)
{
	Object[Key] = Value;
}

double FArchive::GetDouble(const FString& Key)
{
	return Object.at(Key).get<double>();
}

void FArchive::SetDouble(const FString& Key, double Value)
{
	Object[Key] = GetFixedDouble(Value);
}

bool FArchive::GetBool(const FString& Key)
{
	return Object.at(Key).get<bool>();
}

void FArchive::SetBool(const FString& Key, bool Value)
{
	Object[Key] = Value;
}

FString FArchive::GetString(const FString& Key)
{
	return Object.at(Key).get<FString>();
}

void FArchive::SetString(const FString& Key, const FString& Value)
{
	Object[Key] = Value;
}
