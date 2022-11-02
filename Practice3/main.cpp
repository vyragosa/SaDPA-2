#include <iostream>
#include "include/BinFileOperations.h"
#include "include/hashTableOperations.h"
#include "include/binHashTable.h"

int main() {
	int num;
	std::cout << "Press 1 to test hash table\n"
		<< "Press 2 to test binary file operations\n"
		<< "Press 3 to test manually hash table (binary)\n"
		<< "Press 4 to test with preset hash table (binary)\n";
	std::cin >> num;
	switch (num) {
	case 1:
		return testHashT();
	case 2:
		return testBinF();
	case 3:
		return testBinHashM();
	case 4:
		return testBinHashT();
	default:
		return 0;
	}
}
