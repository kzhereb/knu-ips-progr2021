/*
 * lesson_2021_02_23_stack_queue.cpp
 *
 *  Created on: Feb 23, 2021
 *      Author: KZ
 */

#include <iostream>
#include <exception>

//#define NDEBUG  // disable asserts; should be enabled automatically in release mode

#include <cassert>

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

	int* pop_pointer() {
		if (this->top == nullptr) {
			std::cout<<"Trying to pop item from empty stack"<<std::endl;
			return nullptr;
		}
		ListNode* current = this->top;
		this->top = this->top->next;
		int* result = new int;
		*result = current->value;
		delete current;
		size--;
		return result;
	}

	int pop_exception_string() {
		if (this->top == nullptr) {
			std::cout<<"Trying to pop item from empty stack"<<std::endl;
			throw "Trying to pop item from empty stack";
		}
		ListNode* current = this->top;
		this->top = this->top->next;
		int result = current->value;
		delete current;
		size--;
		return result;

	}

	int pop_exception() {
		if (this->top == nullptr) {
			//std::cout<<"Trying to pop item from empty stack"<<std::endl;
			throw std::logic_error("Trying to pop item from empty stack");
		}
		ListNode* current = this->top;
		this->top = this->top->next;
		int result = current->value;
		delete current;
		size--;
		return result;

	}

	int pop_assert() {
		assert(this->top != nullptr); // Trying to pop item from empty stack

		ListNode* current = this->top;
		this->top = this->top->next;
		int result = current->value;
		delete current;
		size--;
		return result;

	}

	int pop_assert_with_message() {
		assert(this->top != nullptr && "Trying to pop item from empty stack");

		ListNode* current = this->top;
		this->top = this->top->next;
		int result = current->value;
		delete current;
		size--;
		return result;

	}

	int pop() {
		return pop_assert_with_message();
	}


//	void print() {
//		ListNode* current = this->top
//	}
};

#define POP_PRINT std::cout<<mystack.pop()<<std::endl;
//#define POP_PRINT if (mystack.pop_bool(result)) {std::cout<<result<<std::endl;}
//#define POP_PRINT std::cout<<*mystack.pop_pointer()<<std::endl; //error
//#define POP_PRINT if(mystack.pop_pointer() != nullptr) {std::cout<<*mystack.pop_pointer()<<std::endl;} // call pop twice
//#define POP_PRINT p_result = mystack.pop_pointer(); if(p_result) {std::cout<<*p_result<<std::endl;} // memory leak
//#define POP_PRINT p_result = mystack.pop_pointer(); if(p_result) {std::cout<<*p_result<<std::endl; delete p_result;}
//#define POP_PRINT std::cout<<mystack.pop_exception()<<std::endl; //crashes on exception
//#define POP_PRINT try { std::cout<<mystack.pop_exception_string()<<std::endl; } catch (...) {std::cout<<"exception"<<std::endl;}
//#define POP_PRINT try { std::cout<<mystack.pop_exception()<<std::endl; } catch (const std::logic_error& e) {std::cerr<<e.what()<<std::endl;}
//#define POP_PRINT std::cout<<mystack.pop_assert()<<std::endl;
//#define POP_PRINT std::cout<<mystack.pop_assert_with_message()<<std::endl;

int main() {
	Stack mystack;
	mystack.push(123);
	mystack.push(45);
	int result = 0;
	int* p_result = nullptr;

	POP_PRINT
	POP_PRINT

	mystack.push(12345);

	POP_PRINT
	POP_PRINT
	POP_PRINT

	return 0;
}
}


