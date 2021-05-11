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

	TreeNode* find_recursive(int key) {
		if (root) {
			return root->find_recursive(key);
		} else {
			return nullptr;
		}
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

	return 0;
}
}

