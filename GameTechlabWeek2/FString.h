#pragma once

#include <string>

class FString
{
private:
	std::string String;

public:
	FString(std::string_view InString);

};