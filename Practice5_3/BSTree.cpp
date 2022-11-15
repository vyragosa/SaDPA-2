#include "include/BSTree.h"
#include <iostream>

BSTree::BSTree() {
	root = nullptr;
}

void BSTree::insertValue(int key, int data) {
	insertValue(root, key, data);
}

int BSTree::get(int key) {
	return get(root, key);
}

void BSTree::deleteValue(int key) {
	deleteValue(root, key);
}

void BSTree::printTree() {
	printTree(root);
}

void BSTree::insertValue(tNode*& node, int key, int data) {
	if (!node) {
		node = new tNode{key, data};
	}
	else if (key < node->key)
		insertValue(node->left, key, data);
	else if (key > node->key)
		insertValue(node->right, key, data);
}

void BSTree::deleteValue(tNode*& node, int key) {
	if (!node)
		return;
	if (key < node->key)
		deleteValue(node->left, key);
	else if (key > node->key)
		deleteValue(node->right, key);
	else if (node->left && node->right) {
		const tNode* temp = minValueNode(node->right);
		node->data = temp->data;
		node->key = temp->key;
		deleteValue(node->right, node->key);
	}
	else {
		const tNode* temp = node;
		if (!node->left)
			node = node->right;
		else if (!node->right)
			node = node->left;
		delete temp;
	}
}

BSTree::tNode* BSTree::minValueNode(tNode*& node) {
	if (!node)
		return nullptr;
	if (!node->left)
		return node;
	return minValueNode(node->left);
}

int BSTree::get(tNode*& node, int data) {
	cBST++;
	if (!node)
		return -1;
	cBST++;
	if (data < node->key)
		return get(node->left, data);
	cBST++;
	if (data > node->key)
		return get(node->right, data);
	return node->data;
}

void BSTree::printTree(tNode*& node, const std::string& prefix, bool isRight) {
	if (!node)
		return;
	printTree(node->right, prefix + (isRight ? "    " : "|   "), true);
	std::cout << prefix + "|--" << node->key << " " << node->data << '\n';
	printTree(node->left, prefix + (isRight ? "|   " : "    "), false);
}

void BSTree::deleteTree(tNode*& node) {
	if (!node)
		return;
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

BSTree::~BSTree() {
	deleteTree(root);
}

BSTree* generateBSTreeRandom(int cnt) {
	BSTree* tree = new BSTree();
	for (int i = 0; i < cnt; i++) {
		tree->insertValue(rand(), rand());
	}
	return tree;
}

int testBSTreeM() {
	BSTree* tree;
	int num, code = 0, menu = 1;
	while (menu) {
		std::cout << "Press 1 Generate tree\n"
			<< "Press 2 insert node\n"
			<< "Press 3 delete node\n"
			<< "Press 4 to get node\n"
			<< "Press 5 to print tree\n"
			<< "Press 6 to delete tree\n"
			<< "Press 0 to exit program\n";
		std::cin >> menu;

		switch (menu) {
		case 1:
			std::cout << "Enter amount of nodes: ";
			std::cin >> num;
			tree = generateBSTreeRandom(num);
			break;
		case 2:
			std::cout << "Enter node: ";
			std::cin >> num;
			tree->insertValue(num, rand());
			break;
		case 3:
			std::cout << "Enter node: ";
			std::cin >> num;
			tree->deleteValue(num);
			break;
		case 4:
			std::cout << "Enter node : ";
			std::cin >> num;
			num = tree->get(num);
			std::cout << "Value: " << (num != -1 ? std::to_string(num) : "not found") << '\n';
			break;
		case 5:
			std::cout << "*******************************************\n";
			tree->printTree();
			std::cout << "*******************************************\n";
			break;
		case 6:
			delete tree;
			break;
		default:
			break;
		}
		if (code == -1)
			std::cout << "There are some problems!\n";
		std::cout << std::endl;
	}
	return 0;
}
