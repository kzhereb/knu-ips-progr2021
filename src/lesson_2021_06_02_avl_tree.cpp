/*
 * lesson_2021_06_02_avl_tree.cpp
 *
 *  Created on: Jun 2, 2021
 *      Author: KZ
 */


namespace lesson_2021_06_02_avl_tree {

struct AvlNode {
	int data;
	int balance; // right height - left height
	AvlNode* left;
	AvlNode* right;
	AvlNode(int data, int balance = 0, AvlNode* left = nullptr, AvlNode* right = nullptr) {
		this->data = data;
		this->balance = balance;
		this->left = left;
		this->right = right;
	}
};

struct AvlTree {
	AvlNode* root;

	AvlTree() {
		root = nullptr;
	}

	void left_rotate(AvlNode*& current) {
		AvlNode* b = current->right;
		current->right = b->left;
		b->left = current;
		current = b;
	}

	void right_rotate(AvlNode*& current) {
		AvlNode* b = current->left;
		current->left = b->right;
		b->right = current;
		current = b;
	}

	AvlNode* insert_recursive(AvlNode* current, int key) {
		if (key == current->data) {
			return current;
		} else if (key < current->data) {
			if (current->left) {
				int prev_balance = current->left->balance;
				AvlNode* result = insert_recursive(current->left, key);
				int current_balance = current->left->balance;
				if (prev_balance == 0) {
					if (current_balance != 0) {
						current->balance--;
						if (current->balance < -1) {
							// rebalance
						}
					}
				} else if (prev_balance == -1) {

				}
			} else {
				current->left = new AvlNode(key);
				current->balance--;
				return current->left;

			}
		} else { // key > current->data
			current = current->right;
		}
	}

	AvlNode* insert(int key) {
		if (!this->root) {
			this->root = new AvlNode(key);
			return this->root;
		}
		AvlNode* current = this->root;
		while (current) {
			if (key == current->data) {
				return current;
			} else if (key < current->data) {
				if (current->left) {
					current = current->left;
				} else {
					current->left = new AvlNode(key);
					current->balance--;
					if (current->balance < -1) {
						fix_balance(current);
					}
				}
			} else { // key > current->data
				current = current->right;
			}
		}
	}
};


int main() {
	return 0;
}
}

