#include <iostream>
#include "PBTree.h"

PBTree::PBTree(int _size) {
	createTree(root = nullptr, size = _size);
}

void PBTree::createTree(tNode*& node, int size) {
	if (size == 0)
		return;
	int key, data;
	std::cin >> key >> data;

	node = new tNode{key, data};
	createTree(node->left, size / 2);
	createTree(node->right, size - 1 - size / 2);
}

void PBTree::printTree() {
	printTree(root);
}

void PBTree::getAverage() {
	getAverage(root);
}

void PBTree::printTree(tNode*& node, const std::string& prefix, bool isRight) {
	if (!node)
		return;
	printTree(node->right, prefix + (isRight ? "    " : "|   "), true);
	std::cout << prefix + "|--" << node->key << " " << node->data << '\n';
	printTree(node->left, prefix + (isRight ? "|   " : "    "), false);
}


void PBTree::deleteTree(tNode*& node) {
	if (!node)
		return;
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

double PBTree::average(tNode*& node) {
	if (!node)
		return 0;
	return node->key + average(node->left) + average(node->right);
}

void PBTree::getAverage(tNode*& node) {
	std::cout << "Average of left subtree: " << average(node->left) / (double)(size / 2) << '\n';
	std::cout << "Average of right subtree: " << average(node->right) / (double)(size - 1 - size / 2) << '\n';
}

int PBTree::get(int key) {
	return get(root, key);
}

PBTree::~PBTree() {
	deleteTree(root);
}

int PBTree::get(tNode*& node, int key) {
	if (!node)
		return -1;
	if (key == node->key)
		return node->data;
	if (get(node->left, key) == -1)
		get(node->right, key);
	return -1;
}

int testPBTreeM() {
	int menu = 1, num;
	PBTree* tree;
	while (menu) {
		std::cout << "Press 1 create perfect balanced tree\n"
			<< "Press 2 print tree from root\n"
			<< "Press 3 to get average\n"
			<< "Press 4 to delete tree\n"
			<< "Press 5 to search by key\n"
			<< "Press 0 to exit program\n";
		std::cin >> menu;
		switch (menu) {
		case 1:
			std::cout << "Enter size of tree: ";
			std::cin >> num;
			tree = new PBTree(num);
			break;
		case 2:
			tree->printTree();
			break;
		case 3:
			tree->getAverage();
			break;
		case 4:
			delete tree;
			break;
		case 5:
			std::cout << "Enter key: ";
			std::cin >> num;
			num = tree->get(num);
			std::cout << "Data: " << (num != -1 ? std::to_string(num) : "not found") << '\n';
			break;
		default:
			break;
		}
	}
	return 0;
}
