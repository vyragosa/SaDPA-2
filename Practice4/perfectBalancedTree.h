#pragma once

struct tNode {
	double data;
	tNode* left;
	tNode* right;
};

class perfectBalancedTree {
	int size;
	static double average(tNode*& node);
public:
	tNode* root;
	perfectBalancedTree(int _size);
	void createTree(tNode*& node, int size);
	void printTree(tNode*& node, const std::string& prefix = "", bool isRight = false);
	void deleteTree(tNode*& node);
	void getAverage(tNode*& node);
	~perfectBalancedTree();
};