#pragma	once
#include <vector>
#include <stdexcept>


#include <vector>
#include <stdexcept>

template<typename T>
class TArray
{
private:
	std::vector<T> Array;
public:
	void Add(const T& Element)
	{
		Array.push_back(Element);
	}

	void Empty() { Array.clear(); }

	bool IsEmpty() const { return Array.empty(); }

	T Pop() {
		if (Array.empty()) throw std::runtime_error("Stack empty");
		T Top = Array.back();
		Array.pop_back();
		return Top;
	}

	int Num() const { return Array.size(); }

	void RemoveAt(size_t Index) { Array.erase(Array.begin() + Index); }

	T& operator[](size_t Index) { return Array[Index]; }
	const T& operator[](size_t Index) const { return Array[Index]; }

	auto begin() { return Array.begin(); }
	auto end() { return Array.end(); }

	
};