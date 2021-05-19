/*
 * lesson_2021_05_11_binary_search_tree.cpp
 *
 *  Created on: May 11, 2021
 *      Author: KZ
 */

#include <iostream>
#include <cassert>

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

	TreeNode* insert(int key) {
		if (key == this->data) {
			// don't add duplicate keys
			return this;
		} else if (key < this->data) {
			if (this->left) {
				return this->left->insert(key);
			} else {
				TreeNode* new_node = new TreeNode(key);
				this->left = new_node;
				return new_node;
			}
		} else if (key > this->data) {
			if (this->right) {
				return this->right->insert(key);
			} else {
				TreeNode* new_node = new TreeNode(key);
				this->right = new_node;
				return new_node;
			}
		}
	}

	TreeNode*& find_previous_child() {
		TreeNode*& current = this->left;
		if (!current) { return current; } //no previous child
		while(current->right) {
			current = current->right;
		}
		return current;
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

bool remove_func(TreeNode*& node, int key) {
	if (key == node->data) {
		if (node->left) {
			if (node->right) { //both children present
				TreeNode*& previous = node->find_previous_child();
				assert(previous != nullptr);
				node->data = previous->data;
				remove_func(previous, previous->data);

			} else {
				node->data = node->left->data;
				remove_func(node->left, node->left->data);
			}
		} else {
			if (node->right) {
				node->data = node->right->data;
				remove_func(node->right, node->right->data);
			} else { // no children
				TreeNode* to_delete = node;
				node = nullptr;
				delete to_delete;
			}
		}
		return true;
	} else if (key < node->data) {
		if (node->left) {
			return remove_func(node->left, key);
		} else {
			return false;
		}
	} else if (key > node->data) {
		if (node->right) {
			return remove_func(node->right, key);
		} else {
			return false;
		}
	}
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

	TreeNode* insert(int key) {
		if (this->root) {
			return this->root->insert(key);
		} else {
			this->root = new TreeNode(key);
			return this->root;
		}
	}

	bool remove(int key) {
		return remove_func(this->root, key);
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


	TreeNode* find_iterative_v3(int key) {
		return find_iterative_func(this->root, key);
	}

    TreeNode* find_non_recursive_v4(int key)
    {
        TreeNode* node = root;
        while (node) // better add {} here, or later changes make introduce subtle and hard to find bugs
            if (node->data > key)
                node = node->right;
            else if (node->data < key)
                node = node->left;
            else
                return node;
        return nullptr;
    }

    TreeNode* find_key_v5(int key)
    {
        TreeNode* current = root;
        while (current != NULL)
        {
            if (current->data == key) return current;
            if (key < current->data) current = current->left;
            else current = current->right;
        }
        return nullptr;
    }

	TreeNode* find_func_v6_errors(int key) {
		if (root) {
			if (key == root->data) {
				return root;
			} else { // ERROR: accessing root without check for nullptr
				while (key < root->data) { // ERROR: works only for always left or always right, not in general case
					root=root->left; // ERROR: changes root
				}
				while (key > root->data) {
					root=root->right;
				}
			}
			if (key == root->data) {
				return root;
			}

			return nullptr;
		}
	}

	TreeNode* find_func_v6(int key) {
		if (root) {
			if (key == root->data) {
				return root;
			} else {
				while (root && key < root->data) {
					root=root->left;
				}
				while (root && key > root->data) {
					root=root->right;
				}
			}
			if (root && key == root->data) {
				return root;
			}

			return nullptr;
		}
	}

    TreeNode* find_nonrecursive_v7(int key)
    {
        TreeNode* node = root;
        while (node != NULL)
        {
            if (node->data == key)
            {
                return node;
            }
            if (key < node->data)
            {
                node = node->left;
            }
            else{ node = node->right;
            }
        }
        return nullptr;}


	TreeNode* find_iterative(int key) {
		return find_iterative_v3(key);
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

	tree.insert(4);
	tree.print_as_tree();

	if (tree.remove(2)) {
		std::cout<<"removed 2"<<std::endl;
	} else {
		std::cout<<"could not remove 2"<<std::endl;
	}
	tree.print_as_tree();

	return 0;
}
}

