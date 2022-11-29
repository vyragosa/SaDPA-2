#include <iostream>

int *grassHoppersJumps(int N, int k, const int *path) {
	int *coins_path = new int[N]{0};
	int *max_array = new int[N]{0};
	for (int i = 1; i < N; i++) {
		int max_value;
		if ((i - k) > 0) max_value = i - k;
		else max_value = 0;
		int max_index = i;
		for (int j = max_value; j < i; j++) {
			if (max_array[max_value] <= max_array[j]) {
				max_index = j;
			}
		}
		coins_path[i] = max_index;
		max_array[i] = max_array[max_index] + path[i];
	}
	delete[] max_array;

	int *jumps = new int[N]{0};
	int iter = N - 1;
	for (int i = 0; i < N; i++) {
		jumps[i] = iter;
		iter = coins_path[iter];
	}
	delete[] coins_path;
	return jumps;
}

void print_jumps(int *array, int size) {
	std::cout << "Jumps:\n1\t" ;
	for (int i = size - 1; i >= 0; i--) {
		if (array[i] != 0)
			std::cout << array[i] + 1 << '\t';
	}
	std::cout << '\n';
}

int* fill_coins(int size) {
	int *array = new int[size]{0};
	for (int i = 1; i < size - 1; i++) {
		std::cin >> array[i];
	}
	return array;
}

int main() {
	int N, k;
	std::cout << "Enter N and K: ";
	std::cin >> N >> k;
	std::cout << "Enter coins: ";
	int *coins = fill_coins(N);
	int *jumps = grassHoppersJumps(N, k, coins);
	print_jumps(jumps, N);
	delete[] coins;
	delete[] jumps;
	return 0;
}