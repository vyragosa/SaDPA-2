#include "grassHopper.h"
#include <iostream>

int* grass_hoppers_jumps(int N, int K, const int* path) {
	int* parents = new int[N] {0};
	int* dynamic = new int[N];
	dynamic[0] = 0;
	for (int i = 1; i < N; i++) {
		int max_value;
		if (i - K > 0)
			max_value = i - K;
		else
			max_value = 0;
		int num_max = i;
		for (int j = max_value; j < i; j++) {
			if (dynamic[max_value] <= dynamic[j]) {
				num_max = j;
			}
		}
		parents[i] = num_max;
		dynamic[i] = dynamic[num_max] + path[i];
	}
	delete[] dynamic;

	int* jumps = new int[N] {0};
	int iterator = N - 1;
	for (int i = 0; i < N; i++) {
		jumps[i] = iterator;
		iterator = parents[iterator];
	}
	delete[] parents;
	return jumps;
}

void print_jumps(int* array, int size) {
	std::cout << "Jumps:\n1\t";
	for (int i = size - 1; i >= 0; i--) {
		if (array[i] != 0)
			std::cout << array[i] + 1 << '\t';
	}
	std::cout << '\n';
}

int* fill_coins(int size) {
	int* array = new int[size] {0};
	for (int i = 1; i < size - 1; i++) {
		std::cin >> array[i];
	}
	return array;
}
