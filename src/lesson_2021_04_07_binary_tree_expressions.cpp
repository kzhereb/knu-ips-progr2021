/*
 * lesson_2021_04_07_binary_tree_expressions.cpp
 *
 *  Created on: Apr 7, 2021
 *      Author: KZ
 */

#include <iostream>
#include <string>
#include <cctype>
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

	int operation_priority() {
		if (data == "+") {
			return 2;
		} else if (data == "-") {
			return 2;
		} else if (data == "*") {
			return 1;
		} else if (data == "/") {
			return 1;
		} else {
			return -1; // for values and variables, we don't want to use parentheses, so priority should be the lowest
		}
	}

	bool is_operation() {
		return operation_priority() > 0;
	}

	bool is_associative() {
		if (data == "+") {
			return true;
		} else if (data == "-") {
			return false;
		} else if (data == "*") {
			return true;
		} else if (data == "/") {
			return false;
		} else {
			return true; // for values and variables, we don't want to use parentheses, so we consider them associative
		}
	}

	std::string optional_parentheses(TreeNode* child) {
		assert(child!=nullptr);
		bool need_parentheses = false;
		if (child->operation_priority() > this->operation_priority() ) {
			need_parentheses = true;
		} else if(child->operation_priority() == this->operation_priority()) {
			if (child->is_associative() && this->is_associative()) {
				need_parentheses = false;
			} else {
				need_parentheses = true;
			}
		} else {
			need_parentheses = false;
		}
		if (need_parentheses) {
			return "(" + child->pretty_print_no_extra_parentheses() + ")";
		} else {
			return child->pretty_print_no_extra_parentheses();
		}

	}

	std::string pretty_print_no_extra_parentheses() {
		if (! this->is_operation()) {
			return this->data;
		}
		return optional_parentheses(this->left) + this->data + optional_parentheses(this->right);
	}


};

TreeNode* parse_expression(std::string expression) {
	enum Mode {Number, Variable, Start};
	std::string current_token;
	Mode current_mode;
	for(std::size_t i = 0; i<expression.length(); i++) {
		char current_char = expression[i];
		if (std::isdigit(current_char)) {
			if (current_mode == Number || current_mode == Variable) {
				current_token += current_char;
			}
		} else if (std::isalpha(current_char)) {
			//...
		}
	}
}


int main() {


	TreeNode* root = new TreeNode("+", new TreeNode("5"), new TreeNode("10"));
	std::cout<<root->pretty_print_no_extra_parentheses()<<" = ";
	std::cout<<root->calculate()<<std::endl;

	VariableValues* vars = new VariableValues(2);
	vars->values[0] = {"x", 10};
	vars->values[1] = {"y", 7};
	TreeNode* with_vars = new TreeNode("*", new TreeNode("x"),
			new TreeNode("+",new TreeNode("y"), new TreeNode("5")));
	std::cout<<with_vars->pretty_print_no_extra_parentheses()<<" = ";
	std::cout<<with_vars->calculate(vars)<<std::endl;

	TreeNode* with_vars2 = new TreeNode("+", new TreeNode("x"),
				new TreeNode("*",new TreeNode("y"), new TreeNode("5")));
	std::cout<<with_vars2->pretty_print_no_extra_parentheses()<<" = ";
	std::cout<<with_vars2->calculate(vars)<<std::endl;


	TreeNode* not_associative = new TreeNode("*",
			new TreeNode("/",new TreeNode("x"), new TreeNode("5")),
			new TreeNode("/",new TreeNode("y"), new TreeNode("1"))
	);
	std::cout<<not_associative->pretty_print_no_extra_parentheses()<<" = ";
	std::cout<<not_associative->calculate(vars)<<std::endl;

	return 0;
}

}



