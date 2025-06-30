#include <algorithm>
#include "timer.h"
#include "print.h"
#include "matrix.h"

#include <limits>

int main(int argc, char *argv[]) {
    tools::Timer timer;
    int countOfPoints = 0;
    std::vector<std::vector<int>> distanceMtx;
    std::vector<std::vector<int>> volumeMtx;

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <count of points> <distance matrix file> <volume matrix file>" << std::endl;
        return 1;
    } else {
        countOfPoints = atoi(argv[1]);
        tools::parseMatrix(argv[2], distanceMtx);
        tools::parseMatrix(argv[3], volumeMtx);
    }

    std::vector<int> permArr = {};
    for (int i = 0; i < countOfPoints; i++) {
        permArr.push_back(i);
    }

    std::cout << "Расстояния:" << std::endl;
    tools::printMatrix(distanceMtx);


    std::cout << std::endl << "Потоки товаров:" << std::endl;
    tools::printMatrix(volumeMtx);

    int minGraphValue = std::numeric_limits<int>::max();
    std::vector<int> minGraphPerm = {};

    timer.start();

    do {
        int sumValue = 0;
        for (int i = 0; i < countOfPoints; i++) {
            for (int j = i + 1; j < countOfPoints; j++) {
                sumValue += distanceMtx[i][j] * volumeMtx[permArr[i]][permArr[j]];
                sumValue += distanceMtx[j][i] * volumeMtx[permArr[j]][permArr[i]];
            }
        }

        if (sumValue < minGraphValue) {
            minGraphValue = sumValue;
            minGraphPerm.clear();
            std::copy(permArr.begin(), permArr.end(), back_inserter(minGraphPerm));
        }

//        std::cout << tools::renderArr(permArr).str() << " " << sumValue << std::endl;
    } while (std::next_permutation(permArr.begin(), permArr.end()));

    auto delta = timer.getDelta();
    std::cout << delta.toString() << std::endl;

    std::cout << "Результат: " << minGraphValue << std::endl;
    std::cout << "Размещение: " << tools::renderArr(minGraphPerm).str() << std::endl;
    std::cout << "Время выполнения для " << countOfPoints << " точек: " << delta.getSeconds() << std::endl;

    std::cout << std::endl;

    auto calculatedTime = delta;

    int i = countOfPoints + 1;
    for (; i <= 20; i++) {
        calculatedTime *= i;
    }
    std::cout << "Расчётное время для 20 точек: " << calculatedTime.toString() << std::endl;

    for (;i <= 50; i++) {
        calculatedTime *= i;
    }
    std::cout << "Расчётное время для 50 точек: " << calculatedTime.toString() << std::endl;
    return 0;
}


