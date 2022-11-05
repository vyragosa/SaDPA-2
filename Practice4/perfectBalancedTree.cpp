#include <iostream>
#include "perfectBalancedTree.h"

perfectBalancedTree::perfectBalancedTree(int _size) {
	createTree(root = nullptr, size = _size);
}

void perfectBalancedTree::createTree(tNode*& node, int size) {
	if (size == 0)
		return;
	int key, data;
	std::cin >> key >> data;

	node = new tNode{key, data, nullptr, nullptr};
	createTree(node->left, size / 2);
	createTree(node->right, size - 1 - size / 2);
}

void perfectBalancedTree::printTree(tNode*& node, const std::string& prefix, bool isRight) {
	if (!node)
		return;
	printTree(node->right, prefix + (isRight ? "    " : "|   "), true);
	std::cout << prefix + "|--" << node->key << " " << node->data << '\n';
	printTree(node->left, prefix + (isRight ? "|   " : "    "), false);
}


void perfectBalancedTree::deleteTree(tNode*& node) {
	if (!node)
		return;
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

double perfectBalancedTree::average(tNode*& node) {
	if (!node)
		return 0;
	return node->key + average(node->left) + average(node->right);
}

void perfectBalancedTree::getAverage(tNode*& node) {
	std::cout << "Average of left subtree: " << average(node->left) / (double)(size / 2) << '\n';
	std::cout << "Average of right subtree: " << average(node->right) / (double)(size - 1 - size / 2) << '\n';
}

perfectBalancedTree::~perfectBalancedTree() {
	deleteTree(root);
}

int perfectBalancedTree::searchElement(tNode*& node, int key) {
	if (!node)
		return -1;
	if (key == node->key)
		return node->data;
	if (searchElement(node->left, key) == -1)
		searchElement(node->right, key);
}
