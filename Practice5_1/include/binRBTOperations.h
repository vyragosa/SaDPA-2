#pragma once
#include "RBTree.h"

int addRecord(RBTree& tree, std::string name, int pos);

int addAll(RBTree& tree, std::string name);

int deleteByKey(RBTree& tree, std::string name, int key);

int getByKey(RBTree& tree, std::string name, int key);

int testBinRBT();