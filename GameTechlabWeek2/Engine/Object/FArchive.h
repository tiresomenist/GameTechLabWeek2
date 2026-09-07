#pragma once

#include "Container/FString.h"
#include "Container/TArray.h"
#include "Engine/Core.h"
#include <type_traits>

#include "SimpleJSON.hpp"

// TODO: 언젠가는 이 코드가 JSON에 강하게 커플링 되어있는 문제를 해결해야할지도

class FArchive
{
private:
	json::JSON Object;

public:
	FArchive();
	FArchive(json::JSON& InObject);

	json::JSON GetJSON() const { return Object; }

	int32 GetInt32(const FString& Key);
	void SetInt32(const FString& Key, int32 Value);

	float GetFloat(const FString& Key);
	void SetFloat(const FString& Key, float Value);

	uint32 GetUInt32(const FString& Key);
	void SetUInt32(const FString& Key, uint32 Value);

	double GetDouble(const FString& Key);
	void SetDouble(const FString& Key, double Value);

	bool GetBool(const FString& Key);
	void SetBool(const FString& Key, bool Value);
	
	FString GetString(const FString& Key);
	void SetString(const FString& Key, const FString& Value);
	
	template <typename T>
	TArray<T> GetArray(const FString& Key) = delete;
	
	template <>
	TArray<float> GetArray<float>(const FString& Key);

	// GetArray는 필요하면 더 추가
	
	template <typename T>
	void SetArray(const FString& Key, TArray<T>& Value)
	{
		Object[Key] = json::Array();

		for (int i = 0; i < Value.Num(); ++i)
		{
			Object[Key][i] = Value[i];
		}
	}
};

template<>
inline TArray<float> FArchive::GetArray(const FString& Key)
{
	TArray<float> Array;

	for (auto& Item : Object[Key].ArrayRange())
	{
		double Value = Item.ToFloat();
		Array.Add(static_cast<float>(Value));
	}

	return Array;
}