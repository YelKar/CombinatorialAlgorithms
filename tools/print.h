#pragma once
#include <iostream>
#include <vector>
#include <sstream>

namespace tools {
    template <typename T>
    std::stringstream renderArr(std::vector<T> arr) {
        std::stringstream out;
        for (T a : arr) {
            out << a << " ";
        }
        return out;
    }
}
