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
};

TreeNode* build_from_sorted_array(int* array, std::size_t size) {
	if (size == 0) {
		return nullptr;
	}
	std::size_t middle = size/2;
	return new TreeNode(array[middle],
			build_from_sorted_array(&array[0], middle),
			build_from_sorted_array(&array[middle + 1], size - middle - 1)
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

	return 0;
}
}

