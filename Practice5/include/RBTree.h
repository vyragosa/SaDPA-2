#pragma once
#include <string>
#include "include/BinFileOperations.h"
enum Color {
	RED = true,
	BLACK = false,
};

struct tNode {
	int data;
	Patient& ref;
	int color = RED;
	tNode* left = nullptr;
	tNode* right = nullptr;
	tNode* parent = nullptr;
};

class RBTree {
	void rotateLeft(tNode*& node);
	void rotateRight(tNode*& node);
	void fixInsertRBTree(tNode*& node);
	void fixDeleteRBTree(tNode*& node);
	int getColor(tNode*&);
	void setColor(tNode*&, int);
	tNode* insertBST(tNode*&, tNode*&);
	tNode* deleteBST(tNode*&, int);
	tNode* minValueNode(tNode*& node);
public:
	tNode* root;
	RBTree();
	void insertValue(int n, Patient& patient);
	void deleteValue(int n);
	Patient* get(tNode*& node, int data);
	void deleteTree(tNode*& node);
	~RBTree();
	void printTree(tNode*& node, const std::string& prefix = "", bool isRight = false);
};
