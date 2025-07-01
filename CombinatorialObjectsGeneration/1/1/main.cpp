#include <algorithm>
#include "timer.h"
#include "print.h"
#include "matrix.h"
#include "narayana.h"

#include <limits>

int main(int argc, char *argv[]) {
    tools::Timer timer;
	std::vector<int> array = {1, 2, 3, 4};
	do {
		tools::PrintArray(array);
	} while (Narayana::NextPermutation(array));
    return 0;
}
