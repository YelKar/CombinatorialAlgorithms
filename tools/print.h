#pragma once
#include <iostream>
#include <vector>
#include <sstream>

namespace tools {
    template <typename T>
    std::stringstream RenderArray(std::vector<T> arr) {
        std::stringstream out;
        for (T a : arr) {
            out << a << " ";
        }
        return out;
    }
	template <typename T>
	std::stringstream RenderArray(T* arr, std::size_t size) {
		std::stringstream out;
		for (std::size_t i = 0; i < size; i++) {
			out << arr[i] << " ";
		}
		return out;
	}
	template <typename T>
	void PrintArray(std::vector<T> arr) {
		std::cout << RenderArray(arr).str() << std::endl;
	}
	template <typename T>
	void PrintArray(T* arr, std::size_t size) {
		std::cout << RenderArray(arr, size).str() << std::endl;
	}
}
