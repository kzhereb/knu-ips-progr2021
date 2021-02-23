/*
 * lesson_2021_02_23_stack_queue.cpp
 *
 *  Created on: Feb 23, 2021
 *      Author: KZ
 */

#include <iostream>

namespace lesson_2021_02_23_stack_queue {

struct ListNode {
	int value;
	ListNode* next;
	ListNode(int value, ListNode* next = nullptr) {
		this->value = value;
		this->next = next;
	}
};

struct Stack {
	std::size_t size;
	ListNode* top;

	Stack() {
		this->size = 0;
		this->top = nullptr;
	}


	void push(int value) {
		ListNode* new_node = new ListNode(value, this->top);
		this->top = new_node;
		size++;
	}

	int pop_minus1() {
		if (this->top == nullptr) {
			std::cout<<"Trying to pop item from empty stack"<<std::endl;
			return -1;
		}
		ListNode* current = this->top;
		this->top = this->top->next;
		int result = current->value;
		delete current;
		size--;
		return result;

	}

	bool pop_bool(int& result) {
		if (this->top == nullptr) {
			std::cout<<"Trying to pop item from empty stack"<<std::endl;
			return false;
		}
		ListNode* current = this->top;
		this->top = this->top->next;
		result = current->value;
		delete current;
		size--;
		return true;
	}

//	void print() {
//		ListNode* current = this->top
//	}
};


int main() {
	Stack mystack;
	mystack.push(123);
	mystack.push(45);
	int result = 0;
	if (mystack.pop_bool(result)) {std::cout<<result<<std::endl;}
	if (mystack.pop_bool(result)) {std::cout<<result<<std::endl;}
//	std::cout<<mystack.pop()<<std::endl;
//	std::cout<<mystack.pop()<<std::endl;
	mystack.push(12345);
//	std::cout<<mystack.pop()<<std::endl;
//	std::cout<<mystack.pop()<<std::endl;
	if (mystack.pop_bool(result)) {std::cout<<result<<std::endl;}
	if (mystack.pop_bool(result)) {std::cout<<result<<std::endl;}
	return 0;
}
}


