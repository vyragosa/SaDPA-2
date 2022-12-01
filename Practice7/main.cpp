#include <iostream>
#include "grassHopper.h"

int main() {
	int N, k;
	std::cout << "Enter N and K: ";
	std::cin >> N >> k;
	std::cout << "Enter coins: ";
	int* coins = fill_coins(N);
	int* jumps = grass_hoppers_jumps(N, k, coins);
	print_jumps(jumps, N);
	delete[] coins;
	delete[] jumps;
	return 0;
}
