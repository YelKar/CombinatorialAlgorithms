#include <gtest/gtest.h>
#include "RCut.h"


class TSTest : public ::testing::TestWithParam<std::tuple<MetricSpace>> {};

TEST_P(TSTest, Tests) {
	auto [edges] = GetParam();
    
}

INSTANTIATE_TEST_SUITE_P(
	Cases,
	TSTest,
	::testing::Values(
		
	)
);
