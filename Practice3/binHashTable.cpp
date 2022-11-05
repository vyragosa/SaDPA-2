#include "include/binHashTable.h"
#include <chrono>
#include <iostream>

int addRecord(hashTable& table, std::string name, int pos) {
	int number = getPolicyByPosition(name, pos);
	if (number == -1)
		return -1;
	return table.add(number, pos);
}

int addAll(hashTable& table, std::string name) {
	for (int i = 0; i < sizeOfFile(name); i++) {
		addRecord(table, name, i);
	}
	return 0;
}

int deleteByKey(hashTable& hashTable, std::string name, int key) {
	int number = hashTable.get(key);
	if (number == -1)
		return -1;
	hashTable.remove(key);
	return directAccessDelete(name, number);
}

int getByKey(hashTable& hashTable, std::string name, int key) {
	Patient patient;
	int code = directAccess(name, hashTable.get(key), patient);
	if (code == -1)
		return -1;
	printPatient(patient);
	return code;
}

int testBinHashT() {
	std::cout << "Test on small amount of data\n";
	overwriteFromTextToBinary("B.bin", "A.txt");
	printBinFile("B.bin");
	hashTable table1(10);
	addAll(table1, "B.bin");
	table1.print();
	std::cout << "*******************************************\n";

	std::cout << "Test on big amount of data\n";
	std::cout << "Filling bin file...\n";
	fillRandBinary("B.bin", 1000000);
	// printBinFile("B.bin");
	hashTable table2(1000000);
	std::cout << "Filling hash table...\n";
	addAll(table2, "B.bin");
	//table1.print();
	std::cout << "Searching...\n";
	auto begin = std::chrono::high_resolution_clock::now();
	getByKey(table2, "B.bin", getPolicyByPosition("B.bin", 0));
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - begin;
	std::cout << "Time to find first record: " << duration.count() << "ms\n";

	begin = std::chrono::high_resolution_clock::now();
	getByKey(table2, "B.bin", getPolicyByPosition("B.bin", 500000));
	end = std::chrono::high_resolution_clock::now();
	duration = end - begin;
	std::cout << "Time to find middle record: " << duration.count() << "ms\n";

	begin = std::chrono::high_resolution_clock::now();
	getByKey(table2, "B.bin", getPolicyByPosition("B.bin", 999999));
	end = std::chrono::high_resolution_clock::now();
	duration = end - begin;
	std::cout << "Time to find last record: " << duration.count() << "ms\n";

	return 0;
}

int testBinHashM() {
	std::string fileName, newFileName;
	int num, code = 0, menu = 1;
	std::cout << "Enter size of hash table: ";
	std::cin >> num;
	hashTable table(num);
	while (menu) {
		std::cout << "Press 1 to choose your interaction binary file\n"
			<< "Press 2 overwrite from text file to binary file\n"
			<< "Press 3 to print binary file\n"
			<< "Press 4 to add all records to hash table\n"
			<< "Press 5 to add single record to hash table\n"
			<< "Press 6 delete from hash table and file\n"
			<< "Press 7 to search in hash table\n"
			<< "Press 8 to print hash table"
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
			code = addAll(table, fileName);
			break;
		case 5:
			std::cout << "Enter position: ";
			std::cin >> num;
			code = addRecord(table, fileName, num);
			break;
		case 6:
			std::cout << "Enter key: ";
			std::cin >> num;
			code = deleteByKey(table, fileName, num);
			break;
		case 7:
			std::cout << "Enter key: ";
			std::cin >> num;
			code = getByKey(table, fileName, num);
			break;
		case 8:
			table.print();
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
