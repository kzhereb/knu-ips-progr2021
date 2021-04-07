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

	template<typename Callable>
	void traverse_callable(TreeNode* node, Callable process) {
		process(node->data);

		TreeNode* current = node->first_child;
		while(current) {
			traverse_callable<Callable>(current, process);
			current = current->next;
		}
	}
};

void process_print(int data) {
	std::cout<<data<<" ";
}

namespace traverse_sum {
int sum = 0;
void process_sum_global(int data) {
	sum += data;
}
}

void process_sum_static_print(int data) {
	static int sum = 0;
	sum += data;
	std::cout<<"partial sum = "<<sum<<std::endl;
}

void process_sum_static_print_reset(int data, bool needs_reset=false) {
	static int sum = 0;
	if (needs_reset) {
		sum = 0;
	}
	sum += data;
	std::cout<<"partial sum = "<<sum<<std::endl;
}

void process_sum_static_ref_reset(int data, int& result, bool needs_reset=false) {
	static int sum = 0;
	if (needs_reset) {
		sum = 0;
	}
	sum += data;
	result = sum;
}

struct Summator {
	int sum;
	Summator() {sum = 0;}
	Summator(const Summator& other) = delete;
	void operator()(int data) {
		this->sum+= data;
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

	std::cout<<"traverse print"<<std::endl;
	tree.traverse(tree.root,process_print);
	std::cout<<std::endl;

	std::cout<<"traverse sum global"<<std::endl;
	traverse_sum::sum = 0;
	tree.traverse(tree.root,traverse_sum::process_sum_global);
	std::cout<<"sum="<<traverse_sum::sum<<std::endl;

	std::cout<<"traverse sum global"<<std::endl;
	traverse_sum::sum = 0;
	tree.traverse(tree.root,traverse_sum::process_sum_global);
	std::cout<<"sum="<<traverse_sum::sum<<std::endl;

	std::cout<<"traverse sum static print"<<std::endl;
	tree.traverse(tree.root,process_sum_static_print);
	std::cout<<std::endl;

	std::cout<<"traverse sum static print"<<std::endl;
	tree.traverse(tree.root,process_sum_static_print);
	std::cout<<std::endl;

	std::cout<<"traverse sum static print with reset"<<std::endl;
	// tree.traverse(tree.root,process_sum_static_print_reset); // ERROR - wrong function signature
	tree.traverse(tree.root, [] (int data) { process_sum_static_print_reset(data);});
	std::cout<<std::endl;

	std::cout<<"traverse sum static print with reset"<<std::endl;

	// tree.traverse(tree.root, [] (int data) { process_sum_static_print_reset(data, true);}); // ERROR - resets on each step
	tree.traverse(tree.root, [] (int data) {
		static bool first_call = true;
		process_sum_static_print_reset(data, first_call);
		first_call = false;
	});
	std::cout<<std::endl;

	std::cout<<"traverse sum static print with reset"<<std::endl;

	// tree.traverse(tree.root, [] (int data) { process_sum_static_print_reset(data, true);}); // ERROR - resets on each step
	tree.traverse(tree.root, [] (int data) {
		static bool first_call = true;
		process_sum_static_print_reset(data, first_call);
		first_call = false;
	});
	std::cout<<std::endl;

	std::cout<<"traverse sum static print with reset"<<std::endl;
	process_sum_static_print_reset(0,true); // reset sum
	tree.traverse(tree.root, [] (int data) { process_sum_static_print_reset(data);});
	std::cout<<std::endl;


	std::cout<<"traverse sum static ref with reset"<<std::endl;
	int sum = 0;
//	tree.traverse(tree.root, [&] (int data) { //ERROR: can't convert capturing lambda to function pointer
//		static bool first_call = true;
//		process_sum_static_ref_reset(data, sum, first_call);
//		first_call = false;
//	});

	tree.traverse_callable(tree.root, [&] (int data) { //OK: template doesn't require function pointer, just any callable with correct signature
		static bool first_call = true;
		process_sum_static_ref_reset(data, sum, first_call);
		first_call = false;
	});
	std::cout<<"sum="<<sum<<std::endl;


	std::cout<<"traverse sum functor"<<std::endl;
	Summator summator;
	tree.traverse_callable<Summator&>(tree.root,summator);
	std::cout<<"sum="<<summator.sum<<std::endl<<std::endl;

	std::cout << "remove 25" << std::endl;
	tree.remove(tree.root->first_child);
	tree.print();

	std::cout << "remove root" << std::endl;
	tree.remove(tree.root);
	tree.print();

	return 0;
}
}


