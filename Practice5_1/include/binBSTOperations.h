#pragma once
#include "BSTree.h"

int addRecord(BSTree& tree, std::string name, int pos);

int addAll(BSTree& tree, std::string name);

int deleteByKey(BSTree& tree, std::string name, int key);

int getByKey(BSTree& tree, std::string name, int key);

int testBinRBT();