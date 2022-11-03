#pragma once

struct tNode {
	double data;
	tNode* left;
	tNode* right;
};

class perfectBalancedTree {
	int size;
	static void average(tNode*& node, double& sum, int& cnt);
public:
	tNode* root;
	perfectBalancedTree(int _size);
	static void createTree(tNode*& node, int size);
	static void printTree(tNode*& node, const std::string& prefix = "", bool isRight = false);
	static void deleteTree(tNode*& node);
	static void getAverage(tNode*& node);
	~perfectBalancedTree();
};