#include <iostream>
#include "perfectBalancedTree.h"

perfectBalancedTree::perfectBalancedTree(int _size) {
	createTree(root = nullptr, size = _size);
}

void perfectBalancedTree::createTree(tNode*& node, int size) {
	if (size != 0) {
		double x;
		std::cin >> x;
		node = new tNode{ x, nullptr, nullptr };
		createTree(node->left, size / 2);
		createTree(node->right, size - 1 - size / 2);
	}
}

void perfectBalancedTree::printTree(tNode*& node, const std::string& prefix, bool isRight) {
	if (node) {
		std::cout << prefix + (isRight ? "|--" : "L--") << node->data << '\n';

		printTree(node->right, prefix + (isRight ? "|   " : "    "), true);
		printTree(node->left, prefix + (isRight ? "|   " : "    "), false);
	}
}

void perfectBalancedTree::deleteTree(tNode*& node) {
	if (node) {
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

void perfectBalancedTree::average(tNode*& node, double& sum, int& cnt) {
	if (node) {
		average(node->left, sum += node->data, ++cnt);
		average(node->right, sum += node->data, ++cnt);
	}
}

void perfectBalancedTree::getAverage(tNode*& node) {
	double sum;
	int cnt;
	average(node->left, sum = 0, cnt = 0);
	std::cout << "Average of left subtree: " << sum / (double)cnt << '\n';
	average(node->right, sum = 0, cnt = 0);
	std::cout << "Average of right subtree: " << sum / (double)cnt << '\n';
}

perfectBalancedTree::~perfectBalancedTree() {
	deleteTree(root);
}
