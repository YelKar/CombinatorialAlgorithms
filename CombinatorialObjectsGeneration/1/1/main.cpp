#include <algorithm>
#include "timer.h"
#include "print.h"
#include "matrix.h"
#include "Permutations.h"

#include <limits>

int main(int argc, char *argv[]) {
    tools::Timer timer;
	std::vector<int> array = Permutations::First(13);
	timer.Start();
	do {
//		tools::PrintArray(array);
	} while (Permutations::Next(array));
	auto time = timer.GetDelta();
	std::cout << "Time for N = " << array.size() << ": " << time.ToSeconds() << "s" << std::endl;
//	for (int i = array.size(); i <= 15; i++) {
//		array.push_back(i);
//	}
//	timer.start();
//	do {
//		// tools::PrintArray(array);
//	} while (Narayana::NextPermutation(array));
//	time = timer.getDelta();
//	std::cout << "Time for N = " << array.size() << ": " << time.toSeconds() << "s" << std::endl;
	std::cout << "Estimated time for N = 20: " << time.ToSeconds() * (tgamma(20) / tgamma(array.size() + 1)) << "s" << std::endl;
	std::cout << "Estimated time for N = 50: " << time.ToSeconds() * (tgamma(50) / tgamma(array.size() + 1)) << "s" << std::endl;
    return 0;
}
