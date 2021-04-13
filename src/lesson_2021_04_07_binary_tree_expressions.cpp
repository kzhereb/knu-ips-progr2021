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

struct VariableValue {
	std::string variable;
	int value;
};

struct VariableValues {
	VariableValue* values;
	std::size_t size;
	VariableValues(std::size_t size) {
		this->size = size;
		this->values = new VariableValue[size];
	}

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
		} else { // variable or number in string
			if (vars) {
				for (std::size_t i = 0; i < vars->size; i++) {
					VariableValue val = vars->values[i];
					if(val.variable == data) {
						return val.value;
					}
				}
			}
			int value = std::stoi(data);
			return value;
		}
	}
};



int main() {


	TreeNode* root = new TreeNode("+", new TreeNode("5"), new TreeNode("10"));
	std::cout<<root->calculate()<<std::endl;

	VariableValues* vars = new VariableValues(2);
	vars->values[0] = {"x", 10};
	vars->values[1] = {"y", 7};
	TreeNode* with_vars = new TreeNode("*", new TreeNode("x"),
			new TreeNode("+",new TreeNode("y"), new TreeNode("5")));
	std::cout<<with_vars->calculate(vars)<<std::endl;



	return 0;
}

}



