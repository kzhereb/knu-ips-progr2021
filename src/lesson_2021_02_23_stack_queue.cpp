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

	int pop() {
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

//	void print() {
//		ListNode* current = this->top
//	}
};


int main() {
	Stack mystack;
	mystack.push(123);
	mystack.push(45);
	std::cout<<mystack.pop()<<std::endl;
	std::cout<<mystack.pop()<<std::endl;
	mystack.push(12345);
	std::cout<<mystack.pop()<<std::endl;
	std::cout<<mystack.pop()<<std::endl;
	return 0;
}
}


