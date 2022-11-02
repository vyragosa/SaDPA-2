#include "include/binHashTable.h"
#include <iostream>
int addRecord(hashTable& table, std::string name, int pos) {
    return table.add(getRecordByPosition(name, pos), pos);
}
 
int addAll(hashTable& table, std::string name) {
    for (int i = 0; i < sizeOfFile(name); i++) {
        addRecord(table, name, i);
        std::cout << sizeOfFile(name) << '\n';
    }
    return 0;
}

int deleteByKey(hashTable& hashTable, std::string name, int key) {
    int number = hashTable.get(key);
    if (number == -1)
        return -1;
    hashTable.remove(key);
    return deleteRecordByAccess(name, number);
}

int getByKey(hashTable& hashTable, std::string name, int key) {
    int number = hashTable.get(key);
    if (number == -1)
        return -1;
    Patient patient;
    number = directAcess(name, number, patient);
    if (number == -1)
        return -1;
    printPatient(patient);
}

int testBinHash() {
    hashTable table(100);
    addAll(table, "B.bin");
    table.print();
    printBinFile("B.bin");
    deleteByKey(table, "B.bin", 13599);
    printBinFile("B.bin");
    std::cout << '\n';
    getByKey(table, "B.bin", 80289);
    return 0;
}
