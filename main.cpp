#include <iostream>
#include <vector>
#include "tools/print.h"


void Sort(std::vector<int>& arr);
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{

	std::vector<int> arr = {3, 7, 3, 4, 7, 2, 9, 4, 3};
	Sort(arr);
	tools::PrintArray(arr);

	return 0;
	// TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}

void Sort(std::vector<int>& arr) {
	if (arr.size() < 2) {
		return;
	}
	bool sorted = false;

	while (!sorted) {
		sorted = true;
		for (auto it = arr.begin() + 1; it != arr.end(); ++it) {
			if (*(it - 1) > *it) {
				sorted = false;
				std::swap(*it, *(it - 1));
			}
		}
	}
}
