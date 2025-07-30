#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <ranges>
#include <algorithm>
#include "print.h"


namespace tools {
    template<typename T>
    void ParseMatrix(const std::string& path, std::vector<std::vector<T>>& mtx) {
        std::ifstream inFile;
        inFile.open(path);
        if (inFile.fail()) {
            std::cerr << "FILE " << path << ": " << strerror(errno) << std::endl;
            exit(1);
        }
        mtx.clear();
        std::string line;
        for (;!inFile.eof();) {
            std::vector<T> mtxRow;
            std::getline(inFile, line);
            std::string num;
            for (char c : line) {
                if ('0' <= c && c <= '9') {
                    num += c;
                }
                if (c == ' ' && !num.empty()) {
                    mtxRow.push_back(stoi(num));
                    num = "";
                }
            }
            mtxRow.push_back(stoi(num));
            mtx.push_back(mtxRow);
        }
    }

    template<typename T>
    void PrintMatrix(const std::vector<std::vector<T>>& mtx) {
        if (mtx.empty() || mtx[0].empty()) {
            return;
        }
        for (const std::vector<T>& mtxRow : mtx) {
            std::cout << "| " << RenderArray(mtxRow, " | ").str() << "|\n";
        }
    }
}
