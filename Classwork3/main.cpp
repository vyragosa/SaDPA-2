#include <iostream>

struct tNode {
	int key = 0;
	int offset = 0;
	bool isOpen = true;    //свободна
	bool isDeleted = false;   //не удалялась
};

struct hashTable {
	int L = 19;
	tNode *table;    //таблица
	int insertedCount;  //количество вставленных ключей
	int deletedCount;   //количество удаленных ключей
	void createHashTable() {
		table = new tNode[L];
		insertedCount = 0;
		deletedCount = 0;
	}
};

int hash(int key, int L) {
	return key % L;
}

int insertInHashTable(int key, int offset, hashTable &t) {
	int i = hash(key, t.L);
	while (i < t.L && !t.table[i].isOpen)
		i++;
	if (i < t.L) {
		t.table[i].key = key;
		t.table[i].offset = offset;
		t.table[i].isOpen = false;
		t.insertedCount++;
		return 0;
	}
	return -1;
}

int search(int key, hashTable &t) {
	int i = hash(key, t.L);
	while (i < t.L && ((t.table[i].isOpen == false
			&& t.table[i].isDeleted == false)
			|| (t.table[i].isOpen == true && t.table->isDeleted == true))
			&& t.table[i].key != key)
		i++;
	if (t.table[i].isOpen == true && t.table->isDeleted == true)
		return -1;
	return t.table[i].offset;
}

void outHashTable(hashTable t) {
	for (int i = 0; i < t.L; ++i) {
		std::cout << i << ' ' << t.table[i].key << ' ' << t.table[i].offset << std::endl;
	}
}

int main() {
	hashTable table;
	table.createHashTable();
	insertInHashTable(101, 1, table);
	insertInHashTable(105, 5, table);
	insertInHashTable(106, 3, table);
	insertInHashTable(102, 2, table);
	insertInHashTable(102, 4, table);
	insertInHashTable(107, 7, table);
	insertInHashTable(108, 6, table);
	insertInHashTable(109, 8, table);
	outHashTable(table);
	std::cout << search(107, table);
}