#pragma once
#include <string>
#include <vector>
inline std::vector<int> randomValues;
namespace BT
{
	inline int i = 0;
	inline uint64_t c = 0;
	struct tNode {
		int key;
		int data;
		tNode* left;
		tNode* right;
	};
	class perfectBalancedTree {
		

		int size;
		int average(tNode*& node);
	public:


		tNode* root;
		perfectBalancedTree(int _size);
		void createTree(tNode*& node, int size);
		void printTree(tNode*& node, const std::string& prefix = "", bool isRight = false);
		void deleteTree(tNode*& node);
		void getAverage(tNode*& node);
		int get(tNode*& node, int key);
		~perfectBalancedTree();
	};
}


