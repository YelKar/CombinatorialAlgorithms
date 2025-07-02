#include <vector>


namespace Knapsack {

struct Thing {
	int weight;
	int value;
};

std::ostream& operator<<(std::ostream& os, const Thing& thing) {
	os << "(w=" << thing.weight << " v=" << thing.value << ")";
	return os;
}

struct Knapsack {
	const int capacity;
	int value;
	std::vector<Thing> things;
};


bool NextOccurrence(std::vector<bool>& array) {
	size_t size = array.size();
	for (size_t i = size; i > 0 && i--;) {
		if (!array[i]) {
			array[i] = true;
			for (size_t j = i + 1; size > j; ++j)
				array[j] = false;
			return true;
		}
	}
	return false;
}

void Pack(Knapsack& knapsack, std::vector<Thing>& things) {
	std::vector<bool> array(things.size(), false);
	std::vector<bool> bestThingsIndicator;
	int maxValue = 0;
	do {
		int weight = 0;
		int value = 0;
		for (int i = 0; i < array.size(); ++i) {
			if (array[i]) {
				weight += things[i].weight;
				value += things[i].value;
			}
		}

		if (weight <= knapsack.capacity && value > maxValue) {
			maxValue = value;
			bestThingsIndicator = array;
		}
	} while (NextOccurrence(array));

	knapsack.value = maxValue;
	knapsack.things.clear();
	for (int i = 0; i < bestThingsIndicator.size(); ++i) {
		if (bestThingsIndicator[i]) {
			knapsack.things.push_back(things[i]);
		}
	}
}

}
