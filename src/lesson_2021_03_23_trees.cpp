/*
 * lesson_2021_03_23_trees.cpp
 *
 *  Created on: Mar 23, 2021
 *      Author: KZ
 */

#include <iostream>
#include <cassert>

namespace lesson_2021_03_23_trees {



// root (parent = nullptr, prev=next=nullptr, first_child = ch1
// > ch1 (parent = root, prev = nullptr, next = ch2, first_child = gc1)
// >>> gc1 (parent = ch1, prev = nullptr, next = gc2, first_child = nullptr)
// >>> gc2 (parent = ch1, prev = gc1, next = nullptr, first_child = nullptr)
// > ch2 (parent = root, prev = ch1, next = ch3, first_child = nullptr)
// > ch3 (parent = root, prev = ch2, next = nullptr, first_child = gc3)
// >>> gc3 (parent = ch3, prev = nullptr, next = nullptr, first_child = nullptr)


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

	void remove(TreeNode* node) {
		if (node->prev) {
			node->prev->next = node->next;
		} else {
			if (node->parent) { // this is first child
				assert(node->parent->first_child == node);
				node->parent->first_child = node->next;
			} else { //this is root
				assert(this->root == node);
				this->root = nullptr;
			}
		}
		if (node->next) {
			node->next->prev = node->prev;
		}

		while(node->first_child) {
			remove(node->first_child);
		}

		delete node;
	}
	typedef void (*process_func)(int);
	void traverse(TreeNode* node, process_func process) {
		process(node->data);

		TreeNode* current = node->first_child;
		while(current) {
			traverse(current, process);
			current = current->next;
		}
	}
};

void process_print(int data) {
	std::cout<<data<<" ";
}

int main() {
	Tree tree;

	tree.add(10);
	std::cout<<tree.root->data<<std::endl;
	tree.add(25);
	std::cout<<tree.root->first_child->data<<std::endl;
	tree.print();
	tree.add(35);
	tree.print();

	std::cout<<"traverse print"<<std::endl;
	tree.traverse(tree.root,process_print);
	std::cout<<std::endl;

	std::cout << "remove 25" << std::endl;
	tree.remove(tree.root->first_child);
	tree.print();

	std::cout << "remove root" << std::endl;
	tree.remove(tree.root);
	tree.print();

	return 0;
}
}


