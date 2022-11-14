#include <chrono>
#include <iostream>
#include <random>
#include "include/hashTableOperations.h"
#include "include/BSTree.h"
#include "include/RBTree.h"
#include <vector>

inline std::vector<int> randomValues;

void test(int size);

int main() {
	for (int i = 0; i < 10000000; ++i)
		randomValues.push_back(i + 1);
	std::ranges::shuffle(randomValues, std::default_random_engine(time(nullptr)));

	test(10);
	test(100);
	test(1000);
	test(10000);
	test(100000);
	test(1000000);
	return 0;
}

void test(int size) {
	std::cout << size << " elements\n";
	std::cout << "Creating structures...\n";
	RBTree* rbTree = new RBTree;
	hashTable* table = new hashTable(size * 2);
	BSTree* bsTree = new BSTree;

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
	auto begin = std::chrono::high_resolution_clock::now();
	std::cout << "Data: " << table->get(key) << '\t';
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - begin;
	std::cout << "Time: " << duration.count() << "ms\t";
	std::cout << "Comparisons: " << cHT << '\n';
	cHT = 0;

	std::cout << "Binary search tree\t";
	begin = std::chrono::high_resolution_clock::now();
	std::cout << "Data: " << bsTree->get(key) << '\t';
	end = std::chrono::high_resolution_clock::now();
	duration = end - begin;
	std::cout << "Time: " << duration.count() << "ms\t";
	std::cout << "Comparisons: " << cBST << '\n';
	cBST = 0;

	std::cout << "Red-black tree  \t";
	begin = std::chrono::high_resolution_clock::now();
	std::cout << "Data: " << rbTree->get(key) << '\t';
	end = std::chrono::high_resolution_clock::now();
	duration = end - begin;
	std::cout << "Time: " << duration.count() << "ms\t";
	std::cout << "Comparisons: " << cBBT << '\n';
	cBBT = 0;

	std::cout << "********************************************************\n";
	delete table;
	delete bsTree;
	delete rbTree;
}
