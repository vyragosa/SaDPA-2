#include <iostream>
#include "include/RBTree.h"
#include "include/binRBTOperations.h"
#include "include/BinFileOperations.h"

int main() {
	int num;
	std::cout << "Press 1 to test tree\n"
		<< "Press 2 to test binary operations\n"
		<< "Press 3 to test tree on binary file\n"
		<< "Press 4 to test rotation count\n";
	std::cin >> num;
	switch (num) {
	case 1:
		return testRBTreeM();
	case 2:
		return testBinF();
	case 3:
		return testBinRBT();
	case 4:
		return testRotations();
	default:
		return 0;
	}
}
