#include "include/hashTableOperations.h"
#include <iostream>

hashTable::hashTable(int size) {
	this->size = size;
	table = new tNode * [size] {nullptr};
}

int hashTable::hash(const int key) const {
	return key % size;
}


int hashTable::add(int key, int data, int feature) {
	if (++capacity / (double)size > 0.75 || feature == 1)
		rehash();
	const int index = hash(key);
	if (feature == 2 && table[index]) {
		table[index]->key = key;
		table[index]->data = data;
		return index;
	}
	table[index] = new tNode{ key, data, table[index] };
	return index;
}

void hashTable::print() const {
	int cnt = 0;
	for (int i = 0; i < size; i++) {
		tNode* node = table[i];
		while (node) {
			std::cout << i << "_" << ++cnt << "\t|" << node->key << "\t" << node->data << '\n';
			node = node->next;
		}
		cnt = 0;
	}
}

int hashTable::get(int key) const {
	tNode* node = table[hash(key)];
	while (node) {
		if (node->key == key) {
			return node->data;
		}
		node = node->next;
	}
	return -1;
}

int hashTable::remove(int key) const {
	tNode* node = table[hash(key)];
	tNode* prev = node;
	while (node) {
		if (node->key == key) {
			prev->next = node->next;
			delete node;
			return 0;
		}
		node = node->next;
	}
	return -1;
}

void hashTable::rehash() {
	tNode** tmp = table;
	table = new tNode * [size = size * 2]{ nullptr };
	capacity = 0;
	for (int i = 0; i < size / 2; i++) {
		while (tmp[i]) {
			add(tmp[i]->key, tmp[i]->data);
			tNode* del = tmp[i];
			tmp[i] = tmp[i]->next;
			delete del;
		}
	}
	delete[] tmp;
}

hashTable::~hashTable() {
	for (int i = 0; i < size; i++) {
		while (table[i]) {
			tNode* tmp = table[i];
			table[i] = table[i]->next;
			delete tmp;
		}
	}
	delete[] table;
}

int testHashT() {
	int code = 0, menu = 1, num, num2;
	std::cout << "Enter size of hash table: ";
	std::cin >> num;
	hashTable table(num);

	while (menu) {
		std::cout << "Press 1 to add element to hash table\n"
			<< "Press 2 to add element to hash table and rehash it\n"
			<< "Press 3 to add element to without collision\n"
			<< "Press 4 to remove element from hash table\n"
			<< "Press 5 to rehash hash table\n"
			<< "Press 6 to output hash table\n";
		std::cin >> menu;

		switch (menu) {
		case 1:
			std::cout << "Enter numbers: ";
			std::cin >> num >> num2;
			code = table.add(num, num2);
			std::cout << "Index " << code;
			break;
		case 2:
			std::cout << "Enter numbers: ";
			std::cin >> num >> num2;
			table.add(num, num2, 1);
			std::cout << "Index " << code;
			break;
		case 3:
			std::cout << "Enter numbers: ";
			std::cin >> num >> num2;
			table.add(num, num2, 2);
			std::cout << "Index " << code;
			break;
		case 4:
			std::cout << "Enter number: ";
			std::cin >> num;
			code = table.remove(num);
			break;
		case 5:
			std::cout << "Rehashing...";
			code = table.remove(num);
			break;
		case 6:
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