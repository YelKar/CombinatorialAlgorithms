#pragma once
#include <iostream>
#include <vector>
#include <sstream>

namespace tools {

template <typename T>
std::stringstream RenderArray(std::vector<T> arr, std::string sep = " ") {
    std::stringstream out;
    for (T a : arr) {
        out << a << sep;
    }
    return out;
}
template <typename T>
std::stringstream RenderArray(T* arr, std::size_t size, std::string sep = " ") {
	std::stringstream out;
	for (std::size_t i = 0; i < size; i++) {
		out << arr[i] << sep;
	}
	return out;
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
