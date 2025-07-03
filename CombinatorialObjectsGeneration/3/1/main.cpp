#include <vector>
#include <numeric>
#include "print.h"
#include "PermutationWithRepetition.h"


void PrintAllPermutations(int n, int k) {
	std::vector array(k, 0);
	std::cout << "(n=" << n << ", k=" << k << "): ";
	do {
		tools::PrintArray(array, "", " -> ");
	} while (PermutationWithRepetition::Next(array, n));
	tools::PrintArray(array, "");
}

int main(int argc, char** argv) {
	PrintAllPermutations(3, 2);
	PrintAllPermutations(2, 3);
	PrintAllPermutations(2, 1);
	PrintAllPermutations(15, 1);
	PrintAllPermutations(1, 15);
	return 0;
}