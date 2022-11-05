#pragma once
#include <string>

namespace BBT
{
	inline uint64_t c = 0;
	enum Color {
		RED = true,
		BLACK = false,
	};
	struct tNode {
		int key;
		int data;
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
		int insertValue(int n, int data);
		int deleteValue(int n);
		int get(tNode*& node, int key);
		void deleteTree(tNode*& node);
		~RBTree();
		void printTree(tNode*& node, const std::string& prefix = "", bool isRight = false);
	};

	
}

int testRBTreeM();
BBT::RBTree* generateTreeRandom(int cnt);

