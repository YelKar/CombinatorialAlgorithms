#include <gtest/gtest.h>
#include "Knapsack.h"
#include "print.h"
#include <cmath>
#include <ranges>

using Things = std::vector<Knapsack::Thing>;
class Tests : public ::testing::TestWithParam<std::tuple<int, int, int, Things>> {};

TEST_P(Tests, Check) {
	auto [capacity, expectedResultWeight, expectedResultValue, things] = GetParam();
	Knapsack::Knapsack knapsack(capacity);
	Knapsack::Pack(knapsack, things);
	EXPECT_EQ(knapsack.weight, expectedResultWeight) << tools::RenderArray(knapsack.things).str();
	EXPECT_EQ(knapsack.value, expectedResultValue) << tools::RenderArray(knapsack.things).str();
}

INSTANTIATE_TEST_SUITE_P(
	Cases,
	Tests,
	::testing::Values(  // capacity, expectedResultWeight, expectedResultValue, things
		std::make_tuple(3, 3, 3, Things{{1, 1}, {2, 2}, {3, 3}}),  // Всё влезло ровно
		std::make_tuple(3, 0, 0, Things{{5, 10}, {7, 13}}),        // Не влезло ничего
		std::make_tuple(5, 3, 30, Things{{1, 10,}, {2, 20}}),      // Влезло с запасом
		std::make_tuple(4, 4, 11, Things{{2, 5}, {2, 6}, {3, 8}}), // Выбор между легкими и ценными
		std::make_tuple(4, 3, 8, Things{{2, 3}, {2, 3}, {3, 8}}),  // Одна вещь ценнее двух
		std::make_tuple(2, 2, 2, Things{{1, 1}, {1, 1}, {1, 1}}),  // Одинаковые вещи
		std::make_tuple(10, 0, 0, Things{}),                       // Нет вещей
		std::make_tuple(0, 0, 0, Things{{1, 10}, {3, 2}}),         // Нулевая вместимость
		std::make_tuple(5, 0, 0, Things{{1, 0}, {2, 0}, {3, 0}}),  // «Бесценные» вещи (нулевая цена)
		std::make_tuple(1, 0, 10, Things{{0, 2}, {0, 3}, {0, 5}}), // Невесомые вещи
		std::make_tuple(2, 2, 5, Things{{2, 3}, {2, 5}})           // Одинаковый вес, разная ценность
	)
);
