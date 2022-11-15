#pragma once
#include <cstdint>


inline uint64_t cHT = 0;

struct hashTable {
	struct tNode {
		int key;
		int data;
		tNode* next;
	};
	int size;
	tNode** table;
	int capacity = 0;
	hashTable(int size);
	int hash(int key) const;
	int add(int key, int data, int feature = 0);
	void print() const;
	int get(int key) const;
	int remove(int key);
	void rehash();
	~hashTable();
};

int testHashT();
