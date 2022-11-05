﻿#include <iostream>
#include "include/RBTree.h"
#include "include/binRBTOperations.h"
using namespace std;

int main() {
	int num;
	std::cout << "Press 1 to test tree\n"
			  << "Press 2 to test tree om binary file\n"
			  << "Press 3 to test speed\n";
	std::cin >> num;
	switch (num) {
		case 1:
			return testRBTreeM();
		case 2:
			return testBinF();
		case 3:
			return testBinRBT();
		default:
			return 0;
	}
}