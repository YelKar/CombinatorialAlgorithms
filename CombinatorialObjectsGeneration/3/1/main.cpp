#include <vector>
#include <numeric>
#include "print.h"
#include "Combinations.h"


int main(int argc, char** argv) {
	auto array = Combinations::First(5, 3);
	do {
		tools::PrintArray(array);
	} while (Combinations::Next(array, 5));
	return 0;
}