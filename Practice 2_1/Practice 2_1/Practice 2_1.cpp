#include <iostream>
#include <fstream>
#include "fileOperations.h"

int main() {
	std::string fileName, newFileName;
	int num, code = 0, menu = 1;
	srand(time(NULL));
	while (menu) {
		std::cout << "Press 1 to choose your interaction file\n"
			<< "Press 2 to create file with random numbers\n"
			<< "Press 3 to output your file\n"
			<< "Press 4 to input new number to the end of file\n"
			<< "Press 5 to find index of number in file\n"
			<< "Press 6 to return amount of numbers in file\n"
			<< "Press 7 to create file with prime nubers\n"
			<< "Press 0 to exit program\n";
		std::cin >> menu;

		switch (menu)
		{
		case 1:
			std::cout << "Enter name of your interaction file: ";
			std::cin >> fileName;
			break;
		case 2:
			std::cout << "Enter amount of numbers: ";
			std::cin >> num;
			code = createTextFile(fileName, num);
			break;
		case 3:
			code = readTextFile(fileName);
			break;
		case 4:
			std::cout << "Enter number you want to add: ";
			std::cin >> num;
			code = addTextToFile(fileName, num);
			break;
		case 5:
			std::cout << "Enter number: ";
			std::cin >> num;
			code = findNByNumber(fileName, num);
			if (code == -1)
				std::cout << "Number not found!\n";
			else
				std::cout << "Index of number: " << code << std::endl;
			break;
		case 6:
			code = countNInFile(fileName);
			if (code == -1)
				std::cout << "Number not found!\n";
			else
				std::cout << "Amount of numbers: " << code << std::endl;
			break;
		case 7:
			std::cout << "Enter name of new text file: ";
			std::cin >> newFileName;
			code = createTextFilePrime(fileName, newFileName);
			break;
		default:
			break;
		}
		if (code == -1)
			std::cout << "There are some file problems!\n";
		std::cout << std::endl;
	}
	return 0;
}
