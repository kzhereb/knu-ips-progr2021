/*
 * lesson_2021_04_07_binary_tree_expressions.cpp
 *
 *  Created on: Apr 7, 2021
 *      Author: KZ
 */

#include <iostream>
#include <string>
#include <cassert>

namespace lesson_2021_04_07_binary_tree_expressions {

struct VariableValues {

};


struct TreeNode {
	std::string data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(std::string data, TreeNode* left = nullptr, TreeNode* right = nullptr) {
		this->data = data;
		this->left = left;
		this->right = right;
	}

	int calculate(VariableValues* vars = nullptr) {
		if (data == "+") {
			return left->calculate(vars) + right->calculate(vars);
		} else if (data == "-") {
			return left->calculate(vars) - right->calculate(vars);
		} else if (data == "*") {
			return left->calculate(vars) * right->calculate(vars);
		} else if (data == "/") {
			int right_value = right->calculate(vars);
			assert(right_value != 0);
			return left->calculate(vars) / right_value;
		} else { // number in string
			int value = std::stoi(data);
			return value;
		}
	}
};



int main() {


	TreeNode* root = new TreeNode("+", new TreeNode("5"), new TreeNode("10"));
	std::cout<<root->calculate()<<std::endl;
	return 0;
}

}



