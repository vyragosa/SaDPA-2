#pragma once
#include <string>

class BSTree {
	struct tNode {
		int key;
		int data;
		tNode* left = nullptr;
		tNode* right = nullptr;
	};
	tNode* root;
	void deleteTree(tNode*& node);
	tNode* minValueNode(tNode*& node);
	void insertValue(tNode*& node, int key, int data);
	int get(tNode*& node, int key);
	void deleteValue(tNode*& node, int key);
	void printTree(tNode*& node, const std::string& prefix = "", bool isRight = false);

public:
	BSTree();
	int insertValue(int key, int data);
	int get(int key);
	void deleteValue(int key);
	void printTree();
	~BSTree();
};

BSTree* generateBSTreeRandom(int cnt);
int testBSTreeM();
