#include <iostream>

struct typeitem {
	int key = 0;
	int offset = 0;
	bool openORclose = true;    //свободна
	bool deleteORnot = false;   //не удалялась
};

struct hashTable {
	int L = 19;
	typeitem *T;    //таблица
	int insertedcount;  //количество вставленных ключей
	int deletedcount;   //количество удаленных ключей
	void createHashTable() {
		T = new typeitem[L];
		insertedcount = 0;
		deletedcount = 0;
	}
};

int hash(int key, int L) {
	return key % L;
}

int insertInHashTable(int key, int offset, hashTable &t) {
	int i = hash(key, t.L);
	while (i < t.L && !t.T[i].openORclose)
		i++;
	if (i < t.L) {
		t.T[i].key = key;
		t.T[i].offset = offset;
		t.T[i].openORclose = false;
		t.insertedcount++;
		return 0;
	}
	return -1;
}

int search(int key, hashTable &t) {
	int i = hash(key, t.L);
	while (i < t.L && ((t.T[i].openORclose == false
			&& t.T[i].deleteORnot == false)
			|| (t.T[i].openORclose == true && t.T->deleteORnot == true))
			&& t.T[i].key != key)
		i++;
	if (t.T[i].openORclose == true && t.T->deleteORnot == true)
		return -1;
	return t.T[i].offset;
}

void outHashTable(hashTable t) {
	for (int i = 0; i < t.L; ++i) {
		std::cout << i << ' ' << t.T[i].key << ' ' << t.T[i].offset << std::endl;
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