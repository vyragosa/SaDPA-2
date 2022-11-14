#include "include/RBTree.h"
#include <windows.h>
#include <iostream>

RBTree::RBTree() {
	root = nullptr;
}

int RBTree::getColor(tNode*& node) {
	if (!node)
		return BLACK;
	return node->color;
}

void RBTree::setColor(tNode*& node, int color) {
	if (!node)
		return;
	node->color = color;
}

RBTree::tNode* RBTree::insertBST(tNode*& node, tNode*& ptr) {
	if (!node)
		return ptr;
	if (ptr->key < node->key) {
		node->left = insertBST(node->left, ptr);
		node->left->parent = node;
	}
	else if (ptr->key > node->key) {
		node->right = insertBST(node->right, ptr);
		node->right->parent = node;
	}

	return node;
}

int RBTree::insertValue(int n, int value) {
	tNode* node = new tNode{n, value};
	root = insertBST(root, node);
	fixInsertRBTree(node);
	return 0;
}

void RBTree::rotateLeft(tNode*& ptr) {
	tNode* right_child = ptr->right;
	ptr->right = right_child->left;

	if (ptr->right != nullptr)
		ptr->right->parent = ptr;

	right_child->parent = ptr->parent;

	if (ptr->parent == nullptr)
		root = right_child;
	else if (ptr == ptr->parent->left)
		ptr->parent->left = right_child;
	else
		ptr->parent->right = right_child;

	right_child->left = ptr;
	ptr->parent = right_child;
}

void RBTree::rotateRight(tNode*& ptr) {
	tNode* left_child = ptr->left;
	ptr->left = left_child->right;

	if (ptr->left != nullptr)
		ptr->left->parent = ptr;

	left_child->parent = ptr->parent;

	if (ptr->parent == nullptr)
		root = left_child;
	else if (ptr == ptr->parent->left)
		ptr->parent->left = left_child;
	else
		ptr->parent->right = left_child;

	left_child->right = ptr;
	ptr->parent = left_child;
}

void RBTree::fixInsertRBTree(tNode*& ptr) {
	while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
		tNode* parent = ptr->parent;
		tNode* grandparent = parent->parent;
		if (parent == grandparent->left) {
			//левый дочерний элемент
			tNode* uncle = grandparent->right;
			if (getColor(uncle) == RED) {
				// Если дядя красный, меняем цвет от вставленного узла вверх по циклу
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				ptr = grandparent;
			}
			else {
				// Если дядя черный, тогда выполняется алгоритм поворота около отца узла
				if (ptr == parent->right) {
					rotateLeft(parent);
					ptr = parent;
					parent = ptr->parent;
				}
				std::swap(parent->color, grandparent->color);
				rotateRight(grandparent);
				ptr = parent;
			}
		}
		else {
			//правый дочерний элемент. Симметричный код
			tNode* uncle = grandparent->left;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				ptr = grandparent;
			}
			else {
				if (ptr == parent->left) {
					rotateRight(parent);
					ptr = parent;
					parent = ptr->parent;
				}
				std::swap(parent->color, grandparent->color);
				rotateLeft(grandparent);
				ptr = parent;
			}
		}
	}
	setColor(root, BLACK);
}

void RBTree::fixDeleteRBTree(tNode*& node) {
	if (!node)
		return;
	tNode* sibling;
	tNode* ptr = node;
	while (ptr != root && getColor(ptr) == BLACK) {
		tNode* parent = ptr->parent;
		if (ptr == parent->left) {
			sibling = parent->right;
			if (getColor(sibling) == RED) {
				setColor(sibling, BLACK);
				setColor(parent, RED);
				rotateLeft(parent);
				sibling = parent->right;
			}

			if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
				setColor(sibling, RED);
				ptr = parent;

			}
			else {
				if (getColor(sibling->right) == BLACK) {
					setColor(sibling->left, BLACK);
					setColor(sibling, RED);
					rotateRight(sibling);
					sibling = parent->right;
				}
				setColor(sibling, parent->color);
				setColor(parent, BLACK);
				setColor(sibling->right, BLACK);
				rotateLeft(parent);
				ptr = root;
			}

		}
		else {
			sibling = parent->left;
			if (getColor(sibling) == RED) {
				setColor(sibling, BLACK);
				setColor(parent, RED);
				rotateRight(parent);
				sibling = parent->left;
			}

			if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {

				setColor(sibling, RED);
				ptr = parent;
			}
			else {
				if (getColor(sibling->left) == BLACK) {
					setColor(sibling->right, BLACK);
					setColor(sibling, RED);
					rotateLeft(sibling);
					sibling = parent->left;
				}
				setColor(sibling, parent->color);
				setColor(parent, BLACK);
				setColor(sibling->left, BLACK);
				rotateRight(parent);
				break;

			}
		}

	}
	setColor(node->parent, BLACK);
	if (node == node->parent->left)
		node->parent->left = nullptr;
	else
		node->parent->right = nullptr;
	delete node;
	setColor(root, BLACK);

}

RBTree::tNode* RBTree::deleteBST(tNode*& root, int data) {
	if (!root)
		return root;

	if (data < root->key)
		return deleteBST(root->left, data);

	if (data > root->key)
		return deleteBST(root->right, data);

	if (root->left && root->right)
		return root;

	tNode* temp = minValueNode(root->right);
	root->key = temp->key;
	root->data = temp->data;
	return deleteBST(root->right, temp->key);
}

void RBTree::printTree(tNode*& node, const std::string& prefix, bool isRight) {
	if (!node)
		return;
	printTree(node->right, prefix + (isRight ? "    " : "|   "), true);
	std::cout << prefix + "|--" << (getColor(node) == RED ? "\033[38;5;9m" : "") << node->key
		<< " " << node->data << "\033[0m" << '\n';
	printTree(node->left, prefix + (isRight ? "|   " : "    "), false);
}

int RBTree::deleteValue(int data) {
	tNode* node = deleteBST(root, data);
	fixDeleteRBTree(node);
	return 0;
}

int RBTree::get(int key) {
	return get(root, key);
}

RBTree::tNode* RBTree::minValueNode(tNode*& node) {
	tNode* ptr = node;
	while (ptr->left != nullptr)
		ptr = ptr->left;
	return ptr;
}

int RBTree::get(tNode*& node, int data) {
	cBBT++;
	if (node == nullptr)
		return -1;
	cBBT++;
	if (data < node->key)
		return get(node->left, data);
	cBBT++;
	if (data > node->key)
		return get(node->right, data);
	return node->data;
}

void RBTree::deleteTree(tNode*& node) {
	if (!node)
		return;
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}

RBTree::~RBTree() {
	deleteTree(root);
}

void RBTree::printTree() {
	printTree(root);
}

RBTree* generateRBTreeRandom(int cnt) {
	RBTree* tree = new RBTree();
	for (int i = 1; i <= cnt; i++) {
		tree->insertValue(i, rand());
	}
	return tree;
}

int testRBTreeM() {
	RBTree* tree;
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
			tree = generateRBTreeRandom(num);
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
			std::cout << "Value: " << (num == -1 ? std::to_string(num) : "not found") << '\n';
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
