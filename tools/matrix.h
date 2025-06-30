#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>


namespace tools {
    void parseMatrix(const std::string& path, std::vector<std::vector<int>>& mtx) {
        std::ifstream inFile;
        inFile.open(path);
        if (inFile.fail()) {
            std::cerr << "FILE " << path << ": " << strerror(errno) << std::endl;
            exit(1);
        }
        mtx.clear();
        std::string line;
        for (;!inFile.eof();) {
            std::vector<int> mtxRow;
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

    void printMatrix(const std::vector<std::vector<int>>& mtx) {
        for (const std::vector<int>& mtxRow : mtx) {
            for (const int num : mtxRow) {
                printf("| %2d ", num);
            }
            std::cout << "|" << std::endl;
        }
    }
}
