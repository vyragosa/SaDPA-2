#pragma once
#include <string>

class PBTree {
	struct tNode {
		int key;
		int data;
		tNode* left = nullptr;
		tNode* right = nullptr;
	};
	int size;
	tNode* root;
	static double average(tNode*& node);
	int get(tNode*& node, int key);
	void deleteTree(tNode*& node);
	void printTree(tNode*& node, const std::string& prefix = "", bool isRight = false);
	void getAverage(tNode*& node);
public:
	PBTree(int _size);
	void createTree(tNode*& node, int size);
	void printTree();
	void getAverage();
	int get(int key);
	~PBTree();
};

int testPBTreeM();
