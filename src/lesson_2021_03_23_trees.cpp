/*
 * lesson_2021_03_23_trees.cpp
 *
 *  Created on: Mar 23, 2021
 *      Author: KZ
 */

#include <iostream>
#include <cassert>

namespace lesson_2021_03_23_trees {

struct TreeNode {
	int data;
	TreeNode* next;
	TreeNode* prev;
	TreeNode* first_child;
	TreeNode* parent;
	TreeNode(int data, TreeNode* prev=nullptr, TreeNode* next=nullptr, TreeNode* parent=nullptr, TreeNode* first_child=nullptr) {
		this->data = data;
		this->prev = prev;
		this->next = next;
		this->parent = parent;
		this->first_child = first_child;
	}
};

struct Tree {
	TreeNode* root;
	Tree() {
		root = nullptr;
	}

	TreeNode* add(int data, TreeNode* parent = nullptr) {
		TreeNode* new_node = new TreeNode(data);
		if (parent == nullptr) {
			if (this->root) {
				// add to root
				add_child_node(root, new_node);
			} else {
				this->root = new_node;
			}
		} else {
			// add to parent
			add_child_node(parent, new_node);
		}

		return new_node;
	}

	void add_child_node(TreeNode* parent, TreeNode* child) {
		assert(parent != nullptr);
		assert(child != nullptr);

		child->parent = parent;

		TreeNode* current = parent->first_child;
		if (! current) {
			parent->first_child = child;
			return;
		}
		while (current->next) {
			current = current->next;
		}
		current->next = child;
		child->prev = current;


	}
	void print(TreeNode* node_to_print = nullptr) {
		if (! node_to_print) {
			node_to_print = this->root;
			if (! node_to_print) {
				std::cout<<"Empty tree"<<std::endl;
				return;
			}
		}
		std::cout<<node_to_print->data<<"(";
		TreeNode* current = node_to_print->first_child;
		while (current) {
			print(current);
			current = current->next;
			if (current) { std::cout<<", "; }
		}
		std::cout<<")";
		if (node_to_print == this->root) {
			std::cout<<std::endl;
		}

	}
};


int main() {
	Tree tree;

	tree.add(10);
	std::cout<<tree.root->data<<std::endl;
	tree.add(25);
	std::cout<<tree.root->first_child->data<<std::endl;
	tree.print();
	tree.add(35);
	tree.print();

	return 0;
}
}


