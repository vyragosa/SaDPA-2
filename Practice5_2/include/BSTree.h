#pragma once
#include <string>

namespace BST
{
	inline int c;

	struct tNode {
		int key;
		int data;
		tNode* left = nullptr;
		tNode* right = nullptr;
	};

	class BSTree {
		tNode* root;
		void deleteTree(tNode*& node);
		tNode* minValueNode(tNode*& node);
		void insertValue(tNode*& node, int key, int data);
		int get(tNode*& node, int key);
		void deleteValue(tNode*& node, int key);
		void printTree(tNode*& node, const std::string& prefix = "", bool isRight = false);

	public:
		BSTree();
		void insertValue(int key, int data);
		int get(int key);
		void deleteValue(int key);
		void printTree();
		~BSTree();
	};
	BSTree* generateTreeRandom(int cnt);
	int testBSTreeM();
}


