#pragma once

class hashTable {
	struct tNode {
		int key;
		int data;
		tNode* next;
	};
	int size;
	tNode** table;
	int capacity;
	int hash(int key) const;
public:
	hashTable(int size);
	int add(int key, int data, int feature = 0);
	void print() const;
	int get(int key) const;
	int remove(int key);
	void rehash();
	~hashTable();
};

int testHashT();
