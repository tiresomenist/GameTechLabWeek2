#pragma once

#include "Container/FString.h"
#include "Container/TArray.h"
#include "Engine/Core.h"
#include <type_traits>

#include "nlohmann/json.hpp"

// TODO: 언젠가는 이 코드가 JSON에 강하게 커플링 되어있는 문제를 해결해야할지도

class FArchive
{
private:
	nlohmann::json Object;
	static double GetFixedDouble(double Value);

public:
	FArchive();
	explicit FArchive(const nlohmann::json& InObject);

	nlohmann::json GetJSON() const { return Object; }

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
	
	// GetArray는 필요하면 더 추가
	template <typename T>
	TArray<T> GetArray(const FString& Key) = delete;
	
	template <>
	TArray<float> GetArray<float>(const FString& Key)
	{
		TArray<float> Array;

		for (const auto& Item : Object.at(Key))
		{
			float Value = Item.get<float>();
			Array.Add(Value);
		}

		return Array;
	}

	template <typename T>
	void SetArray(const FString& Key, TArray<T>& Value)
	{
		Object[Key] = nlohmann::json::array();

		for (int i = 0; i < Value.Num(); ++i)
		{
			if constexpr (std::is_floating_point_v<T>)
			{
				Object[Key].push_back(GetFixedDouble(static_cast<double>(Value[i])));
			}
			else
			{
				Object[Key].push_back(Value[i]);
			}
		}
	}
};
