#pragma once
#include <string>


class RBTree {
	enum Color {
		RED,
		BLACK,
	};
	struct tNode {
		int key;
		int data;
		int color = RED;
		tNode* left = nullptr;
		tNode* right = nullptr;
		tNode* parent = nullptr;
	};
	tNode* root;
	void rotateLeft(tNode*& node);
	void rotateRight(tNode*& node);
	void fixInsertRBTree(tNode*& node);
	void fixDeleteRBTree(tNode*& node);
	int getColor(tNode*&);
	void setColor(tNode*&, int);
	tNode* insertBST(tNode*&, tNode*&);
	tNode* deleteBST(tNode*&, int);
	tNode* minValueNode(tNode*& node);
	void deleteTree(tNode*& node);
	int get(tNode*& node, int key);
	void printTree(tNode*& node, const std::string& prefix = "", bool isRight = false);
public:
	RBTree();
	int insertValue(int n, int data);
	int deleteValue(int n);
	int get(int key);
	~RBTree();
	void printTree();
};


RBTree* generateRBTreeRandom(int cnt);

int testRBTreeM();