#pragma once
#include <string>

inline uint32_t rotateCount = 0;

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
	void fixInsert(tNode*& node);
	void fixDelete(tNode*& node);
	int getColor(tNode*&);
	void setColor(tNode*&, int);
	tNode* insertValue(tNode*&, tNode*&);
	tNode* deleteValue(tNode*&, int);
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