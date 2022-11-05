#include <chrono>
#include <iostream>
#include <random>
#include "include/hashTableOperations.h"
#include "include/perfectBalancedTree.h"
#include "include/RBTree.h"
#include <vector>
using namespace std;
void test(int size) {
	std::cout << size << " elements\n";
	std::cout << "Creating structures...\n";
	BBT::RBTree* rbTree = new BBT::RBTree;
	BT::perfectBalancedTree* pbTree = new BT::perfectBalancedTree(size);
	BT::i = 0;
	HT::hashTable* table = new HT::hashTable(size * 2);
	
	std::cout << "Filling structures...\n";
	for(int i = 0; i < size; i++) {

		rbTree->insertValue(randomValues[i], randomValues[i]);
		table->add(randomValues[i], randomValues[i]);
	}
	int key = randomValues[rand() % size];
	std::cout << "Key functions has to find and return: " << key <<'\n';
	std::cout << "Searching...\n";
	auto begin = std::chrono::high_resolution_clock::now();
	std::cout << "Data: " << table->get(key) << '\n';
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - begin;
	std::cout << "Time to find in hash table: " << duration.count() << "ms\n";
	std::cout << "Comparisons: " << HT::c <<'\n';
	HT::c = 0;

	begin = std::chrono::high_resolution_clock::now();
	std::cout << "Data: " << pbTree->get(pbTree->root, key) << '\n';
	end = std::chrono::high_resolution_clock::now();
	duration = end - begin;
	std::cout << "Time to find middle record: " << duration.count() << "ms\n";
	std::cout << "Comparisons: " << BT::c << '\n';
	BT::c = 0;

	begin = std::chrono::high_resolution_clock::now();
	std::cout << "Data: " << rbTree->get(rbTree->root, key) << '\n';
	end = std::chrono::high_resolution_clock::now();
	duration = end - begin;
	std::cout << "Time to find last record: " << duration.count() << "ms\n";
	std::cout << "Comparisons: " << BBT::c << '\n';
	std::cout << "********************************************************\n";
	BBT::c = 0;

	delete table;
	delete pbTree;
	delete rbTree;
}

int main() {
	for (unsigned int i = 0; i < 10000000; ++i)
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