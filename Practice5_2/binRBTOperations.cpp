#include <iostream>
#include "include/binRBTOperations.h"
#include "include/BinFileOperations.h"

int addRecord(RBTree& tree, std::string name, int pos) {
	int number = getPolicyByPosition(name, pos);
	if (number == -1)
		return -1;
	return tree.insertValue(number, pos);
}

int addAll(RBTree& tree, std::string name) {
	for (int i = 0; i < sizeOfFile(name); i++) {
		addRecord(tree, name, i);
	}
	return 0;
}

int deleteByKey(RBTree& tree, std::string name, int key) {
	int number = tree.get(key);
	if (number == -1)
		return -1;
	tree.deleteValue(key);
	return directAccessDelete(name, number);
}

int getByKey(RBTree& tree, std::string name, int key) {
	Patient patient;
	int code = directAccess(name, tree.get(key), patient);
	if (code == -1)
		return -1;
	printPatient(patient);
	return code;
}

int testRotations() {
	uint32_t cnt = 0;
	int i;
	const std::string name = "B.bin";
	RBTree tree;
	for (i = 0; i < sizeOfFile(name); i++) {
		addRecord(tree, name, i);
		cnt += rotateCount;
		rotateCount = 0;
	}
	std::cout << "Rotations: " << cnt << '\n'
			  << "Average rotations: " << cnt / (double)i << '\n';
	return 0;
}

int testBinRBT() {
	std::string fileName, newFileName;
	int num, code = 0, menu = 1;
	RBTree tree;
	while (menu) {
		std::cout << "Press 1 to choose your interaction binary file\n"
			<< "Press 2 overwrite from text file to binary file\n"
			<< "Press 3 to print binary file\n"
			<< "Press 4 to add all records to tree\n"
			<< "Press 5 to add single record to tree\n"
			<< "Press 6 delete from tree and file\n"
			<< "Press 7 to search in tree\n"
			<< "Press 8 to print tree"
			<< "Press 0 to exit program\n";

		std::cin >> menu;

		switch (menu) {
		case 1:
			std::cout << "Enter name of your interaction file: ";
			std::cin >> fileName;
			break;
		case 2:
			std::cout << "Enter text file name: ";
			std::cin >> newFileName;
			code = overwriteFromTextToBinary(fileName, newFileName);
			break;
		case 3:
			code = printBinFile(fileName);
			break;
		case 4:
			code = addAll(tree, fileName);
			break;
		case 5:
			std::cout << "Enter position: ";
			std::cin >> num;
			code = addRecord(tree, fileName, num);
			break;
		case 6:
			std::cout << "Enter key: ";
			std::cin >> num;
			code = deleteByKey(tree, fileName, num);
			break;
		case 7:
			std::cout << "Enter key: ";
			std::cin >> num;
			code = getByKey(tree, fileName, num);
			break;
		case 8:
			tree.printTree();
			break;
		default:
			break;
		}
		if (code == -1)
			std::cout << "There are some problems!\n";
		std::cout << std::endl;
	}
	return 0;
}
