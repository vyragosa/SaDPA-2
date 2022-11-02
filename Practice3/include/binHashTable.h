#pragma once
#include "include/BinFileOperations.h"
#include "include/hashTableOperations.h"

int addRecord(hashTable& table, std::string name, int pos);

int addAll(hashTable& table, std::string name);

int deleteByKey(hashTable& hashTable, std::string name, int key);

int getByKey(hashTable& hashTable, std::string name, int key);

int testBinHashT();

int testBinHashM();

