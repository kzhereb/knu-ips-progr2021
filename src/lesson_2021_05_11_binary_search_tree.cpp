/*
 * lesson_2021_05_11_binary_search_tree.cpp
 *
 *  Created on: May 11, 2021
 *      Author: KZ
 */

#include <iostream>

namespace lesson_2021_05_11_binary_search_tree {

struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int data, TreeNode* left = nullptr, TreeNode* right = nullptr) {
		this->data = data;
		this->left = left;
		this->right = right;
	}

	void print_as_tree() {
		std::cout<<this->data<<"(";
		if (left) {
			left->print_as_tree();
		} else {
			std::cout << " ";
		}
		std::cout<<",";
		if (right) {
			right->print_as_tree();
		} else {
			std::cout << " ";
		}
		std::cout<<")";


	}

	TreeNode* find_recursive(int key){
		if (key == data) {
			return this;
		} else if (key < data) {
			if (left) {
				return left->find_recursive(key);
			} else {
				return nullptr;
			}
		} else if (key > data) {
			if (right) {
				return right->find_recursive(key);
			} else {
				return nullptr;
			}
		}
	}
};

TreeNode* find_recursive_func(TreeNode* root, int key) {
	if (root) {
		if (key == root->data) {
			return root;
		} else if (key < root->data) {
			return find_recursive_func(root->left, key);
		} else if (key > root->data) {
			return find_recursive_func(root->right, key);
		}
	} else {
		return nullptr;
	}
}

TreeNode* find_iterative_func(TreeNode* root, int key) {
	TreeNode* current = root;
	while (current && current->data != key) {
		if (key < current->data) {
			current = current->left;
		}
		else if (key > current->data) {
			current = current->right;
		}
	}
	return current;
}

TreeNode* build_from_sorted_array(int* array, std::size_t size) {
	if (size == 0) {
		return nullptr;
	}
	std::size_t middle = size/2;
	return new TreeNode(array[middle],
			build_from_sorted_array(array, middle),
			build_from_sorted_array(array + middle + 1, size - middle - 1) //&array[middle + 1]
			);
}

struct BinarySearchTree {
	TreeNode* root;
	BinarySearchTree() {
		root = nullptr;
	}
	BinarySearchTree(int* array, std::size_t size){
		root = build_from_sorted_array(array, size);
	}

	TreeNode* find_recursive_verbose(int key) {
		if (root) {
			return root->find_recursive(key);
		} else {
			return nullptr;
		}
	}
	TreeNode* find_recursive(int key) {
		return find_recursive_func(root, key);
	}

	TreeNode* find_not_recursive_v1_warn(int key) {
		TreeNode* current = this->root;
		while (current) {
			if (key == current->data) {
				return current;
			} else if (key < current->data) {
				if (current->left) {
					current = current->left;
				} else {
					return nullptr;
				}
			} else if (key > current->data) {
				if (current->right) {
					current = current->right;
				} else {
					return nullptr;
				}
			}
		}
	}

	TreeNode* find_not_recursive_v1(int key) {
		TreeNode* current = this->root;
		while (current) {
			if (key == current->data) {
				return current;
			} else if (key < current->data) {
				current = current->left;
			} else if (key > current->data) {
				current = current->right;
			}
		}
		return nullptr;
	}

	TreeNode* find_not_recursive_v2(int key) {

		TreeNode* current = root;
		if (current != nullptr) { // Extra check not needed
			while (current) {
				if (key == current->data) {
					return current;
				} else if (key < current->data) {
					current = current->left;
				} else if (key > current->data) {
					current = current->right;
				}
			}
			//if (current == nullptr) //WARNING: if uncommented, results in "not all code paths return value"
				return nullptr;
		} else {
			return nullptr;
		}
	}

	TreeNode* find_iterative(int key) {
		return find_iterative_func(this->root, key);
	}

	void print_as_tree() {
		if (root) {
			root->print_as_tree();
		} else {
			std::cout<<"Empty tree";
		}
		std::cout<<std::endl;
	}



};


int main() {
	std::size_t size = 6;
	int array[] { 1, 2, 3, 5, 7, 9};

	BinarySearchTree tree(array, size);
	tree.print_as_tree();

	TreeNode* found = tree.find_recursive(7);
	std::cout<<"searching for 7: ";
	found->print_as_tree();
	std::cout<<std::endl;

	found = tree.find_recursive(8);
	std::cout<<"searching for 8: ";
	std::cout<<found<<std::endl;

	found = tree.find_iterative(7);
	std::cout<<"searching for 7: ";
	found->print_as_tree();
	std::cout<<std::endl;

	found = tree.find_iterative(8);
	std::cout<<"searching for 8: ";
	std::cout<<found<<std::endl;

	return 0;
}
}

