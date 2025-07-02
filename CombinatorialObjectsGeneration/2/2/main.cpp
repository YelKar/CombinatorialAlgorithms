#include <vector>
#include <fstream>
#include "print.h"
#include "Knapsack.h"


std::vector<Knapsack::Thing> ReadThingsFromFile(const std::string& filename);

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cerr << "Using: " << argv[0] << " <max weight> <file>\n";
		return 1;
	}

	int maxWeight = std::stoi(argv[1]);
	std::string filename = argv[2];
	std::vector<Knapsack::Thing> things = ReadThingsFromFile(filename);
	Knapsack::Knapsack knapsack(maxWeight);
	Knapsack::Pack(knapsack, things);
	std::cout << "Best Value: " << knapsack.value << "\n";
	std::cout << "Best Things: ";
	tools::PrintArray(knapsack.things);
	return 0;
}

std::vector<Knapsack::Thing> ReadThingsFromFile(const std::string& filename) {
	std::vector<Knapsack::Thing> things;
	std::ifstream input(filename);
	if (!input) {
		std::cerr << "Error: cannot read the file '" << filename << "'\n";
		return things;
	}

	int w, v;
	while (input >> w >> v) {
		things.push_back({w, v});
	}

	return things;
}
