#include "RCut.h"

int main(int argc, char **argv) {
	MetricSpace space{
		{0, {0, 30}},
		{1, {10, 50}},
		{2, {10, 80}},
		{3, {20, 20}},
		{4, {30, 40}},
		{5, {30, 80}},
		{6, {40, 20}},
		{7, {50, 60}},
		{8, {70, 30}},
		{9, {80, 50}},
		{10, {30, 30}},
		{11, {30, 32}},
	};

	auto tree = RCut(space);
	PrintHSTTree(tree);
	return 0;
}