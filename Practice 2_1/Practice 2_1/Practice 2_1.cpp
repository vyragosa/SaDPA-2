#include <iostream>
#include <fstream>
#include "fileOperations.h"

int main() {
	std::string fileName, newFileName;
	std::cout << "Enter name of your text file: ";
	std::cin >> fileName;
	int code = readTextFile(fileName);

	if (code == -1) {
		std::cout << "There are some file problems!";
		return code;
	}

	std::cout << "Enter name of new text file: ";
	std::cin >> newFileName;

	code = createTextFile(fileName, newFileName);
	if (code == -1) {
		std::cout << "There are some file problems!";
		return code;
	}
	std::cout << foundNByNumber(fileName, 123);
	std::cout << "Retult:\n";
	readTextFile(newFileName);
	return 0;
}
