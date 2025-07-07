#include "timer.h"
#include "print.h"
#include "Permutations.h"


int main(int argc, char *argv[]) {
	std::vector<int> array = Permutations::First(13);
	auto time = tools::LoggingTimer::Measure("Time for N = " + std::to_string(array.size()), [&array] {
		while (Permutations::Next(array));
	});
	std::cout << "Estimated time for N = 20: " << time.ToSeconds() * (tgamma(20) / tgamma(array.size() + 1)) << "s" << std::endl;
	std::cout << "Estimated time for N = 50: " << time.ToSeconds() * (tgamma(50) / tgamma(array.size() + 1)) << "s" << std::endl;
    return 0;
}
