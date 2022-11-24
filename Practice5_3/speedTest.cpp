#include "include/speedTest.h"
#include "include/hashTableOperations.h"
#include "include/BSTree.h"
#include "include/RBTree.h"

#include <chrono>
#include <iostream>
#include <random>
#include <algorithm>

void test(int size) {
	std::cout << size << " elements\n";
	std::cout << "Creating structures...\n";
	RBTree* rbTree = new RBTree();
	hashTable* table = new hashTable(size * 2);
	BSTree* bsTree = new BSTree();

	std::cout << "Filling structures...\n";
	for (int i = 0; i < size; i++) {
		table->add(randomValues[i], randomValues[i]);
		bsTree->insertValue(randomValues[i], randomValues[i]);
		rbTree->insertValue(randomValues[i], randomValues[i]);
	}
	const int key = randomValues[rand() % size];
	std::cout << "Key: " << key << '\n';
	std::cout << "Searching...\n";
	std::cout << "Chained hash table \t";

	int data;
	auto start = std::chrono::high_resolution_clock::now();
	data = table->get(key);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Data: " << data << '\t'
		<< "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns\t"
		<< "Comparisons: " << cHT << '\n';
	cHT = 0;

	std::cout << "Binary search tree \t";
	start = std::chrono::high_resolution_clock::now();
	data = bsTree->get(key);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Data: " << data << '\t'
		<< "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns\t"
		<< "Comparisons: " << cBST << '\n';
	cBST = 0;

	std::cout << "Red-black tree    \t";
	start = std::chrono::high_resolution_clock::now();
	data = rbTree->get(key);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Data: " << data << '\t'
		<< "Time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns\t"
		<< "Comparisons: " << cRBT << '\n';
	cRBT = 0;

	std::cout << "********************************************************\n";
	delete table;
	delete bsTree;
	delete rbTree;
}

int speedTest() {
	for (int i = 0; i < 10000000; ++i)
		randomValues.push_back(i + 1);
	std::ranges::shuffle(randomValues, std::mt19937(std::random_device()()));
	test(10);
	test(100);
	test(1000);
	test(10000);
	test(100000);
	test(1000000);
	return 0;
}
