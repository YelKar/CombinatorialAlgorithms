#pragma once
#include <iostream>
#include <vector>
#include <sstream>

namespace tools {

template <typename T>
std::stringstream RenderArray(T* arr, std::size_t size, std::string sep = " ") {
	std::stringstream out;
	for (std::size_t i = 0; i < size; ++i) {
		if constexpr (std::is_arithmetic_v<T>) {
			if (arr[i] == std::numeric_limits<T>::max()) out << "∞";
			else if constexpr (std::is_signed_v<T>) {
				out << (arr[i] == std::numeric_limits<T>::min() ? "-∞" : std::to_string(arr[i]));
			} else out << arr[i];
		} else out << arr[i];

		if (i + 1 < size) out << sep;
	}
	return out;
}
template <typename T>
std::stringstream RenderArray(std::vector<T> arr, std::string sep = " ") {
	return RenderArray(arr.data(), arr.size(), sep);
}
template <typename T>
void PrintArray(std::vector<T> arr, std::string sep = " ", std::string end = "\n") {
	std::cout << RenderArray(arr, sep).str() << end;
}
template <typename T>
void PrintArray(T* arr, std::size_t size, std::string sep = " ", std::string end = "\n") {
	std::cout << RenderArray(arr, size, sep).str() << end;
}

namespace ArrayStreams {
template <typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> arr) {
    out << RenderArray(arr).str();
    return out;
}
}
}
