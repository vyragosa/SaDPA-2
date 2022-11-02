#pragma once
#ifndef asd
#include "include/BinFileOperations.h"
#include "include/hashTableOperations.h"

int addRecord(hashTable& table, std::string name, int pos);

int addAll(hashTable& table, std::string name);

int testBinHash();
#endif asd
