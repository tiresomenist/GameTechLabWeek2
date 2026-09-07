#include "File.h"

#include <iostream>
#include <fstream>
#include <sstream>

// TODO: 적절한 예외 처리가 언젠간 필요할 것

void File::WriteText(FStringView Path, FStringView Text)
{
	FString PathString{ Path };

	std::ofstream Out{ PathString };

	if (!Out.is_open()) { return; }

	Out << Text;

	Out.close();
}

FString File::ReadText(FStringView Path)
{
	FString PathString{ Path };

	std::ifstream In{ PathString };
	std::stringstream StringStream;

	if (!In.is_open()) { return FString{}; }

	FString Text;

	StringStream << In.rdbuf();

	Text = StringStream.str();

	In.close();

	return Text;
}
